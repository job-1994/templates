#include <ros/ros.h>
#include <templates/custom_srv.h>

class ServiceClient
{
public:
	ServiceClient(ros::NodeHandle nh);
	~ServiceClient();
	ros::ServiceServer service;
	bool cb(templates::custom_srv::Request& request, templates::custom_srv::Response& response);
};

ServiceClient::ServiceClient(ros::NodeHandle nh)
{
	service = nh.advertiseService("service_topic", &ServiceClient::cb, this);
}

ServiceClient::~ServiceClient(){}

bool ServiceClient::cb(templates::custom_srv::Request& request, templates::custom_srv::Response& response)
{
	response.out = request.in;
	return true;
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "ServiceClient");
  ros::NodeHandle nh;
  ServiceClient sc(nh);
  ros::spin();
}