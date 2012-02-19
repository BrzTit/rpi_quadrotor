#include "ros/ros.h"
#include "std_msgs/String.h"

#include "driver_sparkfun6dof/sparkfun6dof.h"

#include <iostream>
#include <sstream>



int main (int argc, char ** argv) 
{
	ros::init(argc, argv, "imu_reader");
	ros::NodeHandle node;
	
	ros::Publisher imu_publisher = node.advertise<std_msgs::String>("imu_data", 240);
	
	//ros::Rate loop_rate(10);
	
	Sparkfun6DOF::imudata data;
	Sparkfun6DOF imu("/dev/tty.usbserial-A7005FSa");
	
	while (ros::ok()) {
		std::stringstream ss;
		std_msgs::String msg;
		
		imu.getIMUData(data);
		
		ss << "hey guys " << data.count;
		msg.data = ss.str();
		
		imu_publisher.publish(msg);
		
		ros::spinOnce();
		//loop_rate.sleep();
	}
	
	return 0;
}