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

#define ANAL_CONFERSION=40000000;


void wait(double seconds){

    _CP0_SET_COUNT(0);

    while(_CP0_GET_COUNT()<((double)40000000*seconds)){
        continue;
    }

    _CP0_SET_COUNT(0);

}

void turn (int degrees){

    drive_off();

    OC2RS=310;
    OC3RS=160;

    if(degrees<0){
        LATBbits.LATB14=1;
        LATBbits.LATB15=0;
    }

    else {
        LATBbits.LATB14=0;
        LATBbits.LATB15=1;
    }

    drive();
    wait(ANAL_CONFERSION*degrees);

    drive_off();
    
    OC2RS=235;
    OC3RS=235;

    drive();

}







#endif	/* FUNCTIONS_H */

