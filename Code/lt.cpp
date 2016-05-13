/*SKELETON CODES FOR AVC */
/*  A.Roberts, 5 Apr 2016*/
#include <stdio.h>

//#include <pthread.h>
#include <time.h>
#include <string.h>

// sudo gcc -Wall
extern "C" int init_hardware();
extern "C" int init(int d_lev);

extern "C" int take_picture();
extern "C" char get_pixel(int row, int col, int color);
extern "C" void set_pixel(int col, int row, char red,char green,char blue);

extern "C" int open_screen_stream();
extern "C" int close_screen_stream();
extern "C" int update_screen();
//extern "C" void GetLine(int row,int threshold);
extern "C" int display_picture(int delay_sec,int delay_usec);
extern "C" int save_picture(char filename[5]);

extern "C" int set_motor(int motor,int speed);

extern "C" int read_analog(int ch_adc);
extern "C" int Sleep(int sec, int usec);
extern "C" int select_IO(int chan, int direct);
extern "C" int write_digital(int chan,char level);
extern "C" int read_digital(int chan);
extern "C" int set_PWM(int chan, int value);

extern "C" int connect_to_server( char server_addr[15],int port);
extern "C" int send_to_server(char message[24]);
extern "C" int receive_from_server(char message[24]);

//motor 1 is left
//motor 2 is right

int v_left = 0;
int v_right = 0;
int full_speed1 = 100;
int full_speed2 = -100;
int stop = 0;
int top_value = 0;
int top_index = 0;
int bottom_value = 0;
int bottom_index = 0;
int mid_value = 0;
int mid_index = 0;
int mid_sum = 0;
int left_value = 0;
int left_index = 0;
int left_sum = 0;
int right_value = 0;
int right_index = 0;
int right_sum = 0;
 

int main()
{
    int i;
    init(0);
    // connect camera to the screen
    open_screen_stream();
    // set all digital outputs to +5V
    for (i = 0; i < 8; i++)
    {
      // set all digital channels as outputs
      select_IO(i,0);
      write_digital(i,1);
    }

    while(1)
    {
       // take camera shot
       take_picture();

       // draw some line
       set_pixel(100, 55 ,255,0,0);
       set_pixel(101, 55 ,255,0,0);
       set_pixel(102, 55 ,255,0,0);
       set_pixel(103, 55 ,255,0,0);
       
       // display picture
       update_screen();
       
       // get the top middle pixel
       top_value = get_pixel(160, 120, 3);
       if(top_value < 127){
		top_index = 0;
       } else {
		top_index = 1;
       }

       //get the bottom middle pixel
       bottom_value = get_pixel(320, 120, 3);
       if(bottom_value < 127){
		bottom_index = 0;
       } else {
		bottom_index = 1;
       }

       // get the middle image of picture
       for(int i=0, i<320, i++){
		mid_value = get_pixel(i, 120, 3);
		if(mid_value < 127){
			mid_index = 0;
		} else {
			mid_index = 1;
		}
		mid_sum = mid_sum + mid_index;
	}

       // get the left side image of the col = 30
       for(int i=0, i<320, i++){
		left_value = get_pixel(i, 30, 3);
		if(left_value < 127){
			left_index = 0;
		} else {
			left_index = 1;
		}
		left_sum = left_sum + left_index;
       }	
       
       // get the left side image of the col = 60
       for(int i=0, i<320, i++){
		left_value = get_pixel(i, 60, 3);
		if(left_value < 127){
			left_index = 0;
		} else {
			left_index = 1;
		}
		left_sum = left_sum + left_index;
       }	

       // get the left side image of the col = 90 
       for(int i=0, i<320, i++){
		left_value = get_pixel(i, 90, 3);
		if(left_value < 127){
			left_index = 0;
		} else {
			left_index = 1;
		}
		left_sum = left_sum + left_index;
       }	

       // get the right side image of the col = 150
       for(int i=0, i<320, i++){
		right_value = get_pixel(i, 150, 3);
		if(right_value < 127){
			right_index = 0;
		} else {
			right_index = 1;
		}
		right_sum = right_sum + right_index;
       }

       // get the right side image of the col = 180
       for(int i=0, i<320, i++){
		right_value = get_pixel(i, 180, 3);
		if(right_value < 127){
			right_index = 0;
		} else {
			right_index = 1;
		}
		right_sum = right_sum + right_index;
       }

       // get the right side image of the col = 210
       for(int i=0, i<320, i++){
		right_value = get_pixel(i, 210, 3);
		if(right_value < 127){
			right_index = 0;
		} else {
			right_index = 1;
		}
		right_sum = right_sum + right_index;
       }

       // control the motors speed and direction
       if(top_index =1 && bottom_index = 1 && left_sum = 0 && right_sum = 0){
		set_motor(1, full_speed1);
		set_motor(2, full_speed2); //go straight
       } else if(top_index =1 && bottom_index = 1 && left_sum > 0 && right_sum > 0){
		set_motor(1, full_speed1);
		set_motor(2, full_speed2); //go straight
       } else if(top_index =1 && bottom_index = 1 && left_sum > 0){
		set_motor(1, full_speed1);
		set_motor(2, full_speed2); //go straight
       } else if(top_index =0 && bottom_index = 1 && left_sum > 0 && right_sum > 0){
		set_motor(1, full_speed1);
		set_motor(2, full_speed2*2); //turn left
       } else if(left_sum > 0){
		set_motor(1, full_speed1);
		set_motor(2, full_speed2*2); //turn left
       } else if(right_sum > 0){
		set_motor(1, full_speed1*2);
		set_motor(2, full_speed2); //turn left
       }

       // check motors
       // set_motor(1, speed1);
       // set_motor(2, speed2);
       // Sleep(5,0);
       // set_motor(1, stop);
       // set_motor(2, stop);
       // Sleep(5,0);
       
       
       for (i = 0 ; i < 8; i++){
        	int av = read_analog(i);
        	printf("ai=%d av=%d\n",i,av);
       }
   }

   // terminate hardware
   close_screen_stream();
   set_motor(1,0);
   set_motor(2,0);
  
   return 0;
}
