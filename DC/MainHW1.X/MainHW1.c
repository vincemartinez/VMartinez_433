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
