rosrun joy joy_node & sleep 1;  # This should be installed
# This fails but i think its because I dont have a joystick connected, you can find information about the package here /opt/ros/kinetic/share/joy

roslaunch joy_ctrl joy_ctrl.launch & sleep 1; # This sets up the Rviz along with other things (dont know right now what they are)

# Modified where it looks for the mapping file, info here http://wiki.ros.org/pcl_ros#pcd_to_pointcloud
# rosrun pcl_ros pcd_to_pointcloud /home/ralexander/catkin_ws_a/src/ground_station/global_mapping/surfel_fusion/model.pcd 1.0 _frame_id:=map  & sleep 1;
rosrun pcl_ros pcd_to_pointcloud /home/ralexander/catkin_ws_a/src/ground_station/global_mapping/surfel_fusion/model_apt.pcd 1.0 _frame_id:=map  & sleep 1;
# rosrun pcl_ros pcd_to_pointcloud /home/ralexander/catkin_ws_a/src/ground_station/global_mapping/surfel_fusion/model_301.pcd 1.0 _frame_id:=map  & sleep 1;
# rosrun pcl_ros pcd_to_pointcloud /home/ralexander/catkin_ws_a/src/ground_station/global_mapping/surfel_fusion/model_balcony.pcd 1.0 _frame_id:=map  & sleep 1;


roslaunch trr_global_planner global_planner_exp.launch # This issue is here
# exec bash;

