cmake_minimum_required(VERSION 2.8.3)
project(rs4se)
set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(realsense2 REQUIRED)
find_package(
  catkin
  REQUIRED COMPONENTS
  roscpp
  std_msgs
  geometry_msgs
  cv_bridge
  image_transport
)

catkin_package(LIBRARIES ${PROJECT_NAME})

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${realsense2_INCLUDE_DIR}
  ${EIGEN3_INCLUDE_DIR}
)

set(DEPS
  ${realsense2_LIBRARY}
  ${OpenCV_LIBS}
  ${catkin_LIBRARIES}
)

add_executable(rs4se src/rs4se.cpp)
target_link_libraries(rs4se ${DEPS})
