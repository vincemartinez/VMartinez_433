/*
 * File:   MainHW1.c
 * Author: Vince
 *
 * Created on April 1, 2015, 8:58 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "initialize.h"
#include <xc.h>
#include <sys/attribs.h>



void main() {

    PIC32startup();
    OC1RS=100; //425 is all the way left, 100 is all the way right
    OC2RS=1500;
    while (1) {
        if (PORTBbits.RB13==0){
            OC1RS=3000;
            LATBbits.LATB4=1;

    }
        else if (PORTBbits.RB13==1){
            OC1RS=3000;
            LATBbits.LATB4=0;
            
        }

    // wait for half a second, setting LED brightness to pot angle while waiting
    /*while (_CP0_GET_COUNT() < 10000000) {
        //int val = readADC();
        //int normalize_to_pr = 1; //max OC1RS (625) divided by max ADC (1023) is about 1

        //OC1RS = val * normalize_to_pr;

        if (PORTBbits.RB3 == 1) {
            
        }
        else {
            LATBINV=0b1000;
        }
    }*/
}
}
