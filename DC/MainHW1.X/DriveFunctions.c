#include "DriveFunctions.h"
#include "initialize.h"
#include <xc.h>
#define DISTANCE_CONVERSION 40000000 //Tics per inch (need to fine tune)

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