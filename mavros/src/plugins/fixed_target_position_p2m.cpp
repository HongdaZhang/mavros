/**
 * @brief 	: FixedTargetPositionP2M plugin
 * @file 	: fixed_target_position_p2m.cpp
 * @author 	: libn
 * @time 	: 2016/09/12
 */

#include <mavros/mavros_plugin.h>

#include <mavros_msgs/FIXED_TARGET_POSITION_P2M.h>

namespace mavros {
namespace std_plugins {
/**
 * @brief FixedTargetPositionP2M plugin.
 */
class FixedTargetPositionP2MPlugin : public plugin::PluginBase {
public:
    FixedTargetPositionP2MPlugin() : PluginBase(),
        nh("~")
    { }

    /**
     * Plugin initializer. Constructor should not do this.
     */
    void initialize(UAS &uas_)
    {
        PluginBase::initialize(uas_);

        nh.param<std::string>("frame_id", frame_id, "map");
        mavros_msg_pub = nh.advertise<mavros_msgs::FIXED_TARGET_POSITION_P2M>("fixed_target_position_p2m", 10);
//		mavros_msg_sub = nh.subscribe("fixed_target_position_p2m", 10, &FixedTargetPositionP2MPlugin::fixed_target_position_cb, this);
    }

    Subscriptions get_subscriptions()
    {
        return {
            make_handler(&FixedTargetPositionP2MPlugin::handle_mavros_msg),
        };
    }

private:
    ros::NodeHandle nh;
    std::string frame_id;

    ros::Publisher mavros_msg_pub;
//	ros::Subscriber mavros_msg_sub;

    void handle_mavros_msg(const mavlink::mavlink_message_t *msg, mavlink::pixhawk::msg::FIXED_TARGET_POSITION_P2M &fixed_target_position_p2m)
    {
        auto ros_msg = boost::make_shared<mavros_msgs::FIXED_TARGET_POSITION_P2M>();

        //ros_msg->header = m_uas->synchronized_header(frame_id, fixed_target_position_p2m.timestamp);

        ros_msg->home_x        = fixed_target_position_p2m.home_x;
		ros_msg->home_y        = fixed_target_position_p2m.home_y;
		ros_msg->home_z        = fixed_target_position_p2m.home_z;

		ros_msg->observe_x     = fixed_target_position_p2m.observe_x;
		ros_msg->observe_y     = fixed_target_position_p2m.observe_y;
		ros_msg->observe_z     = fixed_target_position_p2m.observe_z;

		ros_msg->spray_left_x  = fixed_target_position_p2m.spray_left_x;
		ros_msg->spray_left_y  = fixed_target_position_p2m.spray_left_y;
		ros_msg->spray_left_z  = fixed_target_position_p2m.spray_left_z;

		ros_msg->spray_right_x = fixed_target_position_p2m.spray_right_x;
		ros_msg->spray_right_y = fixed_target_position_p2m.spray_right_y;
		ros_msg->spray_right_z = fixed_target_position_p2m.spray_right_z;

        mavros_msg_pub.publish(ros_msg);
    }
//	 void fixed_target_position_cb(const mavros_msgs::FIXED_TARGET_POSITION_P2M::ConstPtr &req)
//	 {
//	 	mavlink::pixhawk::msg::FIXED_TARGET_POSITION_P2M test_msg{};
//
////	 	test_msg.timestamp = ros::Time::now().toNSec() / 1000;
//
//	 	test_msg.home_lat        	= req->home_lat;
//	 	test_msg.home_lon        	= req->home_lon;
//	 	test_msg.home_alt        	= req->home_alt;
//
//	 	test_msg.observe_lat        = req->observe_lat;
//	 	test_msg.observe_lon        = req->observe_lon;
//	 	test_msg.observe_alt        = req->observe_alt;
//
//	 	test_msg.spray_left_lat     = req->spray_left_lat;
//	 	test_msg.spray_left_lon     = req->spray_left_lon;
//	 	test_msg.spray_left_alt     = req->spray_left_alt;
//
//	 	test_msg.spray_right_lat    = req->spray_right_lat;
//	 	test_msg.spray_right_lon    = req->spray_right_lon;
//	 	test_msg.spray_right_alt    = req->spray_right_alt;
//
//	 	UAS_FCU(m_uas)->send_message_ignore_drop(test_msg);
//	 }
};
}   // namespace std_plugins
}   // namespace mavros

#include <pluginlib/class_list_macros.h>
PLUGINLIB_EXPORT_CLASS(mavros::std_plugins::FixedTargetPositionP2MPlugin, mavros::plugin::PluginBase)
