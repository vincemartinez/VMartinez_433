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
#include <xc.h>
#include <sys/attribs.h>

int startrow=28;
int startcol=32;
int randomint=1337;
int messagesize=10;

void main() {


    PIC32startup();
    display_init();
    LATBINV=0b10000000;

    char message[messagesize];
    sprintf(message, "Hello world %d!", randomint);


    display_string(message, startrow, startcol);

    while(1);


}

