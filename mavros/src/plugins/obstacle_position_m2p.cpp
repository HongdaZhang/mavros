/**
* @file     : obstacle_position_m2p.cpp
* @brief    : obstacle_position_m2p plugin.
* @author   : libn
* @time     : Sep 30, 2016 9:21:42 AM
*/

#include <mavros/mavros_plugin.h>

#include <mavros_msgs/OBSTACLE_POSITION_M2P.h>

namespace mavros {
namespace std_plugins {
/**
 * @brief ObstaclePosition plugin.
 */
class ObstaclePositionM2PPlugin : public plugin::PluginBase {
public:
	ObstaclePositionM2PPlugin() : PluginBase(),
        nh("~")
    { }

    /**
     * Plugin initializer. Constructor should not do this.
     */
    void initialize(UAS &uas_)
    {
        PluginBase::initialize(uas_);

        nh.param<std::string>("frame_id", frame_id, "map");
//        mavros_msg_pub = nh.advertise<mavros_msgs::OBSTACLE_POSITION_M2P>("obstacle_position", 10);
		mavros_msg_sub = nh.subscribe("obstacle_position_m2p", 10, &ObstaclePositionM2PPlugin::obstacle_position_m2p_cb, this);
    }

    Subscriptions get_subscriptions()
    {
        return {
//            make_handler(&ObstaclePositionPlugin::handle_mavros_msg),
        };
    }

private:
    ros::NodeHandle nh;
    std::string frame_id;

//    ros::Publisher mavros_msg_pub;
	ros::Subscriber mavros_msg_sub;

//     void handle_mavros_msg(const mavlink::mavlink_message_t *msg, mavlink::pixhawk::msg::OBSTACLE_POSITION &obstacle_position)
//     {
//         auto ros_msg = boost::make_shared<mavros_msgs::ObstaclePosition>();
//
//         ros_msg->header = m_uas->synchronized_header(frame_id, obstacle_position.timestamp);
//
//	 	ros_msg->obstacle_x 	= obstacle_position.obstacle_x;
//	 	ros_msg->obstacle_y 	= obstacle_position.obstacle_y;
//	 	ros_msg->obstacle_z 	= obstacle_position.obstacle_z;
//	 	ros_msg->obstacle_valid = obstacle_position.obstacle_valid;
//
//         mavros_msg_pub.publish(ros_msg);
//     }
	void obstacle_position_m2p_cb(const mavros_msgs::OBSTACLE_POSITION_M2P::ConstPtr &req) {
		mavlink::pixhawk::msg::OBSTACLE_POSITION_M2P test_msg{};

//		test_msg.timestamp = ros::Time::now().toNSec() / 1000;

		test_msg.obstacle_x 	= req->obstacle_x;
		test_msg.obstacle_y 	= req->obstacle_y;
		test_msg.obstacle_z 	= req->obstacle_z;
		test_msg.obstacle_valid = req->obstacle_valid;

		UAS_FCU(m_uas)->send_message_ignore_drop(test_msg);
	}
};
}   // namespace std_plugins
}   // namespace mavros

#include <pluginlib/class_list_macros.h>
PLUGINLIB_EXPORT_CLASS(mavros::std_plugins::ObstaclePositionM2PPlugin, mavros::plugin::PluginBase)
