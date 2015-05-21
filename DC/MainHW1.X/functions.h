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





void wait(int counts);
//void drive(int percent = 64);
void drive_dist(float dist);
void drive_off();
void turn (int degrees);
void arm(int direction);

int readADC1(void);
int readADC2(void);
int readADC3(void);
void LED_correct(int reference, int detected,int kp,int ki,int kd,int divisor);
double calculate_effort(int reference, int detected, int kp, int ki, int kd);
int volts_to_duty(double volts, double max_volts, int max_duty);
double duty_to_volts(int duty, int max_duty, double max_volts);
void follow_wall_left(int reference, int detected, int kp, int ki, int kd);
void follow_wall_right(int reference, int detected, int kp, int ki, int kd);
//total squares (until turn)
//read sensor








#endif	/* FUNCTIONS_H */

