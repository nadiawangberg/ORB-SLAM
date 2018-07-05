..ORB SLAM EXAMPLE RUN (just see the ORB-SLAM2 github instead xD)..

./Examples/Monocular/mono_kitti Vocabulary/ORBvoc.txt Examples/Monocular/KITTI00-02.yaml /home/nawan/Downloads/dataset/sequences/00





...RUN ORB-SLAM2 WITH ROS...

--Pangolin--
cd Pangolin
*drep build som bor i pangolin*
mkdir build
cd build
cmake ..
cmake --build .

--In root or something--
source devel/setup.bash
roscore

--In ORB_SLAM2 somewhere--
*Åpne en ny terminal, må åpnes ETTER pangolin steppet*
rosrun ORB_SLAM2 Mono /home/nawan/ORB_SLAM2/Vocabulary/ORBvoc.txt /home/nawan/catkin_ws/src/microsoft_cam/CamCalib/Microsoft_calib_file.yaml

--Run bag--
rosbag play *rosbag name* (from where rosbag lives)

--Run node--
rosrun microsoft_cam microsoft_cam





...RUN ANY PROGRAM WITH OPENCV...
g++ main.cpp -o app `pkg-config --cflags --libs opencv`

(hvis kjørt med ROS bør openCV legges til som depend i package.xml og Cmakelist.noe, se visnav_ws)
