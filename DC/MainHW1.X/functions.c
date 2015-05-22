#include "functions.h"


static int global_duty=475;
static int ADC_min;
static int ADC_max;
static int error_p;
static int error_i=0;
static int error_d=0;
static int error_previous=0;


void __ISR(_TIMER_1_VECTOR,IPL6SOFT) Wall_Sensor_Interrupt(void){




    /*
    int reading=readADC1();
    //reading=(int)(reading*1.8);

    OC5RS= reading+50;
    //follow_wall_left(200,reading,1,0,0);
    //follow_wall_right(ADC_max,readADC2(),10,10,1);
    IFS0bits.T1IF = 0;
*/
    IFS0bits.T1IF = 0;
}



void wait(int milliseconds){

    int count=milliseconds*20000;

    int time=_CP0_GET_COUNT();

    while((_CP0_GET_COUNT()-time)< count){
        continue;
    }

    _CP0_SET_COUNT(0);

}

/*void LED_correct(int reference, int detected,int kp,int ki,int kd,int divisor){
    
    double effort=calculate_effort(reference,detected,kp,ki,kd);

        OC1RS=detected+(int)(effort/divisor);

}*/


void follow_wall_left(int reference, int detected, int kp, int ki, int kd){

    double effort=calculate_effort(reference,detected,kp,ki,kd);
    double conversion=0.61; //conversion factor of ADC ticks to duty cycle
    //double conversion=.061;
    //double conversion=1;
    double duty = conversion*effort;
    int duty_int=duty;


    OC5RS=duty_int+global_duty;
    global_duty+=global_duty+duty_int;

}

void follow_wall_right(int reference, int detected, int kp, int ki, int kd){

    double effort=calculate_effort(reference,detected,kp,ki,kd);
    double conversion=0.61; //conversion factor of ADC ticks to duty cycle
    //double conversion=1;
    int duty = conversion*effort;


    OC1RS=duty+global_duty;
    global_duty+=duty;

}


double calculate_effort(int reference, int detected, int kp, int ki, int kd){

    error_p=detected-reference; //errors are all global variables defined in functions.h
    error_i=error_i+error_p;
    error_d=error_p-error_previous;

    double effort=(kp*error_p)+(ki*error_i)+(kd*error_d);

    error_previous=error_p;

    if (effort>100){
        effort=100;
    }
    if(effort<-100){
        effort=-100;
    }

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

void ADC1_tune(void){ //light will turn on, put hand in front of sensor, wait
    //for light to turn back off, take hand away, light will turn back on, keep hand away, and once
    //light is off, values are recorded.

    LATBbits.LATB15=1;
    wait(3000);
    ADC_max=readADC1();
    LATBbits.LATB15=0;
    wait(3000);
    LATBbits.LATB15=1;
    wait(3000);
    ADC_min=readADC1();
    LATBbits.LATB15=0;

    
}

void ADC2_tune(int *ADC_min,int *ADC_max){ //light will turn on, put hand in front of sensor, wait
    //for light to turn back off, take hand away, light will turn back on, keep hand away, and once
    //light is off, values are recorded.

    LATBbits.LATB15=1;
    wait(3000);
    (*ADC_max)=readADC2();
    LATBbits.LATB15=0;
    wait(3000);
    LATBbits.LATB15=1;
    wait(3000);
    (*ADC_min)=readADC2();
    LATBbits.LATB15=0;


}


void ADC4_tune(void){ //light will turn on, put hand in front of sensor, wait
    //for light to turn back off, take hand away, light will turn back on, keep hand away, and once
    //light is off, values are recorded.

    LATBbits.LATB15=1;
    wait(3000);
    ADC_max=readADC4();
    LATBbits.LATB15=0;
    wait(3000);
    LATBbits.LATB15=1;
    wait(3000);
    ADC_min=readADC4();
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

    ANSELAbits.ANSA1 = 1; //sets up A1 as AN1
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

    ANSELBbits.ANSB1 = 1; //sets up B1 as AN3
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


int readADC4(void) {

    ANSELBbits.ANSB0 = 1; //sets up B0 as AN2
    AD1CON3bits.ADCS = 3;
    AD1CHSbits.CH0SA = 2;
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


int readADC5(void) {

    ANSELBbits.ANSB3 = 1; //sets up B3 as AN5
    AD1CON3bits.ADCS = 3;
    AD1CHSbits.CH0SA = 5;
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

void timer1_initialize(void){

    //PR1=1000-1; //sets up timer 1 to run at 5kHz for wall sensor interrupt
    PR1=31250-1; //5 Hz
    TMR1=0;
    //T1CONbits.TCKPS=0b01;
    T1CONbits.TCKPS=0b11; //256 presscaler
    T1CONbits.TGATE=0;
    T1CONbits.TCS=0;
    
    
}

void interrupt_enable(void){
    
    IPC1bits.T1IP=6;
    IPC1bits.T1IS=0;
    IFS0bits.T1IF=0;
    IEC0bits.T1IE=1;
    T1CONbits.ON=1;

}

void interrupt_disable(void){

    IFS0bits.T1IF=0;
    IEC0bits.T1IE=0;
    T1CONbits.ON=0;

}