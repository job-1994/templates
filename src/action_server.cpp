#include <ros/ros.h>
#include <templates/custom_actionAction.h>
#include <actionlib/server/simple_action_server.h>

class ActionServer
{
public:
	ActionServer(ros::NodeHandle nh);
	~ActionServer();
	void goal_cb();
	void preempt_cb();
	void feedback_cb();
protected:
	actionlib::SimpleActionServer<templates::custom_actionAction> as;
	templates::custom_actionFeedback fb;
	templates::custom_actionResult rs;
};

ActionServer::ActionServer(ros::NodeHandle nh) : as(nh, "action_topic", false)
{
	as.registerGoalCallback(boost::bind(&ActionServer::goal_cb, this));
	as.registerPreemptCallback(boost::bind(&ActionServer::preempt_cb, this));
	as.start();
	ROS_INFO("Started Action Server");
}

ActionServer::~ActionServer(){}

void ActionServer::goal_cb()
{
	bool in = as.acceptNewGoal()->goal;
	ROS_INFO("Accepted Goal");
}

void ActionServer::preempt_cb()
{
	ROS_INFO("Preempted");
	as.setPreempted();
}

/*Subscribe to a topic and do the thing you want done, use
if()*/


int main(int argc, char** argv)
{
  ros::init(argc, argv, "Action_Server");

  ros::NodeHandle nh;

  ActionServer ac(nh);

  ros::spin();
}