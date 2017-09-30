/**
* @file     : vision_num_scan_m2p.cpp
* @brief    : vision_num_scan_m2p plugin.
* @author   : libn
* @time     : Oct 2, 2016 9:10:59 AM
*/

#include <mavros/mavros_plugin.h>

#include <mavros_msgs/VISION_NUM_SCAN_M2P.h>

namespace mavros {
namespace std_plugins {
/**
 * @brief VisionNumScan plugin.
 */
class VISION_NUM_SCAN_M2PPlugin : public plugin::PluginBase {
public:
	VISION_NUM_SCAN_M2PPlugin() : PluginBase(),
        nh("~")
    { }

    /**
     * Plugin initializer. Constructor should not do this.
     */
    void initialize(UAS &uas_)
    {
        PluginBase::initialize(uas_);

        nh.param<std::string>("frame_id", frame_id, "map");
        //mavros_msg_pub = nh.advertise<mavros_msgs::VisionNumScan>("vision_num_scan", 10);
		mavros_msg_sub = nh.subscribe("vision_num_scan_m2p", 10, &VISION_NUM_SCAN_M2PPlugin::vision_num_scan_m2p_cb, this);
    }

    Subscriptions get_subscriptions()
    {
        return {
            //make_handler(&VisionNumScanPlugin::handle_mavros_msg),
        };
    }

private:
    ros::NodeHandle nh;
    std::string frame_id;

    //ros::Publisher mavros_msg_pub;
	ros::Subscriber mavros_msg_sub;

    // void handle_mavros_msg(const mavlink::mavlink_message_t *msg, mavlink::pixhawk::msg::VISION_NUM_SCAN &vision_num_scan)
    // {
    //     auto ros_msg = boost::make_shared<mavros_msgs::VisionNumScan>();

    //     ros_msg->header = m_uas->synchronized_header(frame_id, vision_num_scan.timestamp);

	// 	ros_msg->board_num 		= vision_num_scan.board_num;
	// 	ros_msg->board_x 		= vision_num_scan.board_x;
	// 	ros_msg->board_y 		= vision_num_scan.board_y;
	// 	ros_msg->board_z 		= vision_num_scan.board_z;
	// 	ros_msg->board_valid 	= vision_num_scan.board_valid;

    //     mavros_msg_pub.publish(ros_msg);
    // }
	void vision_num_scan_m2p_cb(const mavros_msgs::VISION_NUM_SCAN_M2P::ConstPtr &req) {
		mavlink::pixhawk::msg::VISION_NUM_SCAN_M2P test_msg{};

//		test_msg.timestamp = ros::Time::now().toNSec() / 1000;

		test_msg.board_num 		= req->board_num;
		test_msg.board_x 		= req->board_x;
		test_msg.board_y 		= req->board_y;
		test_msg.board_z 		= req->board_z;
		test_msg.board_valid 	= req->board_valid;

		UAS_FCU(m_uas)->send_message_ignore_drop(test_msg);
	}
};
}   // namespace std_plugins
}   // namespace mavros

#include <pluginlib/class_list_macros.h>
PLUGINLIB_EXPORT_CLASS(mavros::std_plugins::VISION_NUM_SCAN_M2PPlugin, mavros::plugin::PluginBase)
