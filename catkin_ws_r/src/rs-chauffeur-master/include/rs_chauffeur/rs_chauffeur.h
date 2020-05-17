#include <librealsense2/rs.hpp>
#include <Eigen/Dense>
#include <opencv2/opencv.hpp>
#include <ros/ros.h>
#include <sensor_msgs/CameraInfo.h>
#include <sensor_msgs/Imu.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <thread>

using stream_index_pair = std::pair<rs2_stream, int>;
const stream_index_pair COLOR{RS2_STREAM_COLOR, 0};
const stream_index_pair DEPTH{RS2_STREAM_DEPTH, 0};
const stream_index_pair INFRA1{RS2_STREAM_INFRARED, 1};
const stream_index_pair INFRA2{RS2_STREAM_INFRARED, 2};
const stream_index_pair FISHEYE{RS2_STREAM_FISHEYE, 0};
const stream_index_pair FISHEYE1{RS2_STREAM_FISHEYE, 1};
const stream_index_pair FISHEYE2{RS2_STREAM_FISHEYE, 2};
const stream_index_pair GYRO{RS2_STREAM_GYRO, 0};
const stream_index_pair ACCEL{RS2_STREAM_ACCEL, 0};
const stream_index_pair POSE{RS2_STREAM_POSE, 0};

struct LaunchParams
{
  // Infrared/depth/laser module
  bool enable_infrared_left;
  bool enable_infrared_right;
  bool enable_depth;
  bool enable_laser;
  int infrared_width;
  int infrared_height;
  int infrared_fps;
  int infrared_exposure;
  std::string frame_id_infrared_left;
  std::string frame_id_infrared_right;
  std::string frame_id_depth;
  // Colour module
  bool enable_colour;
  int colour_width;
  int colour_height;
  int colour_fps;
  int colour_exposure;
  std::string frame_id_colour;
  // Motion module
  bool enable_motion;
  int freq_accel;
  int freq_gyro;
  std::string frame_id_motion;
  // Performance measures
  bool enable_fps_monitor;
};

void getSensor(const rs2::device& device,
               const std::string& target,
               rs2::sensor& sensor)
{
  for (const auto& query_sensor : device.query_sensors())
  {
    const auto sensor_name = query_sensor.get_info(RS2_CAMERA_INFO_NAME);
    if (!strcmp(sensor_name, target.c_str()))
    {
      sensor = query_sensor;
      break;
    }
  }
}

sensor_msgs::CameraInfo generateStreamCalibData(const rs2::video_stream_profile& video_profile)
{
  rs2_intrinsics intrinsic = video_profile.get_intrinsics();
  sensor_msgs::CameraInfo camera_info;
  camera_info.distortion_model = "plumb_bob";
  camera_info.header.frame_id = "body";
  camera_info.width = intrinsic.width;
  camera_info.height = intrinsic.height;

  camera_info.K.at(0) = intrinsic.fx;
  camera_info.K.at(2) = intrinsic.ppx;
  camera_info.K.at(4) = intrinsic.fy;
  camera_info.K.at(5) = intrinsic.ppy;
  camera_info.K.at(8) = 1;

  camera_info.P.at(0) = camera_info.K.at(0);
  camera_info.P.at(1) = 0;
  camera_info.P.at(2) = camera_info.K.at(2);
  camera_info.P.at(3) = 0;
  camera_info.P.at(4) = 0;
  camera_info.P.at(5) = camera_info.K.at(4);
  camera_info.P.at(6) = camera_info.K.at(5);
  camera_info.P.at(7) = 0;
  camera_info.P.at(8) = 0;
  camera_info.P.at(9) = 0;
  camera_info.P.at(10) = 1;
  camera_info.P.at(11) = 0;

  // Set R (rotation matrix) values to identity matrix
  camera_info.R.at(0) = 1.0;
  camera_info.R.at(1) = 0.0;
  camera_info.R.at(2) = 0.0;
  camera_info.R.at(3) = 0.0;
  camera_info.R.at(4) = 1.0;
  camera_info.R.at(5) = 0.0;
  camera_info.R.at(6) = 0.0;
  camera_info.R.at(7) = 0.0;
  camera_info.R.at(8) = 1.0;

  camera_info.D.resize(5);
  camera_info.D.at(0) = intrinsic.coeffs[0];
  camera_info.D.at(1) = intrinsic.coeffs[1];
  camera_info.D.at(2) = intrinsic.coeffs[2];
  camera_info.D.at(3) = intrinsic.coeffs[3];
  camera_info.D.at(4) = intrinsic.coeffs[4];
  return camera_info;
}

void generateStreamCalibDataFromRsRosWrapper(const rs2::video_stream_profile& video_profile)
{
  std::map<stream_index_pair, sensor_msgs::CameraInfo> camera_info;
  std::map<stream_index_pair, sensor_msgs::CameraInfo> depth_aligned_camera_info;
  std::map<stream_index_pair, rs2_intrinsics> stream_intrinsics;
  std::map<stream_index_pair, std::string> optical_frame_id;
  std::map<stream_index_pair, bool> _enable;
  std::map<stream_index_pair, std::vector<rs2::stream_profile>> enabled_profiles;

  stream_index_pair stream_index{video_profile.stream_type(), video_profile.stream_index()};
  rs2_intrinsics intrinsic = video_profile.get_intrinsics();
  stream_intrinsics[stream_index] = intrinsic;

  ROS_INFO("generateStreamCalibDataFromRsRosWrapper: intrinsic ->  width: %d", intrinsic.width);
  ROS_INFO("generateStreamCalibDataFromRsRosWrapper: intrinsic -> height: %d", intrinsic.height);
  ROS_INFO("generateStreamCalibDataFromRsRosWrapper: intrinsic ->     fx: %.3f", intrinsic.fx);
  ROS_INFO("generateStreamCalibDataFromRsRosWrapper: intrinsic ->     fy: %.3f", intrinsic.fy);
  ROS_INFO("generateStreamCalibDataFromRsRosWrapper: intrinsic ->    ppx: %.3f", intrinsic.ppx);
  ROS_INFO("generateStreamCalibDataFromRsRosWrapper: intrinsic ->    ppy: %.3f", intrinsic.ppy);

  camera_info[stream_index].width = intrinsic.width;
  camera_info[stream_index].height = intrinsic.height;
  camera_info[stream_index].header.frame_id = optical_frame_id[stream_index];

  camera_info[stream_index].K.at(0) = intrinsic.fx;
  camera_info[stream_index].K.at(2) = intrinsic.ppx;
  camera_info[stream_index].K.at(4) = intrinsic.fy;
  camera_info[stream_index].K.at(5) = intrinsic.ppy;
  camera_info[stream_index].K.at(8) = 1;

  camera_info[stream_index].P.at(0) = camera_info[stream_index].K.at(0);
  camera_info[stream_index].P.at(1) = 0;
  camera_info[stream_index].P.at(2) = camera_info[stream_index].K.at(2);
  camera_info[stream_index].P.at(3) = 0;
  camera_info[stream_index].P.at(4) = 0;
  camera_info[stream_index].P.at(5) = camera_info[stream_index].K.at(4);
  camera_info[stream_index].P.at(6) = camera_info[stream_index].K.at(5);
  camera_info[stream_index].P.at(7) = 0;
  camera_info[stream_index].P.at(8) = 0;
  camera_info[stream_index].P.at(9) = 0;
  camera_info[stream_index].P.at(10) = 1;
  camera_info[stream_index].P.at(11) = 0;

  camera_info[stream_index].distortion_model = "plumb_bob";

  // set R (rotation matrix) values to identity matrix
  camera_info[stream_index].R.at(0) = 1.0;
  camera_info[stream_index].R.at(1) = 0.0;
  camera_info[stream_index].R.at(2) = 0.0;
  camera_info[stream_index].R.at(3) = 0.0;
  camera_info[stream_index].R.at(4) = 1.0;
  camera_info[stream_index].R.at(5) = 0.0;
  camera_info[stream_index].R.at(6) = 0.0;
  camera_info[stream_index].R.at(7) = 0.0;
  camera_info[stream_index].R.at(8) = 1.0;

  camera_info[stream_index].D.resize(5);

  for (int i = 0; i < 5; i++)
  {
    camera_info[stream_index].D.at(i) = intrinsic.coeffs[i];
  }

  if (stream_index == DEPTH && _enable[DEPTH] && _enable[COLOR])
  {
    camera_info[stream_index].P.at(3) = 0;
    camera_info[stream_index].P.at(7) = 0;
  }

  bool _align_depth = false;
  if (_align_depth)
  {
    for (auto& profiles : enabled_profiles)
    {
      for (auto& profile : profiles.second)
      {
        auto video_profile = profile.as<rs2::video_stream_profile>();
        stream_index_pair stream_index{video_profile.stream_type(), video_profile.stream_index()};
        depth_aligned_camera_info[stream_index] = camera_info[stream_index];
      }
    }
  }
}

class LerpBuffer
{
public:
  std::deque<double> lerped_gyro_ts;
  std::deque<Eigen::Vector3d> lerped_gyro_data;
  std::deque<double> lerped_accel_ts;
  std::deque<Eigen::Vector3d> lerped_accel_data;

  inline bool isReady()
  {
    if (buf_ts_.size() >= 3 && buf_type_.back() == true) { return true; }
    return false;
  }

  inline void addAccel(const double ts_s,
                       const double ax,
                       const double ay,
                       const double az)
  {
    buf_type_.push_back(true);
    buf_ts_.push_back(ts_s);
    buf_data_.emplace_back(ax, ay, az);
  }

  inline void addGyro(const double ts_s,
                      const double wx,
                      const double wy,
                      const double wz)
  {
    if (buf_type_.size() && buf_type_.front() == true)
    {
      buf_type_.push_back(false);
      buf_ts_.push_back(ts_s);
      buf_data_.emplace_back(wx, wy, wz);
    }
  }

  inline void interpolate()
  {
    double t0 = 0;
    Eigen::Vector3d d0;
    double t1 = 0;
    Eigen::Vector3d d1;
    bool t0_set = false;

    std::deque<double> lerp_ts;
    std::deque<Eigen::Vector3d> lerp_data;

    double ts = 0.0;
    bool dtype;
    Eigen::Vector3d data;

    while (buf_ts_.size())
    {
      ts = buf_ts_.front();
      buf_ts_.pop_front();
      dtype = buf_type_.front();
      buf_type_.pop_front();
      data = buf_data_.front();
      buf_data_.pop_front();

      if (t0_set == false && dtype == true)
      {
        t0 = ts;
        d0 = data;
        t0_set = true;
      }
      else if (t0_set && dtype == true)
      {
        t1 = ts;
        d1 = data;
        while (lerp_ts.size()) {
          const double lts = lerp_ts.front();
          const Eigen::Vector3d ldata = lerp_data.front();
          const double dt = t1 - t0;
          const double alpha = (lts - t0) / dt;

          lerped_accel_ts.push_back(lts);
          lerped_accel_data.push_back(lerp_(d0, d1, alpha));
          lerped_gyro_ts.push_back(lts);
          lerped_gyro_data.push_back(ldata);
          lerp_ts.pop_front();
          lerp_data.pop_front();
        }
        t0 = t1;
        d0 = d1;
      }
      else if (t0_set && ts >= t0 && dtype == false)
      {
        lerp_ts.push_back(ts);
        lerp_data.push_back(data);
      }
    }
    buf_ts_.push_back(ts);
    buf_type_.push_back(dtype);
    buf_data_.push_back(data);
  }

  inline void clear()
  {
    lerped_gyro_ts.clear();
    lerped_gyro_data.clear();
    lerped_accel_ts.clear();
    lerped_accel_data.clear();
  }

private:
  // Accelerometer: true
  // Gyroscope: false
  std::deque<bool> buf_type_;
  std::deque<double> buf_ts_;
  std::deque<Eigen::Vector3d> buf_data_;

  template <typename T>
  T lerp_(const T& a, const T& b, const double t)
  {
    return a * (1.0 - t) + b * t;
  }
};

class RsMotionModule
{
public:
  RsMotionModule(const rs2::device& device,
                 const LaunchParams& lp,
                 const std::function<void(const rs2::frame& frame)> callback)
  {
    if (lp.enable_motion)
    {
      // Configure the sensor
      rs2::config cfg;
      rs2::sensor sensor_motion;
      getSensor(device, "Motion Module", sensor_motion);
      sensor_motion.set_option(RS2_OPTION_GLOBAL_TIME_ENABLED, true);
      cfg.enable_stream(RS2_STREAM_ACCEL, RS2_FORMAT_MOTION_XYZ32F, lp.freq_accel);
      cfg.enable_stream(RS2_STREAM_GYRO, RS2_FORMAT_MOTION_XYZ32F, lp.freq_gyro);
      // Start streaming
      pipeline_.start(cfg, callback);
    }
  }

  ~RsMotionModule() { pipeline_.stop(); }

private:
  rs2::pipeline pipeline_;
};

class RsImageModule
{
public:
  RsImageModule(const rs2::device& device,
                const LaunchParams& lp,
                const std::function<void(const rs2::frame& frame)> callback)
  {
    // Configure the sensors
    rs2::config cfg;
    // If depth is enabled, both of the infrared sensors have to be enabled
    if (lp.enable_depth)
    {
      rs2::sensor sensor_stereo;
      getSensor(device, "Stereo Module", sensor_stereo);
      sensor_stereo.set_option(RS2_OPTION_GLOBAL_TIME_ENABLED, true);
      sensor_stereo.set_option(RS2_OPTION_EMITTER_ENABLED, lp.enable_laser);
      sensor_stereo.set_option(RS2_OPTION_EXPOSURE, lp.infrared_exposure);
      cfg.enable_stream(RS2_STREAM_INFRARED, 1,
                        lp.infrared_width, lp.infrared_height,
                        RS2_FORMAT_Y8, lp.infrared_fps);
      cfg.enable_stream(RS2_STREAM_INFRARED, 2,
                        lp.infrared_width, lp.infrared_height,
                        RS2_FORMAT_Y8, lp.infrared_fps);
      cfg.enable_stream(RS2_STREAM_DEPTH,
                        lp.infrared_width, lp.infrared_height,
                        RS2_FORMAT_Z16, lp.infrared_fps);
    }
    else  // If either infrared sensor is enabled but depth
    {
      rs2::sensor sensor_stereo;
      getSensor(device, "Stereo Module", sensor_stereo);
      sensor_stereo.set_option(RS2_OPTION_GLOBAL_TIME_ENABLED, true);
      sensor_stereo.set_option(RS2_OPTION_EMITTER_ENABLED, lp.enable_laser);
      sensor_stereo.set_option(RS2_OPTION_EXPOSURE, lp.infrared_exposure);
      if (lp.enable_infrared_left)
      {
        cfg.enable_stream(RS2_STREAM_INFRARED, 1,
                          lp.infrared_width, lp.infrared_height,
                          RS2_FORMAT_Y8, lp.infrared_fps);
      }
      if (lp.enable_infrared_right)
      {
        cfg.enable_stream(RS2_STREAM_INFRARED, 2,
                          lp.infrared_width, lp.infrared_height,
                          RS2_FORMAT_Y8, lp.infrared_fps);
      }
    }
    // If the colour sensor is enabled
    if (lp.enable_colour)
    {
      rs2::sensor sensor_colour;
      getSensor(device, "RGB Camera", sensor_colour);
      sensor_colour.set_option(RS2_OPTION_GLOBAL_TIME_ENABLED, true);
      // Negative exposure values for setting auto exposure
      if (lp.colour_exposure < 0)
      {
        sensor_colour.set_option(RS2_OPTION_ENABLE_AUTO_EXPOSURE, true);
      }
      else
      {
        sensor_colour.set_option(RS2_OPTION_EXPOSURE, lp.colour_exposure);
      }
      cfg.enable_stream(RS2_STREAM_COLOR, lp.colour_width, lp.colour_height,
                        RS2_FORMAT_RGB8, lp.colour_fps);
    }
    // Start streaming
    pipeline_.start(cfg, callback);
  }

  ~RsImageModule() { pipeline_.stop(); }

private:
  rs2::pipeline pipeline_;
};

class RsChauffeur
{
public:
  RsChauffeur()
  {
    ros::NodeHandle nh("~");
    // Infrared/depth/laser module
    nh.getParam("enable_infrared_left",    launch_params_.enable_infrared_left);
    nh.getParam("enable_infrared_right",   launch_params_.enable_infrared_right);
    nh.getParam("enable_depth",            launch_params_.enable_depth);
    nh.getParam("enable_laser",            launch_params_.enable_laser);
    nh.getParam("infrared_width",          launch_params_.infrared_width);
    nh.getParam("infrared_height",         launch_params_.infrared_height);
    nh.getParam("infrared_fps",            launch_params_.infrared_fps);
    nh.getParam("infrared_exposure",       launch_params_.infrared_exposure);
    nh.getParam("frame_id_infrared_left",  launch_params_.frame_id_infrared_left);
    nh.getParam("frame_id_infrared_right", launch_params_.frame_id_infrared_right);
    nh.getParam("frame_id_depth",          launch_params_.frame_id_depth);
    // Colour module
    nh.getParam("enable_colour",           launch_params_.enable_colour);
    nh.getParam("colour_width",            launch_params_.colour_width);
    nh.getParam("colour_height",           launch_params_.colour_height);
    nh.getParam("colour_fps",              launch_params_.colour_fps);
    nh.getParam("colour_exposure",         launch_params_.colour_exposure);
    nh.getParam("frame_id_colour",         launch_params_.frame_id_colour);
    // Motion module
    nh.getParam("enable_motion",           launch_params_.enable_motion);
    nh.getParam("freq_accel",              launch_params_.freq_accel);
    nh.getParam("freq_gyro",               launch_params_.freq_gyro);
    nh.getParam("frame_id_motion",         launch_params_.frame_id_motion);
    // Performance measures
    nh.getParam("enable_fps_monitor",      launch_params_.enable_fps_monitor);

    // Lock-free flags
    is_image_updated_infrared_left_      = false;
    is_image_updated_infrared_right_     = false;
    is_image_updated_colour_             = false;
    is_image_updated_depth_              = false;
    is_motion_updated_imu_               = false;
    is_caminfo_retrieved_infrared_left_  = false;
    is_caminfo_retrieved_infrared_right_ = false;
    is_caminfo_retrieved_depth_          = false;
    is_caminfo_retrieved_colour_         = false;

    // Publish topics at the Nyquist frequency
    const double nyq_freq_ratio = 2.;
    const double dur_infrared = 1. / launch_params_.infrared_fps / nyq_freq_ratio;
    const double dur_colour   = 1. / launch_params_.colour_fps / nyq_freq_ratio;
    const double dur_motion   = 1. / launch_params_.freq_gyro / nyq_freq_ratio;
    if (launch_params_.enable_infrared_left || launch_params_.enable_infrared_right)
      timer_infrared_ = nh.createTimer(ros::Duration(dur_infrared), &RsChauffeur::publishInfrared_, this);
    if (launch_params_.enable_depth)
      timer_depth_ = nh.createTimer(ros::Duration(dur_infrared), &RsChauffeur::publishDepth_, this);
    if (launch_params_.enable_colour)
      timer_colour_ = nh.createTimer(ros::Duration(dur_colour), &RsChauffeur::publishColour_, this);
    if (launch_params_.enable_motion)
      timer_motion_ = nh.createTimer(ros::Duration(dur_motion), &RsChauffeur::publishMotion_, this);
    if (launch_params_.enable_fps_monitor)
      timer_monitor_fps_ = nh.createTimer(ros::Duration(1.), &RsChauffeur::monitorFps_, this);

    // Publishers
    const std::string topic_name_infrared_left          = "infrared/left/image";
    const std::string topic_name_infrared_left_caminfo  = "infrared/left/camera_info";
    const std::string topic_name_infrared_right         = "infrared/right/image";
    const std::string topic_name_infrared_right_caminfo = "infrared/right/camera_info";
    const std::string topic_name_depth                  = "depth/image";
    const std::string topic_name_depth_caminfo          = "depth/camera_info";
    const std::string topic_name_colour                 = "colour/image";
    const std::string topic_name_colour_caminfo         = "colour/camera_info";
    const std::string topic_name_motion                 = "motion/imu";

    // Infrared/depth/laser module
    int buf_size_infrared = launch_params_.infrared_fps * 2;
    if (launch_params_.enable_infrared_left)
    {
      image_infrared_left_ = boost::make_shared<sensor_msgs::Image>();
      image_transport::ImageTransport it_infrared_left(nh);
      pub_infrared_left = it_infrared_left.advertise(topic_name_infrared_left, buf_size_infrared);
      pub_caminfo_infrared_left_ = nh.advertise<sensor_msgs::CameraInfo>(topic_name_infrared_left_caminfo, buf_size_infrared);
    }
    if (launch_params_.enable_infrared_right)
    {
      image_infrared_right_ = boost::make_shared<sensor_msgs::Image>();
      image_transport::ImageTransport it_infrared_right(nh);
      pub_infrared_right = it_infrared_right.advertise(topic_name_infrared_right, buf_size_infrared);
      pub_caminfo_infrared_right_ = nh.advertise<sensor_msgs::CameraInfo>(topic_name_infrared_right_caminfo, buf_size_infrared);
    }
    if (launch_params_.enable_depth)
    {
      image_depth_ = boost::make_shared<sensor_msgs::Image>();
      image_transport::ImageTransport it_depth(nh);
      pub_depth_ = it_depth.advertise(topic_name_depth, buf_size_infrared);
      pub_caminfo_depth_ = nh.advertise<sensor_msgs::CameraInfo>(topic_name_depth_caminfo, buf_size_infrared);
    }
    // Colour module
    if (launch_params_.enable_colour)
    {
      image_colour_ = boost::make_shared<sensor_msgs::Image>();
      image_transport::ImageTransport it_colour(nh);
      int buf_size = launch_params_.colour_fps * 2;
      pub_colour_ = it_colour.advertise(topic_name_colour, buf_size);
      pub_caminfo_colour_ = nh.advertise<sensor_msgs::CameraInfo>(topic_name_colour_caminfo, buf_size);
    }
    // Motion module
    if (launch_params_.enable_motion)
    {
      int buf_size = launch_params_.freq_gyro * 2;
      pub_motion_ = nh.advertise<sensor_msgs::Imu>(topic_name_motion, buf_size);
    }
  }

  void ignite()
  {
    LerpBuffer lb;
    // Motion callback
    auto callbackMotion = [&](const rs2::frame& frame)
    {
      const rs2::motion_frame mf = frame.as<rs2::motion_frame>();
      if (mf)
      {
        if (mf && mf.get_profile().stream_type() == RS2_STREAM_ACCEL)
        {
          double ts_s = mf.get_timestamp() * 1e-3;
          const rs2_vector data = mf.get_motion_data();
          lb.addAccel(ts_s, data.x, data.y, data.z);
        }
        else if (mf && mf.get_profile().stream_type() == RS2_STREAM_GYRO)
        {
          double ts_s = mf.get_timestamp() * 1e-3;
          const rs2_vector data = mf.get_motion_data();
          lb.addGyro(ts_s, data.x, data.y, data.z);
        }
        if (lb.isReady())
        {
          lb.interpolate();
          extractMotionImu_(lb);
        }
      }
    };

    // Image callback
    auto callbackImage = [&](const rs2::frame& frame)
    {
      if (const rs2::frameset fs = frame.as<rs2::frameset>())
      {
        thread_pool_.clear();
        // Initialise all image callbacks as a single thread
        if (launch_params_.enable_infrared_left ||
            launch_params_.enable_infrared_right ||
            launch_params_.enable_colour)
          thread_pool_.push_back(std::thread(&RsChauffeur::threadProcessImages_, this, fs));
        // TODO: Synchronise the timestamps between the colour and depth
        // Initialise the depth callback as a single thread
        if (launch_params_.enable_depth)
          thread_pool_.push_back(std::thread(&RsChauffeur::threadProcessDepth_, this, fs));
        // Join the threads
        for (unsigned int i = 0; i < thread_pool_.size(); ++i)
          thread_pool_[i].join();
        // Performance analysis
        ++loop_count_callback_image_;
      }
    };

    // Connect and ignite
    rs2::context context;
    rs2::device_list devices = context.query_devices();
    if (devices.size() == 0)
    {
      ROS_FATAL("No RealSense cameras found. Aborting...");
      exit(-1);
    }
    RsMotionModule rmm(devices[0], launch_params_, callbackMotion);
    RsImageModule rim(devices[0], launch_params_, callbackImage);
    // Discard the first flush due to the sensor initialisation
    sleep(1);
    ros::spin();
  }

private:
  // ROS parameters
  LaunchParams launch_params_;
  // ROS publishers
  image_transport::Publisher pub_infrared_left;
  image_transport::Publisher pub_infrared_right;
  image_transport::Publisher pub_depth_;
  image_transport::Publisher pub_colour_;
  ros::Publisher pub_caminfo_infrared_left_;
  ros::Publisher pub_caminfo_infrared_right_;
  ros::Publisher pub_caminfo_depth_;
  ros::Publisher pub_caminfo_colour_;
  ros::Publisher pub_motion_;
  // ROS timers
  ros::Timer timer_infrared_;
  ros::Timer timer_colour_;
  ros::Timer timer_depth_;
  ros::Timer timer_motion_;
  // Flags for asynchronous and lock-free I/O
  bool is_image_updated_infrared_left_;
  bool is_image_updated_infrared_right_;
  bool is_image_updated_colour_;
  bool is_image_updated_depth_;
  bool is_motion_updated_imu_;
  bool is_caminfo_retrieved_infrared_left_;
  bool is_caminfo_retrieved_infrared_right_;
  bool is_caminfo_retrieved_depth_;
  bool is_caminfo_retrieved_colour_;
  // Cache messages
  sensor_msgs::ImagePtr image_infrared_left_;
  sensor_msgs::ImagePtr image_infrared_right_;
  sensor_msgs::ImagePtr image_colour_;
  sensor_msgs::ImagePtr image_depth_;
  sensor_msgs::CameraInfo caminfo_infrared_left_;
  sensor_msgs::CameraInfo caminfo_infrared_right_;
  sensor_msgs::CameraInfo caminfo_depth_;
  sensor_msgs::CameraInfo caminfo_colour_;
  sensor_msgs::Imu motion_imu_;
  // Performance measures
  std::vector<std::thread> thread_pool_;
  unsigned int loop_count_callback_image_ = 0;
  ros::Timer timer_monitor_fps_;

  inline void processInfraredLeft_(const rs2::frameset& fs)
  {
    const auto infrared_left = fs.get_infrared_frame(1);
    if (!is_caminfo_retrieved_infrared_left_)
    {
      auto profile = infrared_left.get_profile().as<rs2::video_stream_profile>();
      caminfo_infrared_left_ = generateStreamCalibData(profile);
      caminfo_infrared_left_.header.frame_id = launch_params_.frame_id_infrared_left;
      is_caminfo_retrieved_infrared_left_ = true;
    }
    if (infrared_left)
      extractImageInfrared_(infrared_left,
                            launch_params_.frame_id_infrared_left,
                            true,
                            caminfo_infrared_left_);
  }

  inline void processInfraredRight_(const rs2::frameset& fs)
  {
    const auto infrared_right = fs.get_infrared_frame(2);
    if (!is_caminfo_retrieved_infrared_right_)
    {
      auto profile = infrared_right.get_profile().as<rs2::video_stream_profile>();
      caminfo_infrared_right_ = generateStreamCalibData(profile);
      caminfo_infrared_right_.header.frame_id = launch_params_.frame_id_infrared_right;
      is_caminfo_retrieved_infrared_right_ = true;
    }
    if (infrared_right)
      extractImageInfrared_(infrared_right,
                            launch_params_.frame_id_infrared_right,
                            false,
                            caminfo_infrared_right_);
  }

  inline void processColour_(const rs2::frameset& fs)
  {
    const auto colour = fs.get_color_frame();
    if (!is_caminfo_retrieved_colour_)
    {
      auto profile = colour.get_profile().as<rs2::video_stream_profile>();
      caminfo_colour_ = generateStreamCalibData(profile);
      caminfo_colour_.header.frame_id = launch_params_.frame_id_colour;
      is_caminfo_retrieved_colour_ = true;
    }
    if (colour)
      extractImageColour_(colour, launch_params_.frame_id_colour, caminfo_colour_);
  }

  void threadProcessImages_(const rs2::frameset& fs)
  {
    // Infrared left
    if (launch_params_.enable_infrared_left)
      processInfraredLeft_(fs);
    // Infrared right
    if (launch_params_.enable_infrared_right)
      processInfraredRight_(fs);
    // Colour
    if (launch_params_.enable_colour)
      processColour_(fs);
  }

  void threadProcessDepth_(const rs2::frameset& fs)
  {
    // Align depth to colour
    rs2::align align(RS2_STREAM_COLOR);
    // Make sure that your RealSense SDK is compiled from source
    // in order to enable the native OpenMP support
    const auto fs_aligned = align.process(fs);
    const auto depth = fs_aligned.get_depth_frame();
    if (!is_caminfo_retrieved_depth_)
    {
      auto profile = depth.get_profile().as<rs2::video_stream_profile>();
      caminfo_depth_ = generateStreamCalibData(profile);
      caminfo_depth_.header.frame_id = launch_params_.frame_id_depth;
      is_caminfo_retrieved_depth_ = true;
    }
    if (depth)
      extractImageDepth_(depth, launch_params_.frame_id_depth, caminfo_depth_);
  }

  inline void publishInfrared_(const ros::TimerEvent&)
  {
    if (launch_params_.enable_infrared_left && is_image_updated_infrared_left_)
    {
      caminfo_infrared_left_.header.stamp = image_infrared_left_->header.stamp;
      pub_infrared_left.publish(*image_infrared_left_);
      pub_caminfo_infrared_left_.publish(caminfo_infrared_left_);
      is_image_updated_infrared_left_ = false;
    }
    if (launch_params_.enable_infrared_right && is_image_updated_infrared_right_)
    {
      caminfo_infrared_right_.header.stamp = image_infrared_right_->header.stamp;
      pub_infrared_right.publish(*image_infrared_right_);
      pub_caminfo_infrared_right_.publish(caminfo_infrared_right_);
      is_image_updated_infrared_right_ = false;
    }
  }

  inline void publishColour_(const ros::TimerEvent&)
  {
    if (is_image_updated_colour_)
    {
      caminfo_colour_.header.stamp = image_colour_->header.stamp;
      pub_colour_.publish(*image_colour_);
      pub_caminfo_colour_.publish(caminfo_colour_);
      is_image_updated_colour_ = false;
    }
  }

  inline void publishDepth_(const ros::TimerEvent&)
  {
    if (is_image_updated_depth_)
    {
      caminfo_depth_.header.stamp = image_depth_->header.stamp;
      pub_depth_.publish(*image_depth_);
      pub_caminfo_depth_.publish(caminfo_depth_);
      is_image_updated_depth_ = false;
    }
  }

  inline void publishMotion_(const ros::TimerEvent&)
  {
    if (is_motion_updated_imu_)
    {
      pub_motion_.publish(motion_imu_);
      is_motion_updated_imu_ = false;
    }
  }

  inline void extractTimestamp_(const rs2::video_frame& vf,
                                std_msgs::Header& header)
  {
    ros::Time stamp;
    stamp.fromNSec(rsFrameToTs_(vf));
    header.stamp = stamp;
  }

  inline void extractImageInfrared_(const rs2::video_frame& vf,
                                    const std::string& frame_id,
                                    const bool& is_left,
                                    const sensor_msgs::CameraInfo& caminfo)
  {
    // Extract timestamp
    std_msgs::Header header;
    header.frame_id = frame_id;
    extractTimestamp_(vf, header);
    // Convert and assign the image
    cv::Mat cv_frame = rsFrameToCvMat_(vf, vf.get_width(), vf.get_height(), CV_8UC1);
    if (is_left)
    {
      image_infrared_left_ = cv_bridge::CvImage(header, "mono8", cv_frame).toImageMsg();
      is_image_updated_infrared_left_ = true;
    }
    else
    {
      image_infrared_right_ = cv_bridge::CvImage(header, "mono8", cv_frame).toImageMsg();
      is_image_updated_infrared_right_ = true;
    }
  }

  inline void extractImageColour_(const rs2::video_frame& vf,
                                  const std::string& frame_id,
                                  sensor_msgs::CameraInfo& caminfo)
  {
    // Extract timestamp
    std_msgs::Header header;
    header.frame_id = frame_id;
    extractTimestamp_(vf, header);
    // Convert and assign the image
    cv::Mat cv_frame = rsFrameToCvMat_(vf, vf.get_width(), vf.get_height(), CV_8UC3);
    image_colour_ = cv_bridge::CvImage(header, "rgb8", cv_frame).toImageMsg();
    is_image_updated_colour_ = true;
  }

  inline void extractImageDepth_(const rs2::depth_frame& df,
                                 const std::string& frame_id,
                                 sensor_msgs::CameraInfo& caminfo)
  {
    // Extract timestamp
    std_msgs::Header header;
    header.frame_id = frame_id;
    extractTimestamp_(df, header);
    // Convert and assign the image
    cv::Mat cv_frame = rsFrameToCvMat_(df, df.get_width(), df.get_height(), CV_16UC1);
    image_depth_ = cv_bridge::CvImage(header, "16UC1", cv_frame).toImageMsg();
    is_image_updated_depth_ = true;
  }

  inline void extractMotionImu_(LerpBuffer& buf)
  {
    while (buf.lerped_gyro_ts.size())
    {
      // Extract timestamp
      const auto ts = buf.lerped_gyro_ts.front();
      buf.lerped_gyro_ts.pop_front();
      buf.lerped_accel_ts.pop_front();
      // Accelerometer
      const auto accel = buf.lerped_accel_data.front();
      buf.lerped_accel_data.pop_front();
      // Gyroscope
      const auto gyro = buf.lerped_gyro_data.front();
      buf.lerped_gyro_data.pop_front();
      // Motion message header
      motion_imu_.header.frame_id = launch_params_.frame_id_motion;
      motion_imu_.header.stamp = ros::Time{ts};
      // Correct the IMU coordinate on RealSense
      motion_imu_.angular_velocity.x = gyro(2);
      motion_imu_.angular_velocity.y = -gyro(0);
      motion_imu_.angular_velocity.z = -gyro(1);
      motion_imu_.linear_acceleration.x = accel(2);
      motion_imu_.linear_acceleration.y = -accel(0);
      motion_imu_.linear_acceleration.z = -accel(1);
      is_motion_updated_imu_ = true;
    }
    buf.clear();
  }

  inline static cv::Mat rsFrameToCvMat_(const rs2::frame& frame,
                                        const int width,
                                        const int height,
                                        const int format)
  {
    const cv::Size size(width, height);
    const auto stride = cv::Mat::AUTO_STEP;
    const cv::Mat cv_frame(size, format, (void *)frame.get_data(), stride);
    return cv_frame;
  }

  inline static uint64_t strToTs_(const std::string& s)
  {
    uint64_t ts = 0;
    int idx = 0;
    for (int i = 0; i < s.length(); ++i)
    {
      const char c = s.at(s.length() - 1 - i);
      if (c != '.')
      {
        const uint64_t base = static_cast<uint64_t>(pow(10, idx));
        ts += std::atoi(&c) * base;
        ++idx;
      }
    }
    return ts;
  }

  inline static uint64_t rsFrameToTs_(const rs2::video_frame& vf)
  {
    // Calculate half of the exposure time
    // Frame metadata timestamp
    const auto frame_meta_key = RS2_FRAME_METADATA_FRAME_TIMESTAMP;
    const auto frame_ts_us = vf.get_frame_metadata(frame_meta_key);
    const auto frame_ts_ns = static_cast<uint64_t>(frame_ts_us) * 1000;
    // Sensor metadata timestamp
    const auto sensor_meta_key = RS2_FRAME_METADATA_SENSOR_TIMESTAMP;
    const auto sensor_ts_us = vf.get_frame_metadata(sensor_meta_key);
    const auto sensor_ts_ns = static_cast<uint64_t>(sensor_ts_us) * 1000;
    // Half exposure time
    const auto half_exposure_time_ns = frame_ts_ns - sensor_ts_ns;
    // Calculate corrected timestamp
    const auto ts_ms = vf.get_timestamp();
    const auto ts_ns = strToTs_(std::to_string(ts_ms));
    const auto ts_corrected_ns = ts_ns - half_exposure_time_ns;
    return static_cast<uint64_t>(ts_corrected_ns);
  }

  inline void monitorFps_(const ros::TimerEvent&)
  {
    ROS_INFO("Image callback loop rate: %d fps", (int)loop_count_callback_image_);
    loop_count_callback_image_ = 0;
  }
};