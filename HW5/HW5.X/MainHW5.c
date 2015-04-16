/* 
 * File:   MainHW4.c
 * Author: Vince
 *
 * Created on April 12, 2015, 1:27 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "i2c_display.h"
#include "i2c_master_int.h"
#include "initialize.h"
#include "accel.h"
#include <xc.h>
#include <sys/attribs.h>

//int startrow=28;
//int startcol=32;
//int randomint=1337;
//int messagesize=10;

short accels[3];
short mags[3];
short temp;


void main() {


    PIC32startup();
    display_init();
    acc_setup();
    LATBINV=0b10000000;

    

    //char message[messagesize];
    //sprintf(message, "Hello world %d!", randomint);


    //display_string(message, startrow, startcol);

    while(1){
        

        acc_read_register(OUT_X_L_A, (unsigned char *) accels, 6);
        acc_read_register(OUT_X_L_M, (unsigned char *) mags, 6);
        acc_read_register(TEMP_OUT_L, (unsigned char *) &temp, 2);

        acc_bar_display(accels[0], accels[1]);



        LATBINV=0b10000000;
        

    }

}

