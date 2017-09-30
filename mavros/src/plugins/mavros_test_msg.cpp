/**
 * @brief Mavros_test_msg plugin
 * @file mavros_test_msg.cpp
 * @author Andreas Antener <andreas@uaventure.com>
 * @author huang li long <huanglilongwk@outlook.com>
 * @time 2016/08/16
 * @addtogroup plugin
 * @{
 */
/*
 * Copyright 2015 Andreas Antener <andreas@uaventure.com>.
 *
 * This file is part of the mavros package and subject to the license terms
 * in the top-level LICENSE file of the mavros repository.
 * https://github.com/mavlink/mavros/tree/master/LICENSE.md
 */

#include <mavros/mavros_plugin.h>

#include <mavros_msgs/Mavros_test_msg.h>

namespace mavros {
namespace std_plugins {
/**
 * @brief Mavros_test_msg plugin.
 */
class Mavros_test_msgPlugin : public plugin::PluginBase {
public:
    Mavros_test_msgPlugin() : PluginBase(),
        nh("~")
    { }

    /**
     * Plugin initializer. Constructor should not do this.
     */
    void initialize(UAS &uas_)
    {
        PluginBase::initialize(uas_);

        nh.param<std::string>("frame_id", frame_id, "map");
        //mavros_msg_pub = nh.advertise<mavros_msgs::Mavros_test_msg>("mavros_test_msg", 10);
		mavros_msg_sub = nh.subscribe("mavros_test_msg", 10, &Mavros_test_msgPlugin::mavros_test_msg_cb, this);
    }

    Subscriptions get_subscriptions()
    {
        return {
            //make_handler(&Mavros_test_msgPlugin::handle_mavros_msg),
        };
    }

private:
    ros::NodeHandle nh;
    std::string frame_id;

    //ros::Publisher mavros_msg_pub;
	ros::Subscriber mavros_msg_sub;

    // void handle_mavros_msg(const mavlink::mavlink_message_t *msg, mavlink::pixhawk::msg::MAVROS_TEST_MSG &mavros_test_msg)
    // {
    //     auto ros_msg = boost::make_shared<mavros_msgs::Mavros_test_msg>();
    //     ros_msg->header = m_uas->synchronized_header(frame_id, mavros_test_msg.timestamp);
        
    //     ros_msg->test        = mavros_test_msg.test;
    //     mavros_msg_pub.publish(ros_msg);
    // }
	void mavros_test_msg_cb(const mavros_msgs::Mavros_test_msg::ConstPtr &req) {
		mavlink::pixhawk::msg::MAVROS_TEST_MSG test_msg{};
		test_msg.timestamp = ros::Time::now().toNSec() / 1000;
		test_msg.test = req->test;
		UAS_FCU(m_uas)->send_message_ignore_drop(test_msg);
	}
};
}   // namespace std_plugins
}   // namespace mavros

#include <pluginlib/class_list_macros.h>
PLUGINLIB_EXPORT_CLASS(mavros::std_plugins::Mavros_test_msgPlugin, mavros::plugin::PluginBase)