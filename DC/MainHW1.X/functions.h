/* 
 * File:   functions.h
 * Author: Vince
 *
 * Created on May 17, 2015, 12:53 AM --lol
 */


#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <sys/attribs.h>


#ifndef FUNCTIONS_H
#define	FUNCTIONS_H

#define ANAL_CONFERSION 40000000
#define DISTANCE_CONVERSION 40000000 //Tics per inch (need to fine tune)
#define UP 85
#define DOWN 385


void wait(double seconds);
//void drive(int percent = 64);
void drive_dist(float dist);
void drive_off();
void turn (int degrees);
void arm(int direction);








#endif	/* FUNCTIONS_H */

