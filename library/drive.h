#ifndef drive_H 
#define drive_H

#include <math.h>
#include <iostream>

using namespace std;

class drive{

public:
	 
	double vmax;
	double a_max_in;
  double a_max_fi;
	double vmin;
	double vmaxallowed;
	double curr_speed;
  double temp_prev_position;
	double target_distance;
	double dec_position;
	double prev_position;
	double curr_position;
	double stop_distance;
	double dec_speed;
	double init_speed;
	double distance1;
	double distance2;
	double distance3;
	double stop_distance_new;
	double current_target;
	double error_factor;
	bool reached;
	bool reverse;	
	bool forward;
	bool output_file;
	bool check;
	bool stop1;
	bool update_temp,update_temp_2,stop_temp;
	volatile bool newinput;
	
	drive(double d1,double d2,double d3,double d4,bool state){

	vmax=d1;
	vmin=d2;
	a_max_in=d3;
  a_max_fi=d4;
	curr_position=0.0D;
	curr_speed=0.0D;
	target_distance=0.0D;
	reverse=false;
	forward=false;
	newinput=false;
	output_file=state;
	reached=true;
	check=false;
	stop1=false;
	update_temp=false;
	update_temp_2=false;
	stop_temp=false;
	
	vmaxallowed=0.0D;
  temp_prev_position=0.0D;
	error_factor=0.0D;
	dec_position=0.0D;
	prev_position=0.0D;
	curr_position=0.0D;
	stop_distance=0.0D;
	dec_speed=0.0D;
	init_speed=0.0D;
	distance1=0.0D;
	distance2=0.0D;
	distance3=0.0D;
	stop_distance_new=0.0D;
	current_target=0.0D;
	reverse=false;
	forward=false;
	
	}
	
	double readEncoder();
	void move_backward();
	void move_forward();
	void backward_update();
	void forward_update();
	void stop_now();
	void stop_update();
	void setP(double data);
	double maxdrive(double a,double b);
	double mindrive(double a,double b);
	

};

	
	


	

#endif
