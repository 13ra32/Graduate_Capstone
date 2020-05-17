# Install script for directory: /home/ralexander/catkin_ws_a/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/ralexander/catkin_ws_a/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  
      if (NOT EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}")
        file(MAKE_DIRECTORY "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}")
      endif()
      if (NOT EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/.catkin")
        file(WRITE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/.catkin" "")
      endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/ralexander/catkin_ws_a/install/_setup_util.py")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/ralexander/catkin_ws_a/install" TYPE PROGRAM FILES "/home/ralexander/catkin_ws_a/build/catkin_generated/installspace/_setup_util.py")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/ralexander/catkin_ws_a/install/env.sh")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/ralexander/catkin_ws_a/install" TYPE PROGRAM FILES "/home/ralexander/catkin_ws_a/build/catkin_generated/installspace/env.sh")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/ralexander/catkin_ws_a/install/setup.bash;/home/ralexander/catkin_ws_a/install/local_setup.bash")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/ralexander/catkin_ws_a/install" TYPE FILE FILES
    "/home/ralexander/catkin_ws_a/build/catkin_generated/installspace/setup.bash"
    "/home/ralexander/catkin_ws_a/build/catkin_generated/installspace/local_setup.bash"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/ralexander/catkin_ws_a/install/setup.sh;/home/ralexander/catkin_ws_a/install/local_setup.sh")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/ralexander/catkin_ws_a/install" TYPE FILE FILES
    "/home/ralexander/catkin_ws_a/build/catkin_generated/installspace/setup.sh"
    "/home/ralexander/catkin_ws_a/build/catkin_generated/installspace/local_setup.sh"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/ralexander/catkin_ws_a/install/setup.zsh;/home/ralexander/catkin_ws_a/install/local_setup.zsh")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/ralexander/catkin_ws_a/install" TYPE FILE FILES
    "/home/ralexander/catkin_ws_a/build/catkin_generated/installspace/setup.zsh"
    "/home/ralexander/catkin_ws_a/build/catkin_generated/installspace/local_setup.zsh"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/ralexander/catkin_ws_a/install/.rosinstall")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/ralexander/catkin_ws_a/install" TYPE FILE FILES "/home/ralexander/catkin_ws_a/build/catkin_generated/installspace/.rosinstall")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/ralexander/catkin_ws_a/build/gtest/cmake_install.cmake")
  include("/home/ralexander/catkin_ws_a/build/ground_station/utils/catkin_simple/cmake_install.cmake")
  include("/home/ralexander/catkin_ws_a/build/ground_station/utils/DecompRos/decomp_ros_msgs/cmake_install.cmake")
  include("/home/ralexander/catkin_ws_a/build/ground_station/utils/cmake_utils/cmake_install.cmake")
  include("/home/ralexander/catkin_ws_a/build/ground_station/utils/pose_utils/cmake_install.cmake")
  include("/home/ralexander/catkin_ws_a/build/ground_station/utils/quadrotor_msgs/cmake_install.cmake")
  include("/home/ralexander/catkin_ws_a/build/ground_station/global_mapping/map_server/cmake_install.cmake")
  include("/home/ralexander/catkin_ws_a/build/ground_station/polyhedron_generator/cmake_install.cmake")
  include("/home/ralexander/catkin_ws_a/build/ground_station/joy_ctrl/cmake_install.cmake")
  include("/home/ralexander/catkin_ws_a/build/ground_station/utils/odom_visualization/cmake_install.cmake")
  include("/home/ralexander/catkin_ws_a/build/ground_station/simulation/state_machine/cmake_install.cmake")
  include("/home/ralexander/catkin_ws_a/build/ground_station/global_mapping/surfel_fusion/cmake_install.cmake")
  include("/home/ralexander/catkin_ws_a/build/ground_station/global_planner/cmake_install.cmake")
  include("/home/ralexander/catkin_ws_a/build/ground_station/utils/uav_utils/cmake_install.cmake")
  include("/home/ralexander/catkin_ws_a/build/ground_station/simulation/cascade_control/cmake_install.cmake")
  include("/home/ralexander/catkin_ws_a/build/ground_station/simulation/mission_template/cmake_install.cmake")
  include("/home/ralexander/catkin_ws_a/build/ground_station/simulation/router/cmake_install.cmake")
  include("/home/ralexander/catkin_ws_a/build/ground_station/simulation/so3_quadrotor_simulator/cmake_install.cmake")
  include("/home/ralexander/catkin_ws_a/build/ground_station/utils/DecompRos/decomp_ros_utils/cmake_install.cmake")
  include("/home/ralexander/catkin_ws_a/build/ground_station/utils/waypoint_generator/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/ralexander/catkin_ws_a/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
