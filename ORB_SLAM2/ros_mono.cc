/**
* This file is part of ORB-SLAM2.
*
* Copyright (C) 2014-2016 Raúl Mur-Artal <raulmur at unizar dot es> (University of Zaragoza)
* For more information see <https://github.com/raulmur/ORB_SLAM2>
*
* ORB-SLAM2 is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* ORB-SLAM2 is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with ORB-SLAM2. If not, see <http://www.gnu.org/licenses/>.
*/


#include<iostream>
#include<algorithm>
#include<fstream>
#include<chrono>

#include<ros/ros.h>
#include <cv_bridge/cv_bridge.h>

#include<opencv2/core/core.hpp>
#include "geometry_msgs/TransformStamped.h"

#include"../../../include/System.h"
#include "tf/transform_datatypes.h"
#include <tf/transform_broadcaster.h>

using namespace std;

class ImageGrabber
{
public:
    ImageGrabber(ORB_SLAM2::System* pSLAM):mpSLAM(pSLAM){}

    void GrabImage(const sensor_msgs::ImageConstPtr& msg);

    ORB_SLAM2::System* mpSLAM;
};

int main(int argc, char **argv)
{
    ros::init(argc, argv, "Mono");
    ros::start();

    if(argc != 3)
    {
        cerr << endl << "Usage: rosrun ORB_SLAM2 Mono path_to_vocabulary path_to_settings" << endl;        
        ros::shutdown();
        return 1;
    }    

    // Create SLAM system. It initializes all system threads and gets ready to process frames.
    ORB_SLAM2::System SLAM(argv[1],argv[2],ORB_SLAM2::System::MONOCULAR,true);

    ImageGrabber igb(&SLAM);

    ros::NodeHandle nodeHandler;
    ros::Subscriber sub = nodeHandler.subscribe("/camera/image_raw", 1, &ImageGrabber::GrabImage,&igb);

    ros::spin();

    // Stop all threads
    SLAM.Shutdown();

    // Save camera trajectory
    SLAM.SaveKeyFrameTrajectoryTUM("KeyFrameTrajectory.txt");

    ros::shutdown();

    return 0;
}


tf::Quaternion hamiltonProduct(tf::Quaternion a, tf::Quaternion b) {

    tf::Quaternion c;

        c[0] = (a[0]*b[0]) - (a[1]*b[1]) - (a[2]*b[2]) - (a[3]*b[3]);
        c[1] = (a[0]*b[1]) + (a[1]*b[0]) + (a[2]*b[3]) - (a[3]*b[2]);
        c[2] = (a[0]*b[2]) - (a[1]*b[3]) + (a[2]*b[0]) + (a[3]*b[1]);
        c[3] = (a[0]*b[3]) + (a[1]*b[2]) - (a[2]*b[1]) + (a[3]*b[0]);

    return c;
}

void ImageGrabber::GrabImage(const sensor_msgs::ImageConstPtr& msg)
{
    // Copy the ros image message to cv::Mat.
    cv_bridge::CvImageConstPtr cv_ptr;
    try
    {
        cv_ptr = cv_bridge::toCvShare(msg);
    }
    catch (cv_bridge::Exception& e)
    {
        ROS_ERROR("cv_bridge exception: %s", e.what());
        return;
    }

    // Relative pose from ORB_SLAMs TrackMonocular function (T)
    cv::Mat pose = mpSLAM->TrackMonocular(cv_ptr->image,cv_ptr->header.stamp.toSec());

    if (pose.empty())
        return;

    //Relative rotational matrix gotten from relative ORB_SLAM pose (R)
    tf::Matrix3x3 tf3d;
    tf3d.setValue(pose.at<float>(0,0), pose.at<float>(0,1), pose.at<float>(0,2),
            pose.at<float>(1,0), pose.at<float>(1,1), pose.at<float>(1,2),
            pose.at<float>(2,0), pose.at<float>(2,1), pose.at<float>(2,2));


    //Get the matrix tf3d (rotational matrix R) represented as a quaternion (q)
    tf::Quaternion tfqt;
    tf3d.getRotation(tfqt);

    //Change quaternion element order and inverts rotation(??)
    double aux = tfqt[0];
        tfqt[0]=-tfqt[2];
        tfqt[2]=tfqt[1];
        tfqt[1]=aux;


    //Rotated translation for camera (t_ish)
    tf::Vector3 origin;
    origin.setValue(pose.at<float>(0,3),pose.at<float>(1,3),pose.at<float>(2,3));


    //rotate 270deg about x and 270deg about x to get ENU: x forward, y left, z up (From NED to ENU)
    const tf::Matrix3x3 rotation270degXZ(   0, 1, 0,
                                            0, 0, 1,
                                           -1, 0, 0);

    //Actual translation for camera (t)
    tf::Vector3 translationForCamera = origin * rotation270degXZ;


    //Hamilton (Translation for world)
    tf::Quaternion quaternionForHamilton(tfqt[3], tfqt[0], tfqt[1], tfqt[2]);
    tf::Quaternion secondQuaternionForHamilton(tfqt[3], -tfqt[0], -tfqt[1], -tfqt[2]);
    tf::Quaternion translationHamilton(0, translationForCamera[0], translationForCamera[1], translationForCamera[2]);

    tf::Quaternion translationStepQuat;
    translationStepQuat = hamiltonProduct(hamiltonProduct(quaternionForHamilton, translationHamilton), secondQuaternionForHamilton);

    // translation of camera in reference to the world
    tf::Vector3 translation(translationStepQuat[1], translationStepQuat[2], translationStepQuat[3]);

    //Scaling
    //if(m_numScales > 0) {
    //    translation = m_scale * translation;
    //}

    //Set world
    //m_currentQ = tfqt;
    //m_currentT = translation;
    //translation = translation - m_worldT;
    //tfqt = tfqt * m_worldQ.inverse();


    //Creates tf::transform and populates it with translation (as a vector) and rotation (as a quaternion)
    tf::Transform transformCurrent;
    transformCurrent.setOrigin(translation); // sets translational element
    transformCurrent.setRotation(tfqt); // sets rotational element

    //Publishes transform
    static tf::TransformBroadcaster br;
    br.sendTransform(tf::StampedTransform(transformCurrent, ros::Time::now(), "world", "camera_pose"));
}