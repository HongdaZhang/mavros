/**
* @file  offb_node.cpp
* @brief offboard example node, written with mavros version 0.14.2,
*  		 px4 flight stack and tested in Gazebo SITL
*  		 this example code copy from http://dev.px4.io/ros-mavros-offboard.html
*/

#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/State.h>
#include <mavros_msgs/Attitude.h>
//#include <mavros_msgs/Mavros_test_msg.h>
//#include <mavros_msgs/FixedTargetPosition.h>

#include <mavros/frame_tf.h>

mavros_msgs::State current_state;
void state_cb(const mavros_msgs::State::ConstPtr& msg){
    current_state = *msg;
}

mavros_msgs::Attitude att;
void att_cb(const mavros_msgs::Attitude::ConstPtr& msg){
    att = *msg;
    //ROS_INFO("Attitude roll: %f", att.roll);
}

//mavros_msgs::Mavros_test_msg msg_test;
//void mavros_msg_cb(const mavros_msgs::Mavros_test_msg::ConstPtr& msg){
//	msg_test = *msg;
//	ROS_INFO("mavros_msg test: %f", msg_test.test);
//}
//
//mavros_msgs::FixedTargetPosition fix_pos;
//void fixed_target_position_cb(const mavros_msgs::FixedTargetPosition::ConstPtr& msg){
//	fix_pos = *msg;
//	ROS_INFO("mavros_msg test: %f", fix_pos.home_alt);
//}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "offb_node");
    ros::NodeHandle nh;

    ros::Subscriber state_sub = nh.subscribe<mavros_msgs::State>("mavros/state", 10, state_cb);

//	ros::Subscriber test_msg_sub = nh.subscribe<mavros_msgs::Mavros_test_msg>("mavros/mavros_test_msg", 10, mavros_msg_cb);

//	ros::Subscriber fix_pos_sub  = nh.subscribe<mavros_msgs::FixedTargetPosition>("mavros/fixed_target_position", 10, fixed_target_position_cb);

    ros::Subscriber att_sub = nh.subscribe<mavros_msgs::Attitude>("mavros/attitude", 10, att_cb);

    ros::Publisher local_pos_pub = nh.advertise<geometry_msgs::PoseStamped>("mavros/setpoint_position/local", 10);
    ros::ServiceClient arming_client = nh.serviceClient<mavros_msgs::CommandBool>("mavros/cmd/arming");
    ros::ServiceClient set_mode_client = nh.serviceClient<mavros_msgs::SetMode>("mavros/set_mode");

    //the setpoint publishing rate MUST be faster than 2Hz
    ros::Rate rate(20.0);

    // wait for FCU connection
    while(ros::ok() && !current_state.connected){
        ros::spinOnce();
        rate.sleep();
    }
    
    geometry_msgs::PoseStamped pose;
    pose.pose.position.x = 0;
    pose.pose.position.y = 0;
    pose.pose.position.z = 2;

	auto quat_yaw = mavros::ftf::quaternion_from_rpy(0.0, 0.0, 3.14);
	pose.pose.orientation.x = quat_yaw.x();
	pose.pose.orientation.y = quat_yaw.y();
	pose.pose.orientation.z = quat_yaw.z();
	pose.pose.orientation.w = quat_yaw.w();

    //send a few setpoints before starting
    for(int i = 100; ros::ok() && i > 0; --i){
        local_pos_pub.publish(pose);
        ros::spinOnce();
        rate.sleep();
    }

    mavros_msgs::SetMode offb_set_mode;
    offb_set_mode.request.custom_mode = "OFFBOARD";

    mavros_msgs::CommandBool arm_cmd;
    arm_cmd.request.value = true;

    ros::Time last_request = ros::Time::now();

    while(ros::ok()){

        local_pos_pub.publish(pose);

        ros::spinOnce();
        rate.sleep();
    }

    return 0;
}
