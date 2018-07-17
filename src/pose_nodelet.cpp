#include <ros/ros.h>
#include <tf/transform_listener.h>
#include "geometry_msgs/TransformStamped.h"
#include "tf/transform_datatypes.h"
#include <turtlesim/Pose.h>
#include <geometry_msgs/Twist.h>
#include <turtlesim/Spawn.h>

int main(int argc, char** argv){
	ros::init(argc, argv, "pose_listener");
	ros::NodeHandle nh;

	tf::TransformListener listener;

	ros::Rate rate(1.0);
  	while (nh.ok()){
    	tf::StampedTransform transform;
    	try{
      		listener.lookupTransform("world", "camera_pose",
                               ros::Time(0), transform);


      		tf::Vector3 translation = transform.getOrigin();
      		tf::Matrix3x3 rotation_m = transform.getBasis();
      		tf::Quaternion rotation_q = transform.getRotation();

          ROS_INFO("From pose_nodelet.cpp");
      		ROS_INFO("x: %f", translation.getX());
      		ROS_INFO("y: %f", translation.getY());
      		//ROS_INFO("z: %f", translation.getZ());



    	}
    	catch (tf::TransformException &ex) {
      		ROS_ERROR("%s",ex.what());
      		ros::Duration(1.0).sleep();
      		continue;
    	}
	}





}