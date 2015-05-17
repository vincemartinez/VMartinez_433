#include "functions.h"


void wait(double seconds){

    _CP0_SET_COUNT(0);

    while(_CP0_GET_COUNT()<((double)40000000*seconds)){
        continue;
    }

    _CP0_SET_COUNT(0);

}

void drive(int percent = 64)
{
    int val = percent*6.25;
    OC1RS = val;
    TRISBbits.TRISB14 = 1;
    TRISBbits.TRISB15 = 1;

}

void drive_dist(float dist)
{
    OC1RS = 400;
    int drive_count = 0;
    TRISBbits.TRISB14 = 1;
    TRISBbits.TRISB15 = 1;

    while (drive_count < dist*DISTANCE_CONVERSION)
    {
        drive_count++;
    }
    OC1RS = 0;
    TRISBbits.TRISB14 = 0;
    TRISBbits.TRISB15 = 0;


}

void drive_off()
{
    OC1RS = 0;
    TRISBbits.TRISB14 = 0;
    TRISBbits.TRISB15 = 0;
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

void arm(int direction){

    if (direction==UP){
        OC4RS=UP;
    }

    else if (direction==DOWN){
        OC4RS=DOWN;
    }

}