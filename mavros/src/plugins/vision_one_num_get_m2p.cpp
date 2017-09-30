/**
* @file     : vision_one_num_get_m2p.cpp
* @brief    : vision_one_num_get_m2p plugin.
* @author   : libn
* @time     : Oct 2, 2016 9:28:19 AM
*/

#include <mavros/mavros_plugin.h>

#include <mavros_msgs/VISION_ONE_NUM_GET_M2P.h>

namespace mavros {
namespace std_plugins {
/**
 * @brief VisionOneNumGet plugin.
 */
class VISION_ONE_NUM_GET_M2PPlugin : public plugin::PluginBase {
public:
	VISION_ONE_NUM_GET_M2PPlugin() : PluginBase(),
        nh("~")
    { }

    /**
     * Plugin initializer. Constructor should not do this.
     */
    void initialize(UAS &uas_)
    {
        PluginBase::initialize(uas_);

        nh.param<std::string>("frame_id", frame_id, "map");
        //mavros_msg_pub = nh.advertise<mavros_msgs::VisionOneNumGet>("vision_one_num_get", 10);
		mavros_msg_sub = nh.subscribe("vision_one_num_get_m2p", 10, &VISION_ONE_NUM_GET_M2PPlugin::vision_one_num_get_m2p_cb, this);
    }

    Subscriptions get_subscriptions()
    {
        return {
            //make_handler(&VisionOneNumGetPlugin::handle_mavros_msg),
        };
    }

private:
    ros::NodeHandle nh;
    std::string frame_id;

    //ros::Publisher mavros_msg_pub;
	ros::Subscriber mavros_msg_sub;

    // void handle_mavros_msg(const mavlink::mavlink_message_t *msg, mavlink::pixhawk::msg::VISION_ONE_NUM_GET &vision_one_num_get)
    // {
    //     auto ros_msg = boost::make_shared<mavros_msgs::VisionOneNumGet>();

    //     ros_msg->header = m_uas->synchronized_header(frame_id, vision_one_num_get.timestamp);

	// 	ros_msg->loop_value 	= vision_one_num_get.loop_value;
	// 	ros_msg->num 			= vision_one_num_get.num;

    //     mavros_msg_pub.publish(ros_msg);
    // }
	void vision_one_num_get_m2p_cb(const mavros_msgs::VISION_ONE_NUM_GET_M2P::ConstPtr &req) {
		mavlink::pixhawk::msg::VISION_ONE_NUM_GET_M2P test_msg{};

//		test_msg.timestamp = ros::Time::now().toNSec() / 1000;

		test_msg.loop_value 	= req->loop_value;
		test_msg.num 			= req->num;

		UAS_FCU(m_uas)->send_message_ignore_drop(test_msg);
	}
};
}   // namespace std_plugins
}   // namespace mavros

#include <pluginlib/class_list_macros.h>
PLUGINLIB_EXPORT_CLASS(mavros::std_plugins::VISION_ONE_NUM_GET_M2PPlugin, mavros::plugin::PluginBase)
