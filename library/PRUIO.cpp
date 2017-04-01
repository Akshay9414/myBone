/*
Library for fast controlling GPIO, reading Analog Pins, generate PWM.
This is developed using functions of libpruio along with 
pinmuxing of wiringBone.
Fast controlling is achieved with the help of libpruio as it 
read the values directly from registers rather than system files.
---------------------------------------------------------------------
Points to remember:
1) While using gpio, don't forget to set the pinMode() and also make
changes in Userpinconfig.h
2) While using pwm, set the pin to pwm in Userpinconfig.h and along with
this run this command in terminal: config-pin <Pin> pwm
ex : config-pin P8.13 pwm 
3) Do not make any other instance of pruIo or PRUIO as one instantiation
has already been done and further instantiation will result in 
segmentation fault.
4) For running any code of libpruio use the given functional descriptions
only.
---------------------------------------------------------------------
Developer: Akshay Gahlot, Robotics Club IITD
*/

#include "PRUIO.h"
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
using namespace std;

PRUIO::PRUIO(){
  Io = pruio_new(PRUIO_DEF_ACTIVE, 0x98, 0, 1); //! create new driver structure
  if (Io->Errr) {
      printf("initialisation failed (%s)\n", Io->Errr);}
  if (pruio_config(Io, 1, 0x1FE ,0, 4)){ // upload (default) settings, start IO mode
      printf("config failed (%s)\n", Io->Errr);
  }
}

void PRUIO::set_gpio(Pin p,uint8_t val){
    if(p.selectedMode == gpio){
      switch(val){
      	case 0:  if(pruio_gpio_setValue(Io,p.cpu_ball,Io->BallConf[p.cpu_ball])){
        		printf("Failed to write the value\n");
      		}	break;
        case 1:  if(pruio_gpio_setValue(Io,p.cpu_ball,128 + Io->BallConf[p.cpu_ball])){
                               printf("Failed to write the value\n");
                }	break;
        default: printf("Invalid Mode\n");break;
    	}
    }
    else{
      printf("Mode of the pin is not gpio\n");
    }
}

int PRUIO::read_gpio(Pin p){
    if(p.selectedMode == gpio){
      int o = pruio_gpio_Value(Io,p.cpu_ball);
      if(o == -1 ) printf("Error in reading state of pin\n");
      return o; 
    }
    else{
      printf("Mode of the pin is not gpio\n");
      return -1;
    }
}

int PRUIO::read_adc(int u){
  if(u >= 0 && u <= 7){
     int o = Io->Adc->Value[u+1];
     //o = (int)((double)(o) * 0.0625);
     return o; 
  }
  else{
    printf("Pin is not initialised\n");
    return -1;
  } 
}

void PRUIO::set_frequency(Pin p,float f){
    if(p.selectedMode == pwm){
      if(pruio_pwm_setValue(Io,p.cpu_ball,(float_t)f,(float_t)-1)){
        printf("Error in changing frequency of pin\n");
        return;
      }
    }
    else{
      printf("Mode of the pin is not pwm\n");
    }
}

void PRUIO::set_duty_cycle(Pin p,float d){
    if(p.selectedMode == pwm){
      if(d>=0.0 && d<=1.0){
          if(pruio_pwm_setValue(Io,p.cpu_ball,(float_t)-1,(float_t)d)){
            printf("Error in changing duty cycle of pin\n");
            return;
          }
      }
      else{printf("Duty cycle should be b/w 0.0 to 1.0\n");return ;}
    }
    else{
      printf("Mode of the pin is not pwm\n");
    }
}

float PRUIO::read_duty_cycle(Pin p){
    if(p.selectedMode == pwm){
      float_t f,d;     
      if(pruio_pwm_Value(Io,p.cpu_ball,&f,&d)){
          printf("Error in changing duty cycle of pin\n");
          return -1;
      }
      return d;
    }
    else{
      printf("Mode of the pin is not pwm\n");
      return -1;
    }
}

float PRUIO::read_frequency(Pin p){
    if(p.selectedMode == pwm){
      float_t f,d;     
      if(pruio_pwm_Value(Io,p.cpu_ball,&f,&d)){
          printf("Error in changing duty cycle of pin\n");
          return -1;
      }
      return f;
    }
    else{
      printf("Mode of the pin is not pwm\n");
      return -1;
    }
}

void PRUIO::destroy_instance(){
	pruio_destroy(Io);        /* destroy driver structure */
//  	printf("PRU is disabled, Code ended properly\n");
}

PRUIO *libpru;

void digitalWriteFast(Pin p,uint8_t val){
	libpru->set_gpio(p,val);
}

int digitalReadFast(Pin p){
	return libpru->read_gpio(p);
}

int analogReadFast(int val){
	return libpru->read_adc(val);
}

void setFrequencyFast(Pin u,float f){
	libpru->set_frequency(u,f);
}


void setDutyFast(Pin u,float f){
	libpru->set_duty_cycle(u,f);
}

float readFrequencyFast(Pin u){
	return libpru->read_frequency(u);
}

float readDutyFast(Pin u){
	return libpru->read_duty_cycle(u);
}

PRUIO* pruioInstance()
{
  PRUIO* instance = new PRUIO();
  return instance;
}
