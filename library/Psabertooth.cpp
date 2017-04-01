
#include "Psabertooth.h"
#define BYTE unit8_t  

Psabertooth :: Psabertooth(int txpin, long b) {
	TXpin=txpin;
	baud=b;
	
	switch(TXpin)	{
                case 0:
                Serial.begin(baud);
                break;
             

		case 1:
		Serial1.begin(baud);
		break;
		
		case 2:
		Serial2.begin(baud);
		break;
		
		case 3:
		Serial3.begin(baud);
		break; 
	}
}
void Psabertooth :: ChangeBaud( byte address , long baud )
{
byte command = 15;
	byte baudrate = 2;
	switch(baud)
	{
	case 2400 : baudrate = 1;
				break;
	case 9600 : baudrate = 2;
				break;
	case 19200 : baudrate = 3;
				break;
	case 38400 : baudrate = 4;
				break;
	default : baudrate = 2;
			break;
	}
	switch(TXpin)	{
               

		case 0:
		
		Serial.write(address);
		 
		Serial.write(command);
		 
		Serial.write(baudrate);
		 
		Serial.write((address+command+baudrate)&127);
		 
	
		Serial.end();
		delayMicroseconds(10000);
		Serial.begin(baud);
		break;
		
				case 1:
		
		Serial1.write(address);
		 
		Serial1.write(command);
		 
		Serial1.write(baudrate);
		 
		Serial1.write((address+command+baudrate)&127);
		 
	
		Serial1.end();
		delayMicroseconds(10000);
		Serial1.begin(baud);
		break;
		
		case 2:
		
		Serial2.write(address);
		 
		Serial2.write(command);
		 
		Serial2.write(baudrate);
		 
		Serial2.write((address+command+baudrate)&127);
		 
		Serial2.end();
		delayMicroseconds(10000);
		Serial2.begin(baud);
		break;
		
		case 3:
	
		Serial3.write(address);
		 
		Serial3.write(command);
		 
		Serial3.write(baudrate);
		 
		Serial3.write((address+command+baudrate)&127);
		 
		Serial3.end();
		delayMicroseconds(10000);
		Serial3.begin(baud);
		break; 
	}

}
void Psabertooth :: leftSpeed(byte address, int velocity)	{
	byte speed;
	byte command = 0;
	
	if(velocity>127)
	velocity=127;
	else if(velocity<-127)
	velocity=-127;
	
	if (velocity<0) {
		velocity=-velocity;
		command = 1;
	}
	speed=map(velocity,1,127,1,127);
	
	
	switch(TXpin) {

               
		case 0:
		Serial.write(address);
		 
		Serial.write(command);
		 
		Serial.write(speed);
		 
		Serial.write((address+command+speed)&127);
		 
		break;
		case 1:
		Serial1.write(address);
		 
		Serial1.write(command);
		 
		Serial1.write(speed);
		 
		Serial1.write((address+command+speed)&127);
		 
		break;
		
		case 2:
		Serial2.write(address);
		 
		Serial2.write(command);
		 
		Serial2.write(speed);
		 
		Serial2.write((address+command+speed)&127);
		 
		break;
		
		case 3:
		Serial3.write(address);
		 
		Serial3.write(command);
		 
		Serial3.write(speed);
		 
		Serial3.write((address+command+speed)&127);
		 
		break; 
		
	}
}
	
	
void Psabertooth :: rightSpeed(byte address, int velocity)	{
	byte speed;
	byte command = 4;
	
	if(velocity>127)
	velocity=127;
	else if(velocity<-127)
	velocity=-127;
	
	if (velocity<0) {
		velocity=-velocity;
		command = 5;
	}
	speed=map(velocity,1,127,1,127);
	
	switch(TXpin) {

                
		
		case 0:
		Serial.write(address);
		 
		Serial.write(command);
		 
		Serial.write(speed);
		 
		Serial.write((address+command+speed)&127);
		 
		break;
		case 1:
		Serial1.write(address);
		 
		Serial1.write(command);
		 
		Serial1.write(speed);
		 
		Serial1.write((address+command+speed)&127);
		 
		break;
		
		case 2:
		Serial2.write(address);
		 
		Serial2.write(command);
		 
		Serial2.write(speed);
		 
		Serial2.write((address+command+speed)&127);
		 
		break;
		
		case 3:
		Serial3.write(address);
		 
		Serial3.write(command);
		 
		Serial3.write(speed);
		 
		Serial3.write((address+command+speed)&127);
		 
		break; 
		
	}
}

	
void Psabertooth :: stopSaber(byte address)	{
	switch(TXpin) {

               
		
		case 0:
		Serial.write(address);
		 
		Serial.write(0);
		 
		Serial.write(0);
		 
		Serial.write((address+0+0)&127);
		 
		Serial.write(address);
		 
		Serial.write(4);
		 
		Serial.write(0);
		 
		Serial.write((address+4+0)&127);
		 
		break;
		case 1:
		Serial1.write(address);
		 
		Serial1.write(0);
		 
		Serial1.write(0);
		 
		Serial1.write((address+0+0)&127);
		 
		Serial1.write(address);
		 
		Serial1.write(4);
		 
		Serial1.write(0);
		 
		Serial1.write((address+4+0)&127);
		 
		break;
		
		case 2:
		Serial2.write(address);
		 
		Serial2.write(0);
		 
		Serial2.write(0);
		 
		Serial2.write((address+0+0)&127);
		 
		Serial2.write(address);
		 
		Serial2.write(4);
		 
		Serial2.write(0);
		 
		Serial2.write((address+4+0)&127);
		 
		break;
		
		case 3:
		Serial3.write(address);
		 
		Serial3.write(0);
		 
		Serial3.write(0);
		 
		Serial3.write((address+0+0)&127);
		 
		Serial3.write(address);
                 
		Serial3.write(4);
		 
		Serial3.write(0);
		 
		Serial3.write((address+4+0)&127);
		 
		break; 
	}
}
	
