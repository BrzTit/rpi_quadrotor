class Sparkfun6DOF 
{
public:
	enum AccelSensitivity 
	{ sens_1g5, sens_2g, sens_4g, sens_6g };
	
	enum SampleFrequency
	{ freq_50hz , freq_100hz, freq_150hz, freq_200hz, freq_250hz };
	
#pragma pack(push, 1)
	struct imudata {
		char start;
		unsigned short count;

		unsigned short ax, ay, az;
		unsigned short wx, wy, wz;

		char end;
	};
#pragma pack(pop)
	
	Sparkfun6DOF(const char * file);
	~Sparkfun6DOF();
	
	void start();
	void stop();
	
	void setAccelSensitivity(AccelSensitivity sensitivity);
	void setSampleFrequency(SampleFrequency frequency);
	
	void getIMUData(imudata & data);
	
private:
	int fd;
	FILE * f;
	struct termios * options;
	
	void shortswap(unsigned short & val);
};