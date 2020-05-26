# Autonomous Drone Racing with Camera Based State Estimation

In collaboration with the Hybrid Robotics Laboratory at UC Berkeley, we developed autonomous flight technology in the form of state estimation and path planning software for an autonomous racing quadcopter. The result was a software pipeline that: creates a point cloud map of an indoor or outdoor racetrack using an Intel D435i depth camera and identifies the optimum global trajectory though the racetrack. Additionally, we presented an obstacle avoidance routine in MATLAB that used Model Predictive Control to avoid any unmapped obstacles along the global path.

I managed our projects transition though the COVID-19 crisis by collaborating with all involved parties to modify our project objectives to be attainable with limited resources while satisfying stakeholder needs. From a technical standpoint I created the software pipeline by identifying state-of-the-art open source perception and path planning software, modifying and combining this software into a single package, and creating a well documented and easy follow process for use. 
Relevant Skills: 
•	Crisis management, team management and project planning. 
•	ROS package programing and management. Perception – SLAM software experience and implementation (VINS-Mono / Surfel-Fusion, Intel D435i Depth Camera). 




## Description
This repository contains the ROS code for running the mapping – planning software framework for the Autonomous Drone Racing Using Camera Based State Estimation capstone project. The code is presented in three separate catkin workspaces. 
Catkin_ws_a and Catkin_ws_trr are fully assembled.
Catkin_ws_r will require the user to use the catkin_make command to build it. 
Here is the compressed fully built Catkin_ws_r file https://drive.google.com/open?id=1R-WwLrWupxcx-CK5uR445IeeCpPop_wc

TRR_With_Custom_Map.sh includes all terminal commands to run the program. 

Simulation Instruction Document contains on overview of how to operate the code, installation dependencies, and description of how to modify the output

Once the code is installed, use the videos below to run the program.

https://drive.google.com/open?id=1mOaSCpTJieUQ3cFGDOCdT7mwziT2xOgW

https://drive.google.com/open?id=1zMSyWv-TfmQJRrOvJVQmEUx24sPxNPSg

Link to the final presentation: https://drive.google.com/open?id=1DWG8kx2Mh4NUdXWnB35eSfW9XLHJuGiE
