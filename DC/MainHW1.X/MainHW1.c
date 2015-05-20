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

    int ADC_min=0;
    int ADC_max=1024;

    PIC32startup();
    int i=0;
    OC1RS=450;
    OC5RS=450;
    /*while(1){
        
       int reading=readADC3();

       if (reading>200){
           LATBbits.LATB15=1;
           OC1RS=0;
       }
       else{
           LATBbits.LATB15=0;
           OC1RS=600;
       }

    }*/

/*
        ADC1_tune(&ADC_min,&ADC_max);
        int distance=readADC1();

        if (ADC_min>500&&ADC_max<500){
            OC1RS=500;
        }*/
        
    



    
    while (1) {

        if (i<=5000000){
            LATBbits.LATB14=1;
            LATBbits.LATB15=1;
            OC2RS=235;
            OC3RS=228;
            OC4RS=370;
            i++;
        }

        else if (i>5000000&&i<7000000){
            LATBbits.LATB14=1;
            LATBbits.LATB15=0;
            OC2RS=290;
            OC3RS=180;
            OC4RS=235;
            i++;
        }

        else {
            i=0;
        }

}

}
