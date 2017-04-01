/*
Library for controlling a servo
Developer: Akshay Gahlot, Robotics Club IITD
*/

#include <iostream>
#include "Servo.h"
//#include "OVERLAY.h"
#include "PWM.h"
#include "PRUIO.h"

float mapper(int value);
Servo::Servo(Pin name,int value)
{
	if(value > 180) value = 180;
	if(value < 0) value = 0;
	identifier = name;
	setFrequencyFast(identifier,50);
	setDutyFast(identifier,mapper(value));
        current_pos = value;
}

int Servo::read(){
	return current_pos;
}

void Servo::set(int value){
	if(value > 180) value = 180;
	if(value < 0) value = 0;
	int u;
	if(value > current_pos){
		for(u = current_pos;u<=value;u=u+2){
			setDutyFast(identifier,mapper(u));    
			//add delay  
		}
	}
	else{
		for(u = current_pos;u>=value;u=u-2){
			setDutyFast(identifier,mapper(u));
			//add delay
		} 
	}
 current_pos = value;  
}

float mapper(int value){
	return (value*slope + 0.03);
}
