;; Auto-generated. Do not edit!


(when (boundp 'decomp_ros_msgs::PolyhedronArray)
  (if (not (find-package "DECOMP_ROS_MSGS"))
    (make-package "DECOMP_ROS_MSGS"))
  (shadow 'PolyhedronArray (find-package "DECOMP_ROS_MSGS")))
(unless (find-package "DECOMP_ROS_MSGS::POLYHEDRONARRAY")
  (make-package "DECOMP_ROS_MSGS::POLYHEDRONARRAY"))

(in-package "ROS")
;;//! \htmlinclude PolyhedronArray.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass decomp_ros_msgs::PolyhedronArray
  :super ros::object
  :slots (_header _polyhedrons _ids ))

(defmethod decomp_ros_msgs::PolyhedronArray
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:polyhedrons __polyhedrons) (let (r) (dotimes (i 0) (push (instance decomp_ros_msgs::Polyhedron :init) r)) r))
    ((:ids __ids) (make-array 0 :initial-element 0 :element-type :integer))
    )
   (send-super :init)
   (setq _header __header)
   (setq _polyhedrons __polyhedrons)
   (setq _ids __ids)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:polyhedrons
   (&rest __polyhedrons)
   (if (keywordp (car __polyhedrons))
       (send* _polyhedrons __polyhedrons)
     (progn
       (if __polyhedrons (setq _polyhedrons (car __polyhedrons)))
       _polyhedrons)))
  (:ids
   (&optional __ids)
   (if __ids (setq _ids __ids)) _ids)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; decomp_ros_msgs/Polyhedron[] _polyhedrons
    (apply #'+ (send-all _polyhedrons :serialization-length)) 4
    ;; int32[] _ids
    (* 4    (length _ids)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; decomp_ros_msgs/Polyhedron[] _polyhedrons
     (write-long (length _polyhedrons) s)
     (dolist (elem _polyhedrons)
       (send elem :serialize s)
       )
     ;; int32[] _ids
     (write-long (length _ids) s)
     (dotimes (i (length _ids))
       (write-long (elt _ids i) s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; decomp_ros_msgs/Polyhedron[] _polyhedrons
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _polyhedrons (let (r) (dotimes (i n) (push (instance decomp_ros_msgs::Polyhedron :init) r)) r))
     (dolist (elem- _polyhedrons)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;; int32[] _ids
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _ids (instantiate integer-vector n))
     (dotimes (i n)
     (setf (elt _ids i) (sys::peek buf ptr- :integer)) (incf ptr- 4)
     ))
   ;;
   self)
  )

(setf (get decomp_ros_msgs::PolyhedronArray :md5sum-) "a02cec87cf9719f586eda49f2fc2c4ea")
(setf (get decomp_ros_msgs::PolyhedronArray :datatype-) "decomp_ros_msgs/PolyhedronArray")
(setf (get decomp_ros_msgs::PolyhedronArray :definition-)
      "Header header
Polyhedron[] polyhedrons
int32[] ids
================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
# 0: no frame
# 1: global frame
string frame_id

================================================================================
MSG: decomp_ros_msgs/Polyhedron
geometry_msgs/Point[] points
geometry_msgs/Point[] normals #norm is an outer vector

================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z

")



(provide :decomp_ros_msgs/PolyhedronArray "a02cec87cf9719f586eda49f2fc2c4ea")


