/**
* @file     : task_status_change_p2m.cpp
* @brief    : task_status_change_p2m plugin
* @author   : libn
* @time     : Sep 30, 2016 9:47:45 AM
*/

#include <mavros/mavros_plugin.h>

#include <mavros_msgs/TASK_STATUS_CHANGE_P2M.h>

namespace mavros {
namespace std_plugins {
/**
 * @brief TaskStatusChange plugin.
 */
class TaskStatusChangeP2MPlugin : public plugin::PluginBase {
public:
	TaskStatusChangeP2MPlugin() : PluginBase(),
        nh("~")
    { }

    /**
     * Plugin initializer. Constructor should not do this.
     */
    void initialize(UAS &uas_)
    {
        PluginBase::initialize(uas_);

        nh.param<std::string>("frame_id", frame_id, "map");
        mavros_msg_pub = nh.advertise<mavros_msgs::TASK_STATUS_CHANGE_P2M>("task_status_change_p2m", 10);
		//mavros_msg_sub = nh.subscribe("task_status_change", 10, &TaskStatusChangePlugin::task_status_change_cb, this);
    }

    Subscriptions get_subscriptions()
    {
        return {
            make_handler(&TaskStatusChangeP2MPlugin::handle_mavros_msg),
        };
    }

private:
    ros::NodeHandle nh;
    std::string frame_id;

    ros::Publisher mavros_msg_pub;
	//ros::Subscriber mavros_msg_sub;

    void handle_mavros_msg(const mavlink::mavlink_message_t *msg, mavlink::pixhawk::msg::TASK_STATUS_CHANGE_P2M &task_status_change)
    {
        auto ros_msg = boost::make_shared<mavros_msgs::TASK_STATUS_CHANGE_P2M>();

//        ros_msg->header = m_uas->synchronized_header(frame_id, task_status_change.timestamp);

        ros_msg->spray_duration      = task_status_change.spray_duration;
		ros_msg->task_status       = task_status_change.task_status;
		ros_msg->loop_value        = task_status_change.loop_value;

        mavros_msg_pub.publish(ros_msg);
    }
	// void task_status_change_cb(const mavros_msgs::TaskStatusChange::ConstPtr &req) {
	// 	mavlink::pixhawk::msg::TASK_STATUS_CHANGE test_msg{};

	// 	test_msg.timestamp = ros::Time::now().toNSec() / 1000;

	// 	test_msg.num_odd_even      = req->num_odd_even;
	// 	test_msg.task_status       = req->task_status;
	// 	test_msg.loop_value        = req->loop_value;

	// 	UAS_FCU(m_uas)->send_message_ignore_drop(test_msg);
	// }
};
}   // namespace std_plugins
}   // namespace mavros

#include <pluginlib/class_list_macros.h>
PLUGINLIB_EXPORT_CLASS(mavros::std_plugins::TaskStatusChangeP2MPlugin, mavros::plugin::PluginBase)
