/**
 * @brief Attitude plugin
 * @file attitude.cpp
 * @author Andreas Antener <andreas@uaventure.com>
 * @author huang li long <huanglilongwk@outlook.com>
 * @time 2016/07/05
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

#include <mavros_msgs/Attitude.h>

namespace mavros {
namespace std_plugins {
/**
 * @brief Attitude plugin.
 */
class AttitudePlugin : public plugin::PluginBase {
public:
    AttitudePlugin() : PluginBase(),
        nh("~")
    { }

    /**
     * Plugin initializer. Constructor should not do this.
     */
    void initialize(UAS &uas_)
    {
        PluginBase::initialize(uas_);

        nh.param<std::string>("frame_id", frame_id, "map");
        attitude_pub = nh.advertise<mavros_msgs::Attitude>("attitude", 10);
    }

    Subscriptions get_subscriptions()
    {
        return {
            make_handler(&AttitudePlugin::handle_attitude),
        };
    }

private:
    ros::NodeHandle nh;
    std::string frame_id;

    ros::Publisher attitude_pub;

    void handle_attitude(const mavlink::mavlink_message_t *msg, mavlink::common::msg::ATTITUDE &attitude)
    {
        auto ros_msg = boost::make_shared<mavros_msgs::Attitude>();
        ros_msg->header = m_uas->synchronized_header(frame_id, attitude.time_boot_ms);
        
        ros_msg->roll        = attitude.roll;
        ros_msg->pitch       = attitude.pitch;
        ros_msg->yaw         = attitude.yaw;
        ros_msg->rollspeed   = attitude.rollspeed;
        ros_msg->pitchspeed  = attitude.pitchspeed;
        ros_msg->yawspeed    = attitude.yawspeed;

        attitude_pub.publish(ros_msg);
    }
};
}   // namespace std_plugins
}   // namespace mavros

#include <pluginlib/class_list_macros.h>
PLUGINLIB_EXPORT_CLASS(mavros::std_plugins::AttitudePlugin, mavros::plugin::PluginBase)
