#include <stdio.h>
#include <time.h>
#include <string.h>

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
//declaring variables that will be used.
int v_left = 0;
int v_right = 0;
int stop = 0;
int previous_error;
int error;
int current_error = 0;
int proportional_signal;
int kp = 0.5;
int motor1;
int motor2;
int max_speed = 70;
int kd = 5.0;
int derivative_signal;
int quadrantThree = 1;

void straight(){
        set_motor(1,max_speed);
        set_motor(2,max_speed);
        printf("%s","straight");
}

void turnLeft(){
        motor1 =max_speed/2;
        motor2 =max_speed;
        set_motor(1,motor1);
        set_motor(2,motor2);
        printf("%s\n","left");
//      Sleep(0,10000);
        //printf("%d",signal);
}

void turnRight(){
        motor1 = max_speed;
        motor2 = max_speed/2;
        set_motor(1,motor1);
        set_motor(2,motor2);
        printf("%s\n","right");
}

int main()
{
    int i;
    init(0);
    // connect camera to the screen, displaying the camera on the screen
    open_screen_stream();
    // set all digital outputs to +5V
    for (i = 0; i < 8; i++)
        {
      // set all digital channels as outputs
      select_IO(i,0);
      write_digital(i,1);
    }
    //Networking goes here
    connect_to_server("130.195.6.196",1024);
    send_to_server("Please");
    char message[24];
    receive_from_server(message);
    send_to_server(message);

    while(quadrantThree==1) //while(1) means an infinite loop
                {
        // take camera shot, which will then be processed for
        // error correction
        take_picture();

       // draw some line
        set_pixel(100, 55 ,255,0,0);
        set_pixel(101, 55 ,255,0,0);
        set_pixel(102, 55 ,255,0,0);
        set_pixel(103, 55 ,255,0,0);

       // display the most recent picture on the screen
        update_screen();

       // get the middle pixels of the image
        for(int i=0; i<320; i++){
                error =(i-160)* (get_pixel(i, 120, 3));
                current_error = current_error + error;
       }


            //derivative_signal = (current_error-previous_error/0.1)*kd;
        proportional_signal = error *0.5; // <--- kp
        previous_error = current_error;
        printf("Proportional sig: %d\n",proportional_signal);

        if((proportional_signal > 700) && (proportional_signal < 3000)){
                straight();
        }
        else if((proportional_signal > 3000)&&(proportional_signal < 9500)){
                turnLeft();

        }
        else{
                turnRight();
        }




    }

   return 0;
}
