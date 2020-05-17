# rs-chauffeur
An in-house ROS interface for the Intel RealSense D435i camera

## User guide
### Installation
1. Make sure that you have installed `librealsense v2.28.1` which can be accessed via this [[link](https://github.com/HybridRobotics/librealsense)]. You should compile from source to enable the OpenMP support otherwise you may experience frame drop on weak machines especially when the depth alignment is switched on.
2. ROS Kinetic or above is installed.
3. Calibrate your IMU's g-norm bloody accurately using this Python [[script](https://github.com/HybridRobotics/librealsense/blob/master/tools/rs-imu-calibration/rs-imu-calibration.py)].
4. Clone this repo into your catkin workspace and compile.

### Manoeuvre
1. Source your catkin workspace.
2. Run `roslaunch rs_chauffeur ignite.launch` in a terminal.
3. Use whichever tool you want to see the exposure of the infrared images.
4. If you see juicy highlights and shadows you are good to go. If not, conduct trial-and-error adjustments by changing the field `infrared_exposure` in the launch file.

## To-do list
### Plans
1. Encapsulate the code as a ROS Nodelet for zero memory copy - good for mobile platforms.
2. Separate the header into multiple files for easier maintenance.
3. Add auto-exposure capability to the infrared stream, if any.

### Finished
1. Optimise the performance on weak machines by multithreading/OpenMP.
2. Parallelise the depth alignment - see if it is easy to do.
3. Add manual-exposure support to the colour stream.