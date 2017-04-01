/*
Example code for easy controlling of GPIO, reading ADC, generate PWM.
This is developed using functions of libpruio along with 
pinmuxing of wiringBone.
Fast controlling is achieved with the help of libpruio as it 
read the values directly from registers rather than system files.
---------------------------------------------------------------------
Points to remember:
1) While using pwm, set the pin to pwm in Userpinconfig.h and
run this command in terminal: config-pin <Pin> pwm
ex : config-pin P8.13 pwm 
3) Do not make any other instance of pruIo or PRUIO as one instantiation
has already been done and further instantiation will result in 
segmentation fault.
4) For running any code of libpruio use the given functional descriptions
only.
---------------------------------------------------------------------
Functional Description : 
void digitalWriteFast(Pin u,uint8_t val); 
ex: digitalWriteFast(P8_11,0); 0 -> LOW , 1 -> HIGH

int digitalReadFast(Pin u);
ex: digitalReadFast(P8_11); returns 0 or 1 and -1 in case of error.

int analogReadFast(int u); 
ex: analogReadFast(2); returns value of ADC at AIN-2

void setFrequencyFast(Pin u,float f);
ex: setFrequency(P8_13,50); sets 50Hz at P8_13 

void setDutyFast(Pin u,float d);
ex: setDutyCycle(P8_13,0.5); set 50% duty at P8_13 

float readFrequencyFast(Pin u);
-> returns the frequency output of that pin in Hz
-> Don't confuse it with eCAP which can find out frequency of pulse train

float readDutyFast(Pin u);
-> returns the duty cycle of that pin in range 0.0 to 1.0
-> Don't confuse it with eCAP which can find out duty cycle of pulse trains
---------------------------------------------------------------------
Developer: Akshay Gahlot, Robotics Club IITD
*/

#include <stdio.h>
int main()
{
	
	pinMode(P8_14,OUTPUT);
  	pinMode(P8_10,OUTPUT);
  	digitalWriteFast(P8_14,1);
  	delayMicroseconds(1);
        printf("State of Pin P8_14 is %d\n",digitalReadFast(P8_14));
	digitalWriteFast(P8_10,0);
	delayMicroseconds(1);
	printf("State of Pin P8_10 is %d\n",digitalReadFast(P8_10)); 
  	digitalWriteFast(P8_10,1);
        delayMicroseconds(1);
	printf("State of Pin P8_10 is %d\n",digitalReadFast(P8_10)); 
  	
  	//Reading the ADC
    	for(int i=0;i<7;i++){
  		printf("%d ) %d\n",i,analogReadFast(i));
  	}
   	printf("\n");
  	
  	//Controlling the PWM	
  	setFrequencyFast(P8_13,50);
  	setDutyFast(P8_13,0.5);
  	printf("Frequency is %f\n",readFrequencyFast(P8_13)); 
	printf("Duty Cycle is %f\n",readDutyFast(P8_13)); 
	
	while(1){
		digitalWriteFast(P8_10,1);
  		delayMicroseconds(5);
  		printf("%d\t",digitalReadFast(P8_10));
  		digitalWriteFast(P8_10,0);
		delayMicroseconds(5);
		printf("%d\n",digitalReadFast(P8_10));
		delay(500); 
	}
	return 0;
}
