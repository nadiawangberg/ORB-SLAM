#ROS camera driver
The purpose of this ROS package is to publish a camera stream to the ROS topic camera/image_raw. The package has a driver node called cam_driver which takes a camera stream as input and publishes it to the topic camera/image_raw. This package also has a folder CamCalib which contains code for camera calibration and .yaml calibration files.

In this README replace usrname with your Linux username


## RUNNING ORB_SLAM2
### 1. Setting up ROS
Create a ROS workspace named catkin_ws by following this tutorial http://wiki.ros.org/ROS/Tutorials/InstallingandConfiguringROSEnvironment

### 2. Clone this repo
clone this repo from github at location catkin_ws/src/. This repo will now be a new package in the catkin_ws


### 3. Getting ORB_SLAM2
clone ORB_SLAM2 github repo at your home directory, follow guide, run and check if you have all dependencies
https://github.com/raulmur/ORB_SLAM2

### 4. Pangolin (ORB_SLAM2 dependency)
Clone the Pangolin github repo in your home folder from https://github.com/stevenlovegrove/Pangolin and get required Dependencies (see Pangolin README)

##### running pangolin 
cd Pangolin
*evt drep build som bor i pangolin*
mkdir build
cd build
cmake ..
cmake --build .

### 5. Run ORB_SLAM regularly with monocular example video
https://github.com/raulmur/ORB_SLAM2#kitti-dataset
Run KITTI Dataset example with ORB_SLAM2 to check if things are working

./Examples/Monocular/mono_kitti Vocabulary/ORBvoc.txt Examples/Monocular/KITTI00-02.yaml /home/usrname/Downloads/dataset/sequences/00


### 6. Run ORB_SLAM2 with ROS
Run ORB_SLAM2 node by following this guide

If you followed step 1-6 and everything ran smoothly you can continune and make ORB_SLAM2 work with ROS. If you have issues you can check the troubleshoot at the end of this README.






## RUN ORB-SLAM2 WITH ROS

### 1. Initializing ROS
cd ~/catkin_ws
source devel/setup.bash
catkin_make
roscore


### 2. Building ORB_SLAM2 with ROS
https://github.com/raulmur/ORB_SLAM2#7-ros-examples

chmod +x build_ros.sh
./build_ros.sh


### 3. Running ORB_SLAM2 node

rosrun ORB_SLAM2 Mono /home/usrname/ORB_SLAM2/Vocabulary/ORBvoc.txt /home/usrname/catkin_ws/src/microsoft_cam/CamCalib/Microsoft_R.yaml

### 4. Run camera driver node
rosrun microsoft_cam microsoft_cam

### Run rosbag
(can be ran instead of camera driver if you have rosbags)
rosbag play *rosbag name*



## OPENCV Basics
**Building any openCV program:** g++ main.cpp -o app `pkg-config --cflags --libs opencv`

* *(hvis kjørt med ROS bør openCV legges til som depend i package.xml og Cmakelist.noe)* *


**Checking OpenCV version:** pkg-config --modversion opencv
* *(we used version 3.3.1)* *


## Troubleshooting

###Pangolin issues
cd Pangolin
*drep build som bor i pangolin*
mkdir build
cd build
cmake ..
cmake --build .


##Is the end of your bashrc script configurated for ROS ORB-SLAM?
#Single Computer ROS
export ROS_HOSTNAME=localhost
export ROS_MASTER_URI=http://localhost:11311

#Sourcing ROS
source /home/usrname/visnav_ws/devel/setup.bash
source /opt/ros/kinetic/setup.bash
source ~/catkin_ws/devel/setup.bash

# Virtual Environment Wrapper
source /usr/local/bin/virtualenvwrapper.sh

# Virtual Environment Wrapper

export ROS_PACKAGE_PATH=${ROS_PACKAGE_PATH}:/home/nawan/ORB_SLAM2/Examples/ROS


### OpenCV error message: Undefined reference to symbol '_ZN5boost6system15system_categoryEv'--
https://github.com/raulmur/ORB_SLAM2/issues/494
Following this guide, mainly using AdrichCabreras response from Jan10 worked for us.

