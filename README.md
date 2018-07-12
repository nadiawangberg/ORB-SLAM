# ROS camera driver
The purpose of this ROS package is to publish a camera stream to the ROS topic camera/image_raw. The package has a driver node called cam_driver which takes a camera stream as input and publishes it to the topic camera/image_raw. This package also has a folder CamCalib which contains code for camera calibration and .yaml calibration files.

In this README replace usrname/nawan/hvaadal with your Linux username


## Running ORB_SLAM2
### 1. Setting up ROS
Create a ROS workspace named catkin_ws by following this tutorial http://wiki.ros.org/ROS/Tutorials/InstallingandConfiguringROSEnvironment

### 2. Clone this repo (camera drivers for ROS)
clone this repo from github at location catkin_ws/src/. This repo will now be a new package in the catkin_ws


### 3. Downloading ORB_SLAM2
clone ORB_SLAM2 github repo at your home directory, follow guide, run and check if you have all dependencies
https://github.com/raulmur/ORB_SLAM2

### 4. Pangolin (ORB_SLAM2 dependency)
Clone the Pangolin github repo in your Computer/usr/local folder(remember to use sudo). Repo can be found at https://github.com/stevenlovegrove/Pangolin and get required Pangolin dependencies (like Glew, see Pangolin README)

#####Running pangolin:
cd Computer/usr/local/Pangolin
*evt drep build som bor i pangolin*
sudo mkdir build
cd build
sudo cmake ..
sudo cmake --build .

### 5. Running ORB_SLAM with monocular example video
https://github.com/raulmur/ORB_SLAM2#kitti-dataset

Run KITTI Dataset example with ORB_SLAM2 to check if things are working

./Examples/Monocular/mono_kitti Vocabulary/ORBvoc.txt Examples/Monocular/KITTI00-02.yaml /home/nawan/Downloads/dataset/sequences/00

If you followed step 1-6 and everything ran smoothly you can continune and make ORB_SLAM2 work with ROS. If you have issues with step 1-6 you can check the troubleshoot guide at the end of this README.







## RUN ORB-SLAM2 WITH ROS
**Remember to see troubleshoot guide WHEN errors occur**
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

https://github.com/raulmur/ORB_SLAM2#7-ros-examples

rosrun ORB_SLAM2 Mono /home/nawan/ORB_SLAM2/Vocabulary/ORBvoc.txt /home/nawan/catkin_ws/src/ROS_cam_driver/CamCalib/Microsoft_R.yaml

### 4. Run camera driver node
rosrun ROS_cam_driver
 ROS_cam_driver


### Run rosbag
rosbag play *rosbag name*
(can be ran instead of camera driver if you have rosbags)



## OPENCV Basics
**Building any openCV program:** g++ main.cpp -o app `pkg-config --cflags --libs opencv`

* *(hvis kjørt med ROS bør openCV legges til som depend i package.xml og Cmakelist.noe)* *


**Checking OpenCV version:** pkg-config --modversion opencv
* *(we used version 3.3.1)* *


##TF

#### Checking Pose from Orb_Slam
rosrun tf tf_echo camera_link camera_pose

This command prints out the rotation and translation of the drone. This rotation and translation is found from ORB_SLAM2

## Troubleshooting

### Pangolin issues
cd Pangolin
*drep build som bor i pangolin*
mkdir build
cd build
cmake ..
cmake --build .


### Is the end of your bashrc script configurated for ROS ORB-SLAM?
\#Single Computer ROS
export ROS_HOSTNAME=localhost
export ROS_MASTER_URI=http://localhost:11311

\#Sourcing ROS
source /home/nawan/visnav_ws/devel/setup.bash
source /opt/ros/kinetic/setup.bash
source ~/catkin_ws/devel/setup.bash

\# Virtual Environment Wrapper
source /usr/local/bin/virtualenvwrapper.sh

\# Virtual Environment Wrapper

export ROS_PACKAGE_PATH=${ROS_PACKAGE_PATH}:/home/nawan/ORB_SLAM2/Examples/ROS


### Error, problem finding packages / files
**[rosbuild] rospack found package "ORB_SLAM2" at "", but the current directory is "/home/nawan/ORB_SLAM2/Examples/ROS/ORB_SLAM2".  You should double-check your ROS_PACKAGE_PATH to ensure that packages are found in the correct precedence order.**

#####OR
c++: fatal error: input file ‘../lib/libORB_SLAM2.so’ is the same as output file
compilation terminated.


Error can likely be fixed by typing: 
export ROS_PACKAGE_PATH=${ROS_PACKAGE_PATH}:/home/nawan/ORB_SLAM2/Examples/ROS into terminal




### OpenCV error message
**Undefined reference to symbol '_ZN5boost6system15system_categoryEv'--**
https://github.com/raulmur/ORB_SLAM2/issues/494


**Post from forum**
Ok, I got confused. Remove all the flags in that CMakeList. You should do the changes in the ROS CMakeList. I think that is here: /home/USRNAME/ORB_SLAM2/Examples/ROS/ORB_SLAM2/CMakeList.txt

It should have this:

set(LIBS
${OpenCV_LIBS}
${EIGEN3_LIBS}
${Pangolin_LIBRARIES}
${PROJECT_SOURCE_DIR}/../../../Thirdparty/DBoW2/lib/libDBoW2.so
${PROJECT_SOURCE_DIR}/../../../Thirdparty/g2o/lib/libg2o.so
${PROJECT_SOURCE_DIR}/../../../lib/libORB_SLAM2.so
\-lboost_system
)


We only did what the above post said, see link above for discussion around this error message.



##Debug
**see command-line arguments for a launch file**
roslaunch --ros-args ROS_cam_driver driver.launch






