/**
 * @brief 	: FixedTargetPositionP2M plugin
 * @file 	: fixed_target_position_p2m.cpp
 * @author 	: libn
 * @time 	: 2016/09/12
 */

#include <mavros/mavros_plugin.h>

#include <mavros_msgs/FIXED_TARGET_RETURN_M2P.h>

namespace mavros {
namespace std_plugins {
/**
 * @brief FixedTargetPositionM2P plugin.
 */
class FixedTargetReturnM2PPlugin : public plugin::PluginBase {
public:
	FixedTargetReturnM2PPlugin() : PluginBase(),
        nh("~")
    { }

    /**
     * Plugin initializer. Constructor should not do this.
     */
    void initialize(UAS &uas_)
    {
        PluginBase::initialize(uas_);

        nh.param<std::string>("frame_id", frame_id, "map");
//        mavros_msg_pub = nh.advertise<mavros_msgs::FIXED_TARGET_RETURN_M2P>("fixed_target_return_m2p", 10);
		mavros_msg_sub = nh.subscribe("fixed_target_return_m2p", 10, &FixedTargetReturnM2PPlugin::fixed_target_return_m2p_cb, this);
    }

    Subscriptions get_subscriptions()
    {
        return {
//            make_handler(&FixedTargetPositionP2MPlugin::handle_mavros_msg),
        };
    }

private:
    ros::NodeHandle nh;
    std::string frame_id;

//    ros::Publisher mavros_msg_pub;
	ros::Subscriber mavros_msg_sub;

	 void fixed_target_return_m2p_cb(const mavros_msgs::FIXED_TARGET_RETURN_M2P::ConstPtr &req)
	 {
	 	mavlink::pixhawk::msg::FIXED_TARGET_RETURN_M2P test_msg{};

//	 	test_msg.timestamp = ros::Time::now().toNSec() / 1000;

	 	test_msg.home_x        	= req->home_x;
	 	test_msg.home_y        	= req->home_y;
	 	test_msg.home_z        	= req->home_z;

	 	test_msg.observe_x        = req->observe_x;
	 	test_msg.observe_y        = req->observe_y;
	 	test_msg.observe_z        = req->observe_z;

	 	test_msg.spray_left_x     = req->spray_left_x;
	 	test_msg.spray_left_y     = req->spray_left_y;
	 	test_msg.spray_left_z     = req->spray_left_z;

	 	test_msg.spray_right_x    = req->spray_right_x;
	 	test_msg.spray_right_y    = req->spray_right_y;
	 	test_msg.spray_right_z    = req->spray_right_z;

	 	UAS_FCU(m_uas)->send_message_ignore_drop(test_msg);
	 }
};
}   // namespace std_plugins
}   // namespace mavros

#include <pluginlib/class_list_macros.h>
PLUGINLIB_EXPORT_CLASS(mavros::std_plugins::FixedTargetReturnM2PPlugin, mavros::plugin::PluginBase)
