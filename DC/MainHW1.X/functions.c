#include "functions.h"

int error_p=0;
int error_i=0;
int error_d=0;
int error_previous=0;

//void __ISR(_TIMER_1_VECTOR,IPL6SOFT) Wall_Sensor_Interrupt(void){

    //LED_correct();

//}

int readADC1(void) {

    ANSELAbits.ANSA0 = 1; //sets up A0 as AN0
    AD1CON3bits.ADCS = 3;
    AD1CHSbits.CH0SA = 0;
    AD1CON1bits.ADON = 1;

    int elapsed = 0;
    int finishtime = 0;
    int sampletime = 20;
    int a = 0;

    AD1CON1bits.SAMP = 1;
    elapsed = _CP0_GET_COUNT();
    finishtime = elapsed + sampletime;
    while (_CP0_GET_COUNT() < finishtime) {
    }
    AD1CON1bits.SAMP = 0;
    while (!AD1CON1bits.DONE) {
    }
    a = ADC1BUF0;
    return a;
}

int readADC2(void) {

    ANSELAbits.ANSA1 = 1; //sets up A0 as AN0
    AD1CON3bits.ADCS = 3;
    AD1CHSbits.CH0SA = 1;
    AD1CON1bits.ADON = 1;

    int elapsed = 0;
    int finishtime = 0;
    int sampletime = 20;
    int b = 0;

    AD1CON1bits.SAMP = 1;
    elapsed = _CP0_GET_COUNT();
    finishtime = elapsed + sampletime;
    while (_CP0_GET_COUNT() < finishtime) {
    }
    AD1CON1bits.SAMP = 0;
    while (!AD1CON1bits.DONE) {
    }
    b = ADC1BUF0;
    return b;
}

int readADC3(void) {

    ANSELBbits.ANSB1 = 1; //sets up A0 as AN0
    AD1CON3bits.ADCS = 3;
    AD1CHSbits.CH0SA = 3;
    AD1CON1bits.ADON = 1;

    int elapsed = 0;
    int finishtime = 0;
    int sampletime = 20;
    int b = 0;

    AD1CON1bits.SAMP = 1;
    elapsed = _CP0_GET_COUNT();
    finishtime = elapsed + sampletime;
    while (_CP0_GET_COUNT() < finishtime) {
    }
    AD1CON1bits.SAMP = 0;
    while (!AD1CON1bits.DONE) {
    }
    b = ADC1BUF0;
    return b;
}


void wait(int milliseconds){

    int count=milliseconds*20000;

    _CP0_SET_COUNT(0);

    while(_CP0_GET_COUNT()< count){
        continue;
    }

    _CP0_SET_COUNT(0);

}

void LED_correct(int reference, int detected,int kp,int ki,int kd,int divisor){
    
    double effort=calculate_effort(reference,detected,kp,ki,kd);

        OC1RS=OC1RS+(effort/divisor);

}

double calculate_effort(int reference, int detected, int kp, int ki, int kd){

    error_p=reference-detected; //errors are all global variables defined in functions.h
    error_i=error_i+error_p;
    error_d=error_p-error_previous;

    double effort=(kp*error_p)+(ki*error_i)+(kd*error_d);

    error_previous=error_p;

    return effort;

}



int volts_to_duty(double volts, double max_volts, int max_duty){

    int duty = (volts/max_volts)*max_duty;
    return duty;

}


double duty_to_volts(int duty, int max_duty, double max_volts){

    double volts = (duty/max_duty)*max_volts;
    return volts;

}

void ADC1_tune(int *ADC_min,int *ADC_max){ //light will turn on, put hand in front of sensor, wait
    //for light to turn back off, take hand away, light will turn back on, keep hand away, and once
    //light is off, values are recorded.

    LATBbits.LATB15=1;
    wait(3000);
    (*ADC_min)=readADC1();
    LATBbits.LATB15=0;
    wait(3000);
    LATBbits.LATB15=1;
    wait(3000);
    (*ADC_max)=readADC1();
    LATBbits.LATB15=0;

    
}


/*
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

}*/