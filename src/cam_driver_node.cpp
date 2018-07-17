#include "ros/ros.h"

#include "std_msgs/String.h"
#include <sensor_msgs/Image.h>
#include <cv_bridge/cv_bridge.h>


#include <opencv2/opencv.hpp>
#include <sstream>
#include <iostream>

int main(int argc, char **argv)
{
	ros::init(argc, argv, "cam_driver");
	ros::NodeHandle n;

	ros::Publisher image_pub = n.advertise<sensor_msgs::Image>("/camera/image_raw", 1);
	ros::Rate loop_rate(30);
	int count = 0;

	cv::VideoCapture input_stream(1);

	if(!input_stream.isOpened())
	{
		std::cerr << "Could not open camera\n";
		return EXIT_FAILURE;
	}

	//const std::string window_title = "Microsoft Camera Raw";
	//cv::namedWindow(window_title, cv::WINDOW_NORMAL);

	cv::Mat frame;


	while(ros::ok())
	{
		input_stream >> frame;

		if (frame.empty())
			{break;}
		
		//cv::imshow(window_title, frame);

		if (cv::waitKey(15) >= 0) 
			{break;}

		cv_bridge::CvImage msg;
		msg.header = std_msgs::Header();
		msg.encoding = "bgr8"; //Might be wrong
		msg.image = frame;

		image_pub.publish(msg.toImageMsg());
		ros::spinOnce();
		loop_rate.sleep();

	}
	return EXIT_SUCCESS;
}
