cmake_minimum_required(VERSION 2.4.6)
include($ENV{ROS_ROOT}/core/rosbuild/rosbuild.cmake)

# Set the build type.  Options are:
#  Coverage       : w/ debug symbols, w/o optimization, w/ code-coverage
#  Debug          : w/ debug symbols, w/o optimization
#  Release        : w/o debug symbols, w/ optimization
#  RelWithDebInfo : w/ debug symbols, w/ optimization
#  MinSizeRel     : w/o debug symbols, w/ optimization, stripped binaries
#set(ROS_BUILD_TYPE RelWithDebInfo)

rosbuild_init()

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

#rosbuild_genmsg()
#rosbuild_gensrv()

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}
)
rosbuild_add_boost_directories()

rosbuild_add_library(sparkfun6dof 
	driver_sparkfun6dof/sparkfun6dof.cpp driver_sparkfun6dof/sparkfun6dof.h
	)
#target_link_libraries(sparkfun6dof ...)	
rosbuild_link_boost(sparkfun6dof thread)
	
rosbuild_add_executable(imu_reader imu_reader/imu_reader.cpp)
target_link_libraries(
	imu_reader
	sparkfun6dof
)
