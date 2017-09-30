/**
 * @brief 	: TaskStatusChange plugin
 * @file 	: task_status_change.cpp
 * @author 	: huang li long <huanglilongwk@outlook.com>
 * @time 	: 2016/09/12
 */

#include <mavros/mavros_plugin.h>

#include <mavros_msgs/TaskStatusChange.h>

namespace mavros {
namespace std_plugins {
/**
 * @brief TaskStatusChange plugin.
 */
class TaskStatusChangePlugin : public plugin::PluginBase {
public:
    TaskStatusChangePlugin() : PluginBase(),
        nh("~")
    { }

    /**
     * Plugin initializer. Constructor should not do this.
     */
    void initialize(UAS &uas_)
    {
        PluginBase::initialize(uas_);

        nh.param<std::string>("frame_id", frame_id, "map");
        mavros_msg_pub = nh.advertise<mavros_msgs::TaskStatusChange>("task_status_change", 10);
		//mavros_msg_sub = nh.subscribe("task_status_change", 10, &TaskStatusChangePlugin::task_status_change_cb, this);
    }

    Subscriptions get_subscriptions()
    {
        return {
            make_handler(&TaskStatusChangePlugin::handle_mavros_msg),
        };
    }

private:
    ros::NodeHandle nh;
    std::string frame_id;

    ros::Publisher mavros_msg_pub;
	//ros::Subscriber mavros_msg_sub;

    void handle_mavros_msg(const mavlink::mavlink_message_t *msg, mavlink::pixhawk::msg::TASK_STATUS_CHANGE &task_status_change)
    {
        auto ros_msg = boost::make_shared<mavros_msgs::TaskStatusChange>();

        //ros_msg->header = m_uas->synchronized_header(frame_id, task_status_change.timestamp);
        
        ros_msg->num_odd_even      = task_status_change.num_odd_even;
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
PLUGINLIB_EXPORT_CLASS(mavros::std_plugins::TaskStatusChangePlugin, mavros::plugin::PluginBase)