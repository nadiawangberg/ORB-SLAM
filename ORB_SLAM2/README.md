##Monocular visual odometry using ORB_SLAM2 with ROS

**Make sure you have read the readme for vo_framework before reading this, that README will explain the general setup of this project.**


replace your ros_mono.cc file located at path \/home/USRNAME/ORB_SLAM2/Examples/ROS/ORB_SLAM2/src with the ros_mono.cc file in this folder. The ros_mono.cc file is edited such that the pose from ORB_SLAM2 is converted and sent as a tf message. The edited ros_mono.cc is mainly code from hmchungs comment from Nov 12 2017 at this pull request conversation https://github.com/raulmur/ORB_SLAM2/pull/102. More documentation can be found as comments in the code
