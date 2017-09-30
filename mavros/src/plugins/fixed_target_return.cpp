/**
 * @brief 	: FixedTargetReturn plugin
 * @file 	: fixed_target_return.cpp
 * @author 	: huang li long <huanglilongwk@outlook.com>
 * @time 	: 2016/09/12
 */

#include <mavros/mavros_plugin.h>

#include <mavros_msgs/FixedTargetReturn.h>

namespace mavros {
namespace std_plugins {
/**
 * @brief FixedTargetReturn plugin.
 */
class FixedTargetReturnPlugin : public plugin::PluginBase {
public:
    FixedTargetReturnPlugin() : PluginBase(),
        nh("~")
    { }

    /**
     * Plugin initializer. Constructor should not do this.
     */
    void initialize(UAS &uas_)
    {
        PluginBase::initialize(uas_);

        nh.param<std::string>("frame_id", frame_id, "map");
        mavros_msg_pub = nh.advertise<mavros_msgs::FixedTargetReturn>("fixed_target_return", 10);
		//mavros_msg_sub = nh.subscribe("fixed_target_return", 10, &FixedTargetReturnPlugin::fixed_target_return_cb, this);
    }

    Subscriptions get_subscriptions()
    {
        return {
            make_handler(&FixedTargetReturnPlugin::handle_mavros_msg),
        };
    }

private:
    ros::NodeHandle nh;
    std::string frame_id;

    ros::Publisher mavros_msg_pub;
	//ros::Subscriber mavros_msg_sub;

    void handle_mavros_msg(const mavlink::mavlink_message_t *msg, mavlink::pixhawk::msg::FIXED_TARGET_RETURN &fixed_target_return)
    {
        auto ros_msg = boost::make_shared<mavros_msgs::FixedTargetReturn>();

        ros_msg->header = m_uas->synchronized_header(frame_id, fixed_target_return.timestamp);
        
        ros_msg->home_lat        	= fixed_target_return.home_lat;
		ros_msg->home_lon        	= fixed_target_return.home_lon;
		ros_msg->home_alt        	= fixed_target_return.home_alt;

		ros_msg->observe_lat        = fixed_target_return.observe_lat;
		ros_msg->observe_lon        = fixed_target_return.observe_lon;
		ros_msg->observe_alt        = fixed_target_return.observe_alt;

		ros_msg->spray_left_lat     = fixed_target_return.spray_left_lat;
		ros_msg->spray_left_lon     = fixed_target_return.spray_left_lon;
		ros_msg->spray_left_alt     = fixed_target_return.spray_left_alt;

		ros_msg->spray_right_lat    = fixed_target_return.spray_right_lat;
		ros_msg->spray_right_lon    = fixed_target_return.spray_right_lon;
		ros_msg->spray_right_alt    = fixed_target_return.spray_right_alt;

        mavros_msg_pub.publish(ros_msg);
    }
	// void fixed_target_return_cb(const mavros_msgs::FixedTargetReturn::ConstPtr &req) {
	// 	mavlink::pixhawk::msg::FIXED_TARGET_RETURN test_msg{};

	// 	test_msg.timestamp = ros::Time::now().toNSec() / 1000;

	// 	test_msg.home_lat        	 = req->home_lat;
	// 	test_msg.home_lon        	 = req->home_lon;
	// 	test_msg.home_alt        	 = req->home_alt;

	// 	test_msg.observe_lat        = req->observe_lat;
	// 	test_msg.observe_lon        = req->observe_lon;
	// 	test_msg.observe_alt        = req->observe_alt;

	// 	test_msg.spray_left_lat     = req->spray_left_lat;
	// 	test_msg.spray_left_lon     = req->spray_left_lon;
	// 	test_msg.spray_left_alt     = req->spray_left_alt;

	// 	test_msg.spray_right_lat    = req->spray_right_lat;
	// 	test_msg.spray_right_lon    = req->spray_right_lon;
	// 	test_msg.spray_right_alt    = req->spray_right_alt;
		
	// 	UAS_FCU(m_uas)->send_message_ignore_drop(test_msg);
	// }
};
}   // namespace std_plugins
}   // namespace mavros

#include <pluginlib/class_list_macros.h>
PLUGINLIB_EXPORT_CLASS(mavros::std_plugins::FixedTargetReturnPlugin, mavros::plugin::PluginBase)