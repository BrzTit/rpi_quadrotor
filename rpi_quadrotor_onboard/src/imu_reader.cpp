#include "ros/ros.h"
#include "std_msgs/String.h"

#include <iostream>
#include <sstream>



int main (int argc, char ** argv) 
{
	int count = 0;
	
	ros::init(argc, argv, "imu_reader");
	ros::NodeHandle node;
	
	ros::Publisher imu_publisher = node.advertise<std_msgs::String>("imu_data", 240);
	
	ros::Rate loop_rate(10);
	
	while (ros::ok()) {
		std::stringstream ss;
		std_msgs::String msg;
		
		ss << "hey guys " << count++;
		msg.data = ss.str();
		
		imu_publisher.publish(msg);
		
		ros::spinOnce();
		loop_rate.sleep();
	}
	
	return 0;
}