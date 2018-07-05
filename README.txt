Download ORB_SLAM2, Set up dependencies, get it running
https://github.com/raulmur/ORB_SLAM2








----- RUN ORB-SLAM2 WITH ROS -----
--Setting up ROS--
cd ~/catkin_ws
source devel/setup.bash
catkin_make
roscore

--Running ORB_SLAM2 node--
rosrun ORB_SLAM2 Mono /home/nawan/ORB_SLAM2/Vocabulary/ORBvoc.txt /home/nawan/catkin_ws/src/microsoft_cam/CamCalib/Microsoft_calib_file.yaml

--Run nodenode--
rosrun microsoft_cam microsoft_cam

--Run rosbag--
rosbag play *rosbag name* (from where rosbag lives)





...RUN ANY PROGRAM WITH OPENCV...
g++ main.cpp -o app `pkg-config --cflags --libs opencv`

(hvis kjørt med ROS bør openCV legges til som depend i package.xml og Cmakelist.noe, se visnav_ws)


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

