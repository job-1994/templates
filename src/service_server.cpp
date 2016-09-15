#include <ros/ros.h>
#include <templates/custom_srv.h>

class ServiceServer
{
public:
	ServiceServer(ros::NodeHandle nh);
	~ServiceServer();
	ros::ServiceServer service;
	bool cb(templates::custom_srv::Request& request, templates::custom_srv::Response& response);
};

ServiceServer::ServiceServer(ros::NodeHandle nh)
{
	service = nh.advertiseService("service_topic", &ServiceServer::cb, this);
}

ServiceServer::~ServiceServer(){}

bool ServiceServer::cb(templates::custom_srv::Request& request, templates::custom_srv::Response& response)
{
	response.out = request.in;
	return true;
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "ServiceServer");
  ros::NodeHandle nh;
  ServiceServer sc(nh);
  ros::spin();
}