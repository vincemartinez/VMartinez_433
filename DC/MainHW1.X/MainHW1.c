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

    while (1) {
    _CP0_SET_COUNT(0); // set core timer to 0, remember it counts at half the CPU clock
    LATBINV=0b10000000; // invert a pin

    // wait for half a second, setting LED brightness to pot angle while waiting
    while (_CP0_GET_COUNT() < 10000000) {
        int val = readADC();
        int normalize_to_pr = 1; //max OC1RS (625) divided by max ADC (1023) is about 1

        OC1RS = val * normalize_to_pr;

        if (PORTBbits.RB13 == 1) {
            
        }
        else {
            LATBINV=0b10000000;
        }
    }
}
}
