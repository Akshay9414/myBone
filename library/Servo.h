/*
Library for controlling a servo
Developer: Akshay Gahlot, Robotics Club IITD
*/

#ifndef Servo_H
#define Servo_H
#include "PINS.h" 
#define min_timeperiod 0.03 //600
#define max_timeperiod 0.12 //2400
#define slope (max_timeperiod - min_timeperiod)/180

class Servo{
	public:
		Servo(Pin name,int value);
		void set(int value);
		int read();
	private:
		int current_pos;
		Pin identifier;
}; 
#endif
