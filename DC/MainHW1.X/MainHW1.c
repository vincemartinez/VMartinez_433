/*
 * File:   MainHW1.c
 * Author: Vince
 *
 * Created on April 1, 2015, 8:58 PM
 */

/* Sup Curty! The "wait()" function takes a number of seconds as input, and
 * delays the program for that number of seconds. The "drive()" function tells
 * the motors to move forward at a certain percentage of their maximum speed.
 * If no value is put in then it defaults to 64%. The "drive_dist()" function
 * specifies a certain distance in inches to drive. The "drive_off()" function
 * turns the motors off. The "turn()" function takes a number of degrees as the
 * input, and rotates the robot by that number of degrees. If you input a
 * negative number, the robot will turn clockwise(maybe?) and vice versa. The
 * "arm()" function takes either "UP" or "DOWN" as inputs, and moves the arm up
 * or down.
 * */

/*This is Craig's code*/

/* Sup SLAM!  This is you typing. wow. meta. Motors are labelled on legos next to
 attachment points, and on the 3D printed connector (you have to look close on the
 black ones, but it's on there.) Servos 2 and 4 connect to PWM from B9 (the 3x header
 pins closest to the H-bridge) and servos 1 and 3 attach to B8 (bottom 3x header).
 Motors 1 and 3 go to output B. And motor 2 and 4 go to output A from the H-bridge. Please
 * don't fuck with the way the leads go into the screw terminals, as that would
 * fuck everything up that I just typed... Asshat.
 */

#include <stdio.h>
#include <stdlib.h>
#include "initialize.h"
#include <xc.h>
#include <sys/attribs.h>
#include "functions.h"



/*
 void turn_until_sense(int dir){
 
  // readADC1() is left sensor
  // readADC2() is right sensor
 
  // turn until current value is greater than prev value
 
   int turn_direction = dir;
  
 
   int prev_value = 1000000000;
   int curr_value;
   if(turn_direction){
 
       LATBbits.LATB14 = 1;
       LATBbits.LATB15 = 0;
       curr_value = readADC1();
   }
   else if(!turn_direction){
 
       LATBbits.LATB14 = 0;
       LATBbits.LATB15 = 1;
       curr_value = readADC2();
   }
 
   
   
 
   while(prev_value > curr_value){
       OC2RS=290;
        OC3RS=180;
        OC1RS = 550;
        OC5RS = 500;
       prev_value = curr_value;
       if(turn_direction){
             curr_value = readADC1();
       }
       else if(!turn_direction){
           curr_value = readADC2();
       }
   }
 
   return;
 
  }
 
 */


void main()
{

    PIC32startup();
    user = 0;
    int i=75;
    _CP0_SET_COUNT(0);
    killcount=0;
    int wall_follow = 1;
    int turn_90 = 0;
    //bool vince_is_sexy=true;


    int my_color, purple, white;
    int color_thresh = 170;
    
    int arm_down = 370;
    int arm_up = 240;


    int turn_direction = 0;

    int kick_count = 0;

    int stored_color;
    int color_count = 0;
    int color_count_limit = 120000;

    while(1)
    {
        //wait til user button pushed
        while(!user)
        {

            if (PORTBbits.RB13==0)
            {
                user=1;
                _CP0_SET_COUNT(0);
                wait(350);
                my_color = readADC5();
                if(my_color >= color_thresh){
                   // started on white, arm down on white
                   purple = 0;
                   white = 1;
                   // wall follow right
                   turn_direction = 1;
                }
                else if (my_color < color_thresh){
                    // started on purple, arm down on purple
                    purple = 1;
                    white = 0;
                    // wall follow left
                    turn_direction = 0;
                }
                timer1_initialize();
                interrupt_enable();
            }

        }

        //Set directions to forward. Set servos straight. Set PWMs to 500
        LATBbits.LATB14=1;
        LATBbits.LATB15=1;
        OC2RS=235;
        OC3RS=228;
        OC4RS=235;
        OC1RS=400;
        OC5RS=400;

        if(purple){
            stored_color = 1;
        }
        else{
            stored_color = 0;
        }

        while (user)
        {

            // get current color
            // compare to stored color
            // if same, increment counter
            // if different, reset stored color and reset counter

            int current_color = readADC3();
            if (current_color >= color_thresh){
                // current is white
                if(stored_color){ // stored is purple, switch
                    stored_color = 0;
                    color_count = 0;
                }
                else{
                    //increment color count
                    color_count++;
                }
            }
            else{
                // current is purple
                if(stored_color){
                    //increment color count
                    color_count++;
                }
                else{ // stored is white, switch
                    stored_color = 1;
                    color_count = 0;
                }
            }


            if(color_count > color_count_limit){

                if(!turn_direction){
                        LATBbits.LATB14=0;
                        LATBbits.LATB15=1;

                }
                else if (turn_direction){
                    LATBbits.LATB14 = 1;
                    LATBbits.LATB15 = 0;
                }
                //set servos to 45 deg, set motors to 500 PWM and wait for about 1600;
                OC2RS=290;
                OC3RS=180;
                OC1RS = 400;
                OC5RS = 400;
                wait(600);
                //set servos back to straight
                OC2RS=235;
                OC3RS=228;

                color_count = 0;

            }

            while (readADC1() < 200 && readADC2() < 200 && readADC4() < 400)
            {
                // all sensors read zero, drive straight
                LATBbits.LATB14 = 1;
                LATBbits.LATB15 = 1;

                OC2RS = 235;
                OC3RS = 228;

                OC1RS = 400;
                OC5RS = 400;
            }

               if (wall_follow)
               {

                    //set servos straight. Keep directions forward
                    LATBbits.LATB14=1;
                    LATBbits.LATB15=1;
                    OC2RS=235;
                    OC3RS=228;

                    // generalize to wall follow either side:
                    //      (start) white:  wall follow right
                    //                  - reading ADC2
                    //                  - OC1RS <- reading + (50??)
                    //      (start) purple: wall follow left
                    //                  - reading ADC1
                    //                  - OC5RS <- reading + 50
                    //read left sensor and set left motors to reading + 50


                    
                     int reading;

                     if(purple == 1){
                      //wall follow left
                      LATBbits.LATB14=1;
                      LATBbits.LATB15=1;
                      reading = readADC1();
                      OC5RS = reading;
                     
                     }
                     else{
                     // wall follow right
                     LATBbits.LATB14=1;
                     LATBbits.LATB15=1;
                     reading = readADC2();
                     OC1RS = reading + 250; // yet to be tested
                     
                     }
                     
                    
                    //int reading=readADC1();
                    //OC5RS= reading+50;
                    
                    int right_color = readADC5();//reading5
                    int left_color = readADC3();
                    int frontdist = readADC4();//reading4

                    //if we're on white put arm down
                    if(left_color >= color_thresh)
                    {
                        // on white
                        if(white){
                            if(kick_count < 5000){
                                OC4RS = arm_down;
                            }
                            else if (kick_count < 6000){
                                OC4RS = arm_down - 45;

                            }
                            else{
                                OC4RS = arm_down;
                                kick_count = 0;
                            }


                        }
                        else if(purple){
                            OC4RS = arm_up;
                        }
                    }
                    //if we're on purple, put arm up
                    else if(left_color < color_thresh)
                    {
                        // on purple
                        if(purple){
                            if(kick_count < 5000){
                                OC4RS = arm_down;
                            }
                            else if (kick_count < 6000){
                                OC4RS = arm_down - 45;

                            }
                            else{
                                OC4RS = arm_down;
                                kick_count = 0;
                            }
                        }
                        else if (white){
                            OC4RS = arm_up;
                        }
                    }
                    //if front sensor is within certain distance, put in turn mode
                    if(frontdist > 400)
                    {
                        OC1RS=400;
                        OC5RS=400;
                        wall_follow = 0;
                        turn_90 = 1;
                    }
                }

               else if (turn_90) // turn_right_90
               {
                    //set direction on right side backwards


                    // turn_until_sense(turn_direction);

                    // for turn right 90

                   //turn_until_sense(turn_direction);


                   
                    
                    if(!turn_direction){
                        LATBbits.LATB14=0;
                        LATBbits.LATB15=1;

                    }
                    else if (turn_direction){
                        LATBbits.LATB14 = 1;
                        LATBbits.LATB15 = 0;
                    }
                    //set servos to 45 deg, set motors to 500 PWM and wait for about 1600;
                    OC2RS=290;
                    OC3RS=180;
                    OC1RS = 400;
                    OC5RS = 400;
                    wait(900);
                    //set servos back to straight
                    OC2RS=235;
                    OC3RS=228;
                                                
                    // go back to wall follow
                    wall_follow = 1;
                    turn_90 = 0;

               }

               //if button is pressed, kill motors.
               if (PORTBbits.RB13==0)
               {

                    OC1RS=0;
                    OC5RS=0;
                    user=0;
                    wall_follow = 1;
                    turn_90 = 0;
               }

               //if button isn't pressed within 3 minutes, kill motors.
//               if(_CP0_GET_COUNT()>=400000000)
//               {
//                   \killcount++;
//                   if (killcount > 2)
//                   {
//                       OC1RS = 0;
//                       OC5RS = 0;
//                       user = 0;
//                       wall_follow = 1;
//                       turn_90 = 0;
//                   }
//                   _CP0_SET_COUNT(0);
//               }
               if(killcount >= 880)
               {
                   LATBINV = 0b1000000000000000;
                   OC1RS = 0;
                   OC5RS = 0;
                   user = 0;
               }

            kick_count++;

        }
    }
}

