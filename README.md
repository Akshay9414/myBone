myBone
myBone is a user friendly platform like Arduino for BBB (so that anyone could code easily without worrying much about the backend details).
Current Wiring Bone library (https://github.com/AbhraneelBera/wiringBone) supports almost all core actions and functions but is slow in terms of pin toggling. myBone is a  integration of basic Arduino features from Wiring Bone along with addition of features of Libpruio (http://beagleboard.org/project/libpruio/) for fast pin control. I also extended my work and built new C libraries for using pins in eQEP mode for reading values of quadrature encoder and customising DTO according to the needs. 

# Features
For fast pin toggling : 
1) digitalWriteFast(Pin u,uint8_t val); 
ex: digitalWriteFast(P8_11,0); 0 -> LOW , 1 -> HIGH

2) digitalReadFast(Pin u);
ex: digitalReadFast(P8_11); returns 0 or 1 and -1 in case of error.

3) analogReadFast(int u); 
ex: analogReadFast(2); returns value of ADC at AIN-2

4) setFrequencyFast(Pin u,float f);
ex: setFrequency(P8_13,50); sets 50Hz at P8_13 

5) setDutyFast(Pin u,float d);
ex: setDutyCycle(P8_13,0.5); set 50% duty at P8_13 

6) readFrequencyFast(Pin u);
-> returns the frequency output of that pin in Hz
-> Don't confuse it with eCAP which can find out frequency of pulse train

7) float readDutyFast(Pin u);
-> returns the duty cycle of that pin in range 0.0 to 1.0
-> Don't confuse it with eCAP which can find out duty cycle of pulse trains

Along with the all the other features of Arduino like Serial.print()

# How to use
1) Edit the c code according as you wish.
2) Edit the UserPinConfig.h file in library directory by defining type of pin as needed.
3) run the script build-source with argument make : "./build-source make".
4) After compilation type : "./build-source run".
