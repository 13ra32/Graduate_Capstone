# Install script for directory: /home/ralexander/catkin_ws_trr/src/Teach-Repeat-Replan/utils/quadrotor_msgs

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/ralexander/catkin_ws_trr/install")
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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/quadrotor_msgs/msg" TYPE FILE FILES
    "/home/ralexander/catkin_ws_trr/src/Teach-Repeat-Replan/utils/quadrotor_msgs/msg/AuxCommand.msg"
    "/home/ralexander/catkin_ws_trr/src/Teach-Repeat-Replan/utils/quadrotor_msgs/msg/Corrections.msg"
    "/home/ralexander/catkin_ws_trr/src/Teach-Repeat-Replan/utils/quadrotor_msgs/msg/Gains.msg"
    "/home/ralexander/catkin_ws_trr/src/Teach-Repeat-Replan/utils/quadrotor_msgs/msg/OutputData.msg"
    "/home/ralexander/catkin_ws_trr/src/Teach-Repeat-Replan/utils/quadrotor_msgs/msg/PositionCommand.msg"
    "/home/ralexander/catkin_ws_trr/src/Teach-Repeat-Replan/utils/quadrotor_msgs/msg/PPROutputData.msg"
    "/home/ralexander/catkin_ws_trr/src/Teach-Repeat-Replan/utils/quadrotor_msgs/msg/Serial.msg"
    "/home/ralexander/catkin_ws_trr/src/Teach-Repeat-Replan/utils/quadrotor_msgs/msg/SO3Command.msg"
    "/home/ralexander/catkin_ws_trr/src/Teach-Repeat-Replan/utils/quadrotor_msgs/msg/StatusData.msg"
    "/home/ralexander/catkin_ws_trr/src/Teach-Repeat-Replan/utils/quadrotor_msgs/msg/TRPYCommand.msg"
    "/home/ralexander/catkin_ws_trr/src/Teach-Repeat-Replan/utils/quadrotor_msgs/msg/Odometry.msg"
    "/home/ralexander/catkin_ws_trr/src/Teach-Repeat-Replan/utils/quadrotor_msgs/msg/PolynomialTrajectory.msg"
    "/home/ralexander/catkin_ws_trr/src/Teach-Repeat-Replan/utils/quadrotor_msgs/msg/OptimalTimeAllocator.msg"
    "/home/ralexander/catkin_ws_trr/src/Teach-Repeat-Replan/utils/quadrotor_msgs/msg/TrajectoryMatrix.msg"
    "/home/ralexander/catkin_ws_trr/src/Teach-Repeat-Replan/utils/quadrotor_msgs/msg/ReplanCheck.msg"
    "/home/ralexander/catkin_ws_trr/src/Teach-Repeat-Replan/utils/quadrotor_msgs/msg/SpatialTemporalTrajectory.msg"
    "/home/ralexander/catkin_ws_trr/src/Teach-Repeat-Replan/utils/quadrotor_msgs/msg/Bspline.msg"
    "/home/ralexander/catkin_ws_trr/src/Teach-Repeat-Replan/utils/quadrotor_msgs/msg/SwarmCommand.msg"
    "/home/ralexander/catkin_ws_trr/src/Teach-Repeat-Replan/utils/quadrotor_msgs/msg/Replan.msg"
    "/home/ralexander/catkin_ws_trr/src/Teach-Repeat-Replan/utils/quadrotor_msgs/msg/SwarmOdometry.msg"
    "/home/ralexander/catkin_ws_trr/src/Teach-Repeat-Replan/utils/quadrotor_msgs/msg/SwarmInfo.msg"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/quadrotor_msgs/cmake" TYPE FILE FILES "/home/ralexander/catkin_ws_trr/build/Teach-Repeat-Replan/utils/quadrotor_msgs/catkin_generated/installspace/quadrotor_msgs-msg-paths.cmake")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/home/ralexander/catkin_ws_trr/devel/include/quadrotor_msgs")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/roseus/ros" TYPE DIRECTORY FILES "/home/ralexander/catkin_ws_trr/devel/share/roseus/ros/quadrotor_msgs")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/common-lisp/ros" TYPE DIRECTORY FILES "/home/ralexander/catkin_ws_trr/devel/share/common-lisp/ros/quadrotor_msgs")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/gennodejs/ros" TYPE DIRECTORY FILES "/home/ralexander/catkin_ws_trr/devel/share/gennodejs/ros/quadrotor_msgs")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  execute_process(COMMAND "/usr/bin/python" -m compileall "/home/ralexander/catkin_ws_trr/devel/lib/python2.7/dist-packages/quadrotor_msgs")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python2.7/dist-packages" TYPE DIRECTORY FILES "/home/ralexander/catkin_ws_trr/devel/lib/python2.7/dist-packages/quadrotor_msgs")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/ralexander/catkin_ws_trr/build/Teach-Repeat-Replan/utils/quadrotor_msgs/catkin_generated/installspace/quadrotor_msgs.pc")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/quadrotor_msgs/cmake" TYPE FILE FILES "/home/ralexander/catkin_ws_trr/build/Teach-Repeat-Replan/utils/quadrotor_msgs/catkin_generated/installspace/quadrotor_msgs-msg-extras.cmake")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/quadrotor_msgs/cmake" TYPE FILE FILES
    "/home/ralexander/catkin_ws_trr/build/Teach-Repeat-Replan/utils/quadrotor_msgs/catkin_generated/installspace/quadrotor_msgsConfig.cmake"
    "/home/ralexander/catkin_ws_trr/build/Teach-Repeat-Replan/utils/quadrotor_msgs/catkin_generated/installspace/quadrotor_msgsConfig-version.cmake"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/quadrotor_msgs" TYPE FILE FILES "/home/ralexander/catkin_ws_trr/src/Teach-Repeat-Replan/utils/quadrotor_msgs/package.xml")
endif()

