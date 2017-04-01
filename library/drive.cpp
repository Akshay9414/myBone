#include "drive.h"

double drive::maxdrive(double a,double b){
	if(a>b)
	return a;
	else 
	return b; 
 
	
}

double drive::mindrive(double a,double b){
	
	if(a<b)
	return a;
	else 
	return b; 
	
}

double abs(double t){
	if(t<0.0) return -t;
	else return t;
}

void drive::setP(double data){
	
	//outfile <<"newpos"<<endl;
	curr_position=readEncoder();
	stop_distance=data-curr_position;
	if(current_target==data && ((update_temp_2 && stop_distance < 0.0) || (!update_temp_2 && stop_distance > 0.0))) {
		curr_speed=0.0D;
		reached=true;
		
		//cout << "     ...........overflow..........  " ;  
	}
 
   else if(current_target==data && ((curr_position>temp_prev_position && curr_speed < 0) || (curr_position<temp_prev_position && curr_speed > 0))){
   cout << ".............slipping..........";}
	
	else{
 
  temp_prev_position=curr_position;
	
	if(current_target!=data){
	reached=false;
	current_target=data;
	if(curr_position > data) update_temp_2=false;
	else update_temp_2=true;
	
	if(stop_distance>0.0)
		{
			if(curr_speed<0)
			{
				stop_update();
				stop_now();
			}
			else
			{
				forward_update();
				move_forward();
		
			}
		}
	else if(stop_distance<0.0)	
		{
			if(curr_speed>0)
			{
				stop_update();
				stop_now();
			}
			else
			{
				backward_update();
				move_backward();
		
			}
			
			
		}
	}
	
	else{
	
	current_target=data;
	
	if(stop_distance>0.0)
	{
		if(curr_speed<0)
		{
			stop_now();
			update_temp=true;
		}

		else if(update_temp){
			forward_update();
			update_temp=false;
		}
		else
		{
			move_forward();
		
		}
	}
		
	else if(stop_distance<0.0)
	{	
		if(curr_speed>0){
			stop_now();
			update_temp=true;
		}
		else if(update_temp)
		{	
			backward_update();
			update_temp=false;
		}
		else{
			move_backward();
		}
	}
	

	////outfile << curr_speed<<"   "<<curr_position<<endl;
		
	}
	}

}

double drive::readEncoder(){

	return curr_position;
 
}

void drive::forward_update(){
	
	prev_position=readEncoder();
	curr_position=prev_position;
	target_distance=stop_distance;
	dec_position=curr_position;
	dec_speed=curr_speed;
	reverse=false;
	if(curr_speed<vmin && curr_speed>=0)
	curr_speed=vmin;
	init_speed=curr_speed;
	
 
 

	if(target_distance<(curr_speed*curr_speed)/(2*a_max_fi)){

		reverse=true;
		stop_distance_new=target_distance-curr_speed*curr_speed/(2*a_max_fi);
		target_distance=curr_speed*curr_speed/(2*a_max_fi);

	}
	
   if(((curr_speed*curr_speed+2*a_max_in*target_distance)*a_max_fi)/(a_max_in + a_max_fi) > 0)
	vmaxallowed=mindrive(pow(((curr_speed*curr_speed+2*a_max_in*target_distance)*a_max_fi)/(a_max_in + a_max_fi),0.5),vmax);
   else cout << "...........error..........";
	
	distance1=(vmaxallowed*vmaxallowed-curr_speed*curr_speed)/(2*a_max_in);
	distance3=(vmaxallowed*vmaxallowed + error_factor)/(2*a_max_fi);
	distance2=maxdrive(stop_distance-distance1-distance3,0.0);
	dec_position=distance1+distance2+prev_position;
	dec_speed=vmaxallowed;
	
	
}

void drive::move_forward(){

	
		
		if(curr_position<distance1+prev_position){
			if(init_speed*init_speed+2*a_max_in*(curr_position-prev_position) < 0) cout << "********* error1 **********" << endl;
			else curr_speed=pow(init_speed*init_speed+2*a_max_in*(curr_position-prev_position),0.5);
						
		}
		
		else if(curr_position<distance1+distance2+prev_position){
			
			curr_speed=vmaxallowed;
					
			}
		
		else if(curr_position<distance1+distance2+distance3+prev_position){
		
		 
		 	if((dec_speed*dec_speed-2*a_max_fi*(curr_position-dec_position))>0){// && curr_speed>vmin){
			curr_speed=pow(dec_speed*dec_speed-2*a_max_fi*(curr_position-dec_position),0.5);
			
			}
			else{
				if(dec_speed*dec_speed-2*a_max_fi*(curr_position-dec_position) < 0) cout << "********* error2 **********" << endl;
				else curr_speed=0.0;
			}
			
				
		}
		
		//outfile << curr_speed<<"  "<<curr_position<<endl;
			
	if(reverse && curr_speed==0.0){
		setP(stop_distance_new+curr_position);
	}
	
}

void drive::backward_update(){
	
	prev_position=readEncoder();
	curr_position=prev_position;
	target_distance=stop_distance;
	dec_position=curr_position;
	dec_speed=curr_speed;
	forward=false;
	if(curr_speed>-vmin && curr_speed<=0)
	curr_speed=-vmin;
	init_speed=curr_speed;


	if(target_distance>-(curr_speed*curr_speed)/(2*a_max_fi)){

		forward=true;
		stop_distance_new=target_distance+curr_speed*curr_speed/(2*a_max_fi);
		target_distance=-curr_speed*curr_speed/(2*a_max_fi);

	}

	if(((curr_speed*curr_speed-2*a_max_in*target_distance)*a_max_fi)/(a_max_in + a_max_fi) > 0)
	vmaxallowed=maxdrive(-pow(((curr_speed*curr_speed-2*a_max_in*target_distance)*a_max_fi)/(a_max_in + a_max_fi),0.5),-vmax);
  else cout << "...........error..........";	
 
	distance1=(vmaxallowed*vmaxallowed-curr_speed*curr_speed)/(2*a_max_in);
	distance3=(vmaxallowed*vmaxallowed + error_factor)/(2*a_max_fi);
	distance2=maxdrive(-stop_distance-distance1-distance3,0.0);
	dec_position=-distance1-distance2+prev_position;
	dec_speed=vmaxallowed;
	


}

void drive::move_backward(){

		
		if(curr_position>-distance1+prev_position){
			if(init_speed*init_speed-2*a_max_in*(curr_position-prev_position) < 0) ;//cout << "********* error3 **********" << endl;
			else curr_speed=-pow(init_speed*init_speed-2*a_max_in*(curr_position-prev_position),0.5);
			
		}
		
		else if(curr_position>-distance1-distance2+prev_position){
			
			curr_speed=vmaxallowed;
		
			}
		
		else if(curr_position>-distance1-distance2-distance3+prev_position){
			
			if((dec_speed*dec_speed+2*a_max_fi*(curr_position-dec_position))>0){ //&& curr_speed<-vmin){
			curr_speed=-pow(dec_speed*dec_speed+2*a_max_fi*(curr_position-dec_position),0.5);
			
			}
			else{
				if(dec_speed*dec_speed+2*a_max_fi*(curr_position-dec_position) < 0) cout << "********* error4 **********" << endl;
				else curr_speed=0.0;
			}
			
		}
   
			
			//outfile << curr_speed<<"  "<<curr_position<<endl;
			
	//curr_position=readEncoder();

	if(forward && curr_speed==0.0){
		setP(stop_distance_new+curr_position);
	}
	

}

void drive::stop_update(){
	
	prev_position=curr_position;
	init_speed=curr_speed;

}

void drive::stop_now(){

	if(curr_speed>0){
		
			if(init_speed*init_speed-2*a_max_in*(curr_position-prev_position)<0){
				curr_speed=0.0D;

			}
			else
				curr_speed=sqrt(init_speed*init_speed-2*a_max_in*(curr_position-prev_position));
			

	}

	else{

			
			if(init_speed*init_speed+2*a_max_in*(curr_position-prev_position)<0){
				curr_speed=0.0D;
			}
			else
				curr_speed=-pow(init_speed*init_speed+2*a_max_in*(curr_position-prev_position),0.5);



	}
	
	////outfile << curr_speed<<"exitstop"<<curr_position<<endl;

}




