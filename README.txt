In this README replace usrname with your Linux username

-- Setting up ROS --
Create a ROS workspace named catkin_ws by following this tutorial http://wiki.ros.org/ROS/Tutorials/InstallingandConfiguringROSEnvironment


--Clone this repo--
clone this repo from github at location catkin_ws/src/. This repo will now be a new package in the catkin_ws


--Getting ORB_SLAM2 -- 
clone ORB_SLAM2 github repo at your home directory, Set up dependencies, get it running
https://github.com/raulmur/ORB_SLAM2








----- RUN ORB-SLAM2 WITH ROS -----
--Setting up ROS--
cd ~/catkin_ws
source devel/setup.bash
catkin_make
roscore


-- Build ORB_SLAM2 with ROS--
chmod +x build_ros.sh
./build_ros.sh


--Run ORB_SLAM node--
rosrun ORB_SLAM2 Mono /home/usrname/ORB_SLAM2/Vocabulary/ORBvoc.txt /home/usrname/catkin_ws/src/microsoft_cam/CamCalib/Microsoft_R.yaml

--Run nodenode--
rosrun microsoft_cam microsoft_cam

--Run rosbag--
rosbag play *rosbag name* (from where rosbag lives)





...RUN ANY PROGRAM WITH OPENCV...
g++ main.cpp -o app `pkg-config --cflags --libs opencv`

(hvis kjørt med ROS bør openCV legges til som depend i package.xml og Cmakelist.noe)


----- Troubleshooting -----

--Pangolin issues?--
cd Pangolin
*drep build som bor i pangolin*
mkdir build
cd build
cmake ..
cmake --build .


--The end of your bashrc script?--
#Single Computer ROS
export ROS_HOSTNAME=localhost
export ROS_MASTER_URI=http://localhost:11311

#Sourcing ROS
source /home/nawan/visnav_ws/devel/setup.bash
source /opt/ros/kinetic/setup.bash
source ~/catkin_ws/devel/setup.bash

# Virtual Environment Wrapper
source /usr/local/bin/virtualenvwrapper.sh

# Virtual Environment Wrapper

export ROS_PACKAGE_PATH=${ROS_PACKAGE_PATH}:/home/nawan/ORB_SLAM2/Examples/ROS





----- RUN ORB SLAM WITH MONOCULAR EXAMPLE VIDEO -----

https://github.com/raulmur/ORB_SLAM2#kitti-dataset

./Examples/Monocular/mono_kitti Vocabulary/ORBvoc.txt Examples/Monocular/KITTI00-02.yaml /home/nawan/Downloads/dataset/sequences/00

