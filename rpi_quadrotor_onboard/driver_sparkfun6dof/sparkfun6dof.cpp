#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>

#include "sparkfun6dof.h"

Sparkfun6DOF::Sparkfun6DOF(const char * file) 
{
	fd = open(file, O_RDWR | O_NOCTTY | O_NDELAY);
	if (fd == -1) return;
	
	options = new struct termios();
	
	//115200/8/1/N
	tcgetattr(fd, options);
	
	cfsetispeed(options, B115200);
	cfsetospeed(options, B115200);
	
	options->c_cflag &= ~PARENB;
	options->c_cflag &= ~CSTOPB;
	options->c_cflag &= ~CSIZE; 
	options->c_cflag |= CS8;    
	
	tcsetattr(fd, TCSANOW, options);
}

Sparkfun6DOF::~Sparkfun6DOF() 
{
	close(fd);
}
