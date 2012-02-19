struct termios;

class Sparkfun6DOF 
{
public:
	enum AccelSensitivity 
	{ sens_1g5, sens_2g, sens_4g, sens_6g };
	
	enum SampleFrequency
	{ freq_50hz , freq_100hz, freq_150hz, freq_200hz, freq_250hz };
	
	Sparkfun6DOF(const char * file);
	~Sparkfun6DOF();
	
	void start();
	void stop();
	
	
private:
	int fd;
	struct termios * options;
};