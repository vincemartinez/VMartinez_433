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


#include <stdio.h>
#include <stdlib.h>
#include "initialize.h"
#include <xc.h>
#include <sys/attribs.h>
#include "functions.h"



void main() {

    PIC32startup();
    OC1RS=350;

    int i=0;


    while (1) {

        if (i<=2000000){
            LATBbits.LATB14=1;
            LATBbits.LATB15=1;
            OC2RS=235;
            OC3RS=235;
            i++;
        }

        else if (i>2000000&&i<4000000){
            LATBbits.LATB14=1;
            LATBbits.LATB15=0;
            OC2RS=310;
            OC3RS=160;
            i++;
        }

        else {
            i=0;
        }

}
}
