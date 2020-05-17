# This document contains all the terminal commands to map an envirnment with a D435i depth camera
# and generate and optimum path in TRR's simulator using this map. 


##### Mapping phase
# These commands are for creating and saving a point cloud map


### Start the mapping sofware
source ~/catkin_ws_r/devel/setup.bash              # In All Terminals

roslaunch rs4se rs4se.launch                       # In Terminal 1 (D435i Driver)
roslaunch vins_estimator euroc.launch              # In Terminal 2 (Runs VINS-Mono to estimate the Cameras State)

# Verify that the cameras state is being recived
roslaunch vins_estimator vins_rviz.launch          # In Terminal 3 (See the Cameras State in Rviz)
# Be sure to close the rviz window before continuing

source ~/catkin_ws_a/devel/setup.bash              # In Terminal 4 
cd /home/ralexander/catkin_ws_a/src/ground_station
./mapping.sh
# Now walk arround with the camera and record the map
### Start the Mapping Sofware


### Saving the Map
# DELETE ALL FILES IN /home/ralexander/output/vins_output/d435i TO REBUILD THE MAP!
# press Ctrl+C on the ground station (mapping.sh terminal). This will save the point cloud data as model.pcd in the surfel_fusion file /home/ralexander/catkin_ws_a/src/ground_station/global_mapping/surfel_fusion
# to view the point coloud data copy it to pointcloud/build
cd pointcloud/build                      # Go to the right file directory
./range_image_visualization model.pcd    # View model.pcd
### Saving the Map
##### Mapping phase







##### Uploading the MAP
# To allow TRR's simulator to acess the map the user needs to rename the .pcd file found in:
# /home/ralexander/catkin_ws_a/src/ground_station/global_mapping/surfel_fusion
# Once this is done, ROS's point cloud library can be used to create a point cloud rostopic that can be acessed by TRR's simulator

# The point cloud I am using is called model_apt.pcd

# Point Cloud map of my appartment
rosrun pcl_ros pcd_to_pointcloud /home/ralexander/catkin_ws_a/src/ground_station/global_mapping/surfel_fusion/model_apt.pcd 1.0 _frame_id:=map  & sleep 1;

# Example point cloud map from TRR's simulator
rosrun pcl_ros pcd_to_pointcloud /home/ralexander/catkin_ws_a/src/ground_station/global_mapping/surfel_fusion/model_balcony.pcd 1.0 _frame_id:=map  & sleep 1;

# Example point cloud map from TRR's simulator
rosrun pcl_ros pcd_to_pointcloud /home/ralexander/catkin_ws_a/src/ground_station/global_mapping/surfel_fusion/model_301.pcd 1.0 _frame_id:=map  & sleep 1;

# Example point cloud map created by the random map generator in TRR's simulator
rosrun pcl_ros pcd_to_pointcloud /home/ralexander/catkin_ws_a/src/ground_station/global_mapping/surfel_fusion/trr_generated.pcd 1.0 _frame_id:=map  & sleep 1;


# It may also be usfull to alter the map you have recorded to work better with TRR's sofware. This can be done using a function that comes from TRR's experimental branch.

# The code below finds the model_apt.pcd file and modifies into a form thats easyer for TRR's simulator to work with


# To save the modifed point cloud map, start recording before you launch the inflating map sofware
cd bagfiles/
rosbag record /tr_node/inflation_map

# run the code to inflate model_apt.pcd
source ~/catkin_ws_a/devel/setup.bash              # In All Terminals
cd /home/ralexander/catkin_ws_a/src/ground_station # In Terminal 2
./teaching_planning.sh

# Close the bag termainal
rosbag play bag.bag # Just a check
rosrun pcl_ros bag_to_pcd bag.bag /tr_node/inflation_map /home/ralexander/bagfiles # Convert the bag file to a .pcd file

# Now place the file in /home/ralexander/catkin_ws_a/src/ground_station/global_mapping/surfel_fusion

# Inflated map of model_apt.pcd
rosrun pcl_ros pcd_to_pointcloud /home/ralexander/catkin_ws_a/src/ground_station/global_mapping/surfel_fusion/inflated_apt.pcd 1.0 _frame_id:=map  & sleep 1;
##### Uploading the MAP








##### Running the Simulator
roscore # terminal 1

rosrun pcl_ros pcd_to_pointcloud /home/ralexander/catkin_ws_a/src/ground_station/global_mapping/surfel_fusion/model_apt.pcd 1.0 _frame_id:=map  & sleep 1; # Or whatever map you want to use, terminal 2

cd ~/catkin_ws_trr/src/Teach-Repeat-Replan
python key2joy.py # Create keybord joystick

cd ~/catkin_ws_trr/src/Teach-Repeat-Replan
./trr_simulation.sh # Run the Simulation sofware
##### Running the Simulator





