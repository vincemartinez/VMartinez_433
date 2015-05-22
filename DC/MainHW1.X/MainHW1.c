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



void main() {

    user = 0;


    PIC32startup();
    int i=75;
    _CP0_SET_COUNT(0);
    killcount=0;
    



    //ADC1_tune();
    //ADC2_tune(&ADC_min,&ADC_max);
    //ADC4_tune();



    while(!user){

        if (PORTBbits.RB13==0){
            user=1;
            wait(250);
        }

    }


    LATBbits.LATB14=1;
    LATBbits.LATB15=1;

    OC2RS=235;
    OC3RS=228;
    OC4RS=235;
    
    //timer1_initialize();


    OC1RS=500;
    OC5RS=500;



    //interrupt_enable();


    while (user) {


        
           
           if (i==0){

               int reading=readADC1();
            //reading=(int)(reading*1.8);

            OC5RS= reading+50;
            //follow_wall_left(200,reading,1,0,0);
            //follow_wall_right(ADC_max,readADC2(),10,10,1);
            //IFS0bits.T1IF = 0;

            LATBbits.LATB14=1;
            LATBbits.LATB15=1;
            OC2RS=235;
            OC3RS=228;
            

            int reading5 = readADC5();
            int reading4 = readADC4();

            if(reading5 >= 100){
                OC4RS=380;
            }
            else if(reading5 < 100){
                OC4RS=270;
            }
            if(reading4>460){  //reads the front sensor to initiate turn... 460 is just barely about right
                i=100;
                OC1RS=500;
                OC5RS=500;
            }
            

            //i++;
            }

         else if (i=100){


            //OC1RS=500;
            //OC5RS=500;
            //interrupt_disable();
            LATBbits.LATB14=0;
            LATBbits.LATB15=1;
            OC2RS=290;
            OC3RS=180;
            wait(1600);
            OC2RS=235;
            OC3RS=228;
            //user = 0;
            i=0;
            
            //timer1_initialize();
            //interrupt_enable();

         }

        else if(i==50){
            OC1RS=0;
            OC5RS=0;
        }

        if (PORTBbits.RB13==0){
            user=0;
            OC1RS=0;
            OC5RS=0;
        }

           if(_CP0_GET_COUNT()>=400000000){
               OC1RS = 0;
               OC5RS = 0;
               killcount++;
               if (killcount > 2){
                   break;
               }
               _CP0_SET_COUNT(0);
           }

           if(i==75){
            LATBbits.LATB14=0;
            LATBbits.LATB15=1;
            OC2RS=290;
            OC3RS=180;

            if(_CP0_GET_COUNT()>=400000000){

                user=0;
                OC1RS=0;
                OC5RS=0;

            }

           }

}


}
