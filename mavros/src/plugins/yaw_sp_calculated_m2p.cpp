/**
* @file     : yaw_sp_calculated_m2p.cpp
* @brief    : yaw_sp_calculated_m2p plugin.
* @author   : libn
* @time     : Oct 2, 2016 9:41:15 AM
*/

#include <mavros/mavros_plugin.h>

#include <mavros_msgs/YAW_SP_CALCULATED_M2P.h>

namespace mavros {
namespace std_plugins {
/**
 * @brief YawSpCalculated plugin.
 */
class YAW_SP_CALCULATED_M2PPlugin : public plugin::PluginBase {
public:
	YAW_SP_CALCULATED_M2PPlugin() : PluginBase(),
        nh("~")
    { }

    /**
     * Plugin initializer. Constructor should not do this.
     */
    void initialize(UAS &uas_)
    {
        PluginBase::initialize(uas_);

        nh.param<std::string>("frame_id", frame_id, "map");
        //mavros_msg_pub = nh.advertise<mavros_msgs::YawSpCalculated>("yaw_sp_calculated", 10);
		mavros_msg_sub = nh.subscribe("yaw_sp_calculated_m2p", 10, &YAW_SP_CALCULATED_M2PPlugin::yaw_sp_calculated_m2p_cb, this);
    }

    Subscriptions get_subscriptions()
    {
        return {
            //make_handler(&YawSpCalculatedPlugin::handle_mavros_msg),
        };
    }

private:
    ros::NodeHandle nh;
    std::string frame_id;

    //ros::Publisher mavros_msg_pub;
	ros::Subscriber mavros_msg_sub;

    // void handle_mavros_msg(const mavlink::mavlink_message_t *msg, mavlink::pixhawk::msg::YAW_SP_CALCULATED &yaw_sp_calculated)
    // {
    //     auto ros_msg = boost::make_shared<mavros_msgs::YawSpCalculated>();

    //     ros_msg->header = m_uas->synchronized_header(frame_id, yaw_sp_calculated.timestamp);
    //     ros_msg->yaw_sp        = yaw_sp_calculated.yaw_sp;

    //     mavros_msg_pub.publish(ros_msg);
    // }
	void yaw_sp_calculated_m2p_cb(const mavros_msgs::YAW_SP_CALCULATED_M2P::ConstPtr &req) {
		mavlink::pixhawk::msg::YAW_SP_CALCULATED_M2P test_msg{};

//		test_msg.timestamp = ros::Time::now().toNSec() / 1000;
		test_msg.yaw_sp = req->yaw_sp;

		UAS_FCU(m_uas)->send_message_ignore_drop(test_msg);
	}
};
}   // namespace std_plugins
}   // namespace mavros

#include <pluginlib/class_list_macros.h>
PLUGINLIB_EXPORT_CLASS(mavros::std_plugins::YAW_SP_CALCULATED_M2PPlugin, mavros::plugin::PluginBase)
