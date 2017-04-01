#ifndef Psabertooth_h
#define Psabertooth_h

#include "Arduino.h"
//#define BYTE unit8_t 
/*
Library for Sabertooth on Arduino Mega2560
Written by GNB

Edited by Varan Gupta

Constructor requires TX_pin (1,2 or 3 on Mega) and baudrate

*/

class Psabertooth	{
	
	public:
	
	Psabertooth(int txpin, long baud); // prev. baud rate 
	void ChangeBaud( byte address , long baud );
	void leftSpeed(byte address, int velocity);  // address(128,...,133) and velocity
	void rightSpeed(byte address, int velocity);
	void stopSaber(byte address); //stop one sabertooth
	void ramp(byte startspeed,byte finalspeed,byte duration);
	
	private:
	
	int TXpin;
	long baud;
	
};

#endif
