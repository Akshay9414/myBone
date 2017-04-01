#ifndef PRUIO_H
#define PRUIO_H

#define _GNU_SOURCE 1
#include "PINS.h"
#include <stdio.h>
#include <stdint.h>
#include "./src/c_wrapper/pruio.h"

class PRUIO{
	private:
		pruIo *Io;
	public:
		PRUIO();
		//~PRUIO();
		
		void set_gpio(Pin u,uint8_t val); 
		// set_gpio(P8_11,0); 0 -> LOW , 1 - > HIGH
		
		int read_gpio(Pin u);
		// read_gpio(P8_11); return 0 or 1 and -1 in case of error
		int read_adc(int u); 
		// read_adc(2); returns value of ADC at AIN-2

		void set_frequency(Pin u,float f);
		// set_frequency(P8_13,50); set 50Hz at P8_13 

		void set_duty_cycle(Pin u,float d);
		// set_duty_cycle(P8_13,0.5); set 50% duty at P8_13 
		float read_frequency(Pin u);
		// returns the frequency output of that pin
		// Don't confuse it with cap which can find out frequency of pulse train

		float read_duty_cycle(Pin u);
		// returns the duty cycle of that pin in range 0.0Ak to 1.0
		// Don't confuse it with cap which can find out duty cycle of pulse train
		
		void destroy_instance();
}; 

extern PRUIO *libpru;

void digitalWriteFast(Pin p,uint8_t val);
int digitalReadFast(Pin p);
int analogReadFast(int o);
void setFrequencyFast(Pin u,float f);
void setDutyFast(Pin u,float f);
float readFrequencyFast(Pin u);
float readDutyFast(Pin u);
PRUIO* pruioInstance();
		
#endif
