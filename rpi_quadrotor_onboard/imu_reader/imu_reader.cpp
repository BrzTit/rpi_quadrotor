#include "ros/ros.h"
#include "std_msgs/String.h"

#include "driver_sparkfun6dof/sparkfun6dof.h"
#include "rpi_quadrotor_onboard/imu_data.h"

#include <iostream>
#include <sstream>

using namespace rpi_quadrotor_onboard;

int main (int argc, char ** argv) 
{
	ros::init(argc, argv, "imu_reader");
	ros::NodeHandle node;
	
	ros::Publisher imu_publisher = node.advertise<imu_data>("imu_data", 240);

	Sparkfun6DOF::imudata data;
	Sparkfun6DOF imu("/dev/tty.usbserial-A7005FSa");
	
	while (ros::ok()) {
		std::stringstream ss;
		imu_data msg;
		
		imu.getIMUData(data);
		memcpy(& msg.count, & data.count, 14);
		
		imu_publisher.publish(msg);
		
		ros::spinOnce();
		//loop_rate.sleep();
	}
	
	return 0;
}