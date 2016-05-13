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
// initializing variables
int v_left = 0;
int v_right = 0;
int speed1 = 0;
int speed2 =0;
int stop = 0;
int speedIndex = 0;
char p [320];
int main(){    
    connect_to_server("130.195.6.196",1024);//connecting to the gate
    send_to_server("Please");//Sending the gate a message, asking for the password
    char message[24];
    receive_from_server(message); //setting the variable 'message' as the message
    send_to_server(message); //NOTE: You must run se2 on the gate pi before running this code.
    
    int i;
    
    int i;
    init(0);
    // connect camera to the screen
    open_screen_stream();
    // set all didgital outputs to +5V
    for (i = 0; i < 8; i++)
    {
   //    set all digital channels as outputs
        select_IO(i,0);
        write_digital(i,1);
    }
   // while(1 == 1)
   // {
       take_picture(); // take camera shot
       // draw some line
       set_pixel(100, 55 ,255,0,0);
       set_pixel(101, 55 ,255,0,0);
       set_pixel(102, 55 ,255,0,0);
       set_pixel(103, 55 ,255,0,0);

       // get index from picture to check white line
       //scans across the center of the image getting the pixels
    for (i = 0; i <= 320; i++){
        p[i]=get_pixel(i, 120, 3);
        printf("%d\n" ,p[i]);

        if(p[i] <= 50){
        p[i] = 0;}

        else{
        p[i] = 1;}
    }

    printf("%d\n",p[160]);
        if(p[160] == 1){
            set_motor(1, 255);
            set_motor(2, 255);
        }
       // display picture
       update_screen();

       // check motors
   //  }
    Sleep(5,0);
   // terminate hardware
   // close_screen_stream();
    set_motor(1,0);
    set_motor(2,0);

    return 0;



}
