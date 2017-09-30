/**
 * @brief Mavros_msg plugin
 * @file mavros_msg.cpp
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

#include <mavros_msgs/Mavros_msg.h>

namespace mavros {
namespace std_plugins {
/**
 * @brief Mavros_msg plugin.
 */
class Mavros_msgPlugin : public plugin::PluginBase {
public:
    Mavros_msgPlugin() : PluginBase(),
        nh("~")
    { }

    /**
     * Plugin initializer. Constructor should not do this.
     */
    void initialize(UAS &uas_)
    {
        PluginBase::initialize(uas_);

        nh.param<std::string>("frame_id", frame_id, "map");
        mavros_msg_pub = nh.advertise<mavros_msgs::Mavros_msg>("mavros_msg", 10);
    }

    Subscriptions get_subscriptions()
    {
        return {
            make_handler(&Mavros_msgPlugin::handle_mavros_msg),
        };
    }

private:
    ros::NodeHandle nh;
    std::string frame_id;

    ros::Publisher mavros_msg_pub;

    void handle_mavros_msg(const mavlink::mavlink_message_t *msg, mavlink::pixhawk::msg::MAVROS_MSG &mavros_msg)
    {
        auto ros_msg = boost::make_shared<mavros_msgs::Mavros_msg>();
        ros_msg->header = m_uas->synchronized_header(frame_id, mavros_msg.timestamp);
        
        ros_msg->test        = mavros_msg.test;
        mavros_msg_pub.publish(ros_msg);
    }
};
}   // namespace std_plugins
}   // namespace mavros

#include <pluginlib/class_list_macros.h>
PLUGINLIB_EXPORT_CLASS(mavros::std_plugins::Mavros_msgPlugin, mavros::plugin::PluginBase)
