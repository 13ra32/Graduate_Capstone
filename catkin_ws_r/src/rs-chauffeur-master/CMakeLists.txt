cmake_minimum_required(VERSION 2.8.3)
project(rs_chauffeur)
set(CMAKE_CXX_STANDARD 11)

find_package(OpenMP)
if (OpenMP_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

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

add_executable(rs_chauffeur src/rs_chauffeur.cpp)
target_link_libraries(rs_chauffeur ${DEPS})
