#include <cstdio>
#include <ctype.h>

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>

#include "sparkfun6dof.h"

Sparkfun6DOF::Sparkfun6DOF(const char * file) 
{
	fd = open(file, O_RDWR | O_NOCTTY | O_NDELAY);
	if (fd < 0) {
		printf("Error opening file\n");
		return;
	}
	
	printf("%d\n", fd);
	
	options = new struct termios();
	
	tcgetattr(fd, options);
	
	cfsetispeed(options, B115200);
	cfsetospeed(options, B115200);
	
	options->c_cflag &= ~PARENB;
	options->c_cflag &= ~CSTOPB;
	options->c_cflag &= ~CSIZE; 
	options->c_cflag |= CS8;    
	
	tcsetattr(fd, TCSANOW, options);
	fcntl(fd, F_SETFL, 0);
	
	f = fdopen(fd, "rw");
}

Sparkfun6DOF::~Sparkfun6DOF() 
{
	close(fd);
}

void Sparkfun6DOF::start()
{
	
}

void Sparkfun6DOF::stop() 
{
	
}

void Sparkfun6DOF::setAccelSensitivity(AccelSensitivity sensitivity)
{
	
}

void Sparkfun6DOF::setSampleFrequency(SampleFrequency frequency)
{
	
}

void Sparkfun6DOF::shortswap(unsigned short & v) 
{
	v = (v << 8) | (v >> 8);
}

void Sparkfun6DOF::getIMUData(imudata & buf)
{
	char buf2[65];
	buf2[64] = 0;

	int lastfound = 0;
	
	/*
		Note:  If the user is dicking around with the serial connection,
		there can be framing errors with the imudata struct.  Therefore, there
		is some logic here to correct for such framing errors.
	*/
	fread(&	buf, 1, sizeof(buf), f);
	
	shortswap(buf.count);
	shortswap(buf.ax);
	shortswap(buf.ay);
	shortswap(buf.az);
	shortswap(buf.wx);
	shortswap(buf.wy);
	shortswap(buf.wz);

	if (buf.start != 'A' || buf.end != 'Z') {
		//Framing error detected!!!
		fread(&buf2, 1, 64, f);

		for (int i = 1; i < 64; i++) 
		{
			if (buf2[i] == 'A' && buf2[i - 1] == 'Z')
			{
				if (!lastfound) {
					lastfound = i;
				}else{
					if (i - lastfound == sizeof(imudata)) {
						break;
					}else{
						printf("packet size error! (%d)\n", i-lastfound);
					}
				}
			}
		}

		printf("correction offset: %d\n", lastfound);
		fread(&buf2, 1, lastfound, f);
	}
}




