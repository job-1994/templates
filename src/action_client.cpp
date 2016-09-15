#include <ros/ros.h>
#include <templates/custom_actionAction.h>
#include <actionlib/client/simple_action_client.h>

typedef actionlib::SimpleActionClient<templates::custom_actionAction> Client;

class ActionClient
{
public:
	ActionClient(ros::NodeHandle nh);
	~ActionClient();
protected:
	Client ac;

};

ActionClient::ActionClient(ros::NodeHandle nh) : ac("action_topic", true)
{
	ROS_INFO("Waiting for server");
	ac.waitForServer();
	ROS_INFO("Reached server");

	templates::custom_actionGoal goal;
	goal.goal = true;
	ac.sendGoal(goal);
	ros::Duration(2).sleep();
	ac.cancelAllGoals();
}

ActionClient::~ActionClient(){}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "Action_Client");
  ros::NodeHandle nh;
  ActionClient acl(nh);
  ros::spin();
}