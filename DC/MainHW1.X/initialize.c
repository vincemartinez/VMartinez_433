#include "initialize.h"
#include <xc.h>
#include <sys/attribs.h>


void PIC32startup(void){

    //set up DEVCFGs

    // DEVCFG0
#pragma config DEBUG = OFF // no debugging
#pragma config JTAGEN = OFF // no jtag
#pragma config ICESEL = ICS_PGx1 // use PGED1 and PGEC1
#pragma config PWP = OFF // no write protect
#pragma config BWP = OFF // not boot write protect
#pragma config CP = OFF // no code protect

// DEVCFG1
#pragma config FNOSC = PRIPLL // use primary oscillator with pll
#pragma config FSOSCEN = OFF // turn off secondary oscillator
#pragma config IESO = OFF // no switching clocks
#pragma config POSCMOD = HS // high speed crystal mode
#pragma config OSCIOFNC = OFF // free up secondary osc pins by turning sosc off
#pragma config FPBDIV = DIV_1 // divide CPU freq by 1 for peripheral bus clock
#pragma config FCKSM = CSDCMD // do not enable clock switch
#pragma config WDTPS = PS1048576 // slowest wdt
#pragma config WINDIS = OFF // no wdt window
#pragma config FWDTEN = OFF // wdt off by default
#pragma config FWDTWINSZ = WINSZ_25 // wdt window at 25%

// DEVCFG2 - get the CPU clock to 40MHz
#pragma config FPLLIDIV = DIV_2 // divide input clock to be in range 4-5MHz
#pragma config FPLLMUL = MUL_20 // multiply clock after FPLLIDIV
#pragma config FPLLODIV = DIV_2 // divide clock after FPLLMUL to get 40MHz
#pragma config UPLLIDIV = DIV_2 // divide 8MHz input clock, then multiply by 12 to get 48MHz for USB
#pragma config UPLLEN = ON // USB clock on

// DEVCFG3
#pragma config USERID = 12345 // some 16bit userid, doesn't matter what
#pragma config PMDL1WAY = ON // allow only one reconfiguration
#pragma config IOL1WAY = ON // allow only one reconfiguration
#pragma config FUSBIDIO = ON // USB pins controlled by USB module
#pragma config FVBUSONIO = ON // controlled by USB module



    __builtin_disable_interrupts(); //beginning of startup

    __builtin_mtc0(_CP0_CONFIG, _CP0_CONFIG_SELECT, 0xa4210583);

    BMXCONbits.BMXWSDRM=0x0;
    INTCONbits.MVEC=0x1;
    DDPCONbits.JTAGEN=0;

    __builtin_enable_interrupts(); //end of startup

    ANSELBbits.ANSB13=0; //sets up USER pin as input
    U1RXRbits.U1RXR=0b0011;


    //RPB7Rbits.RPB7R=0b0001; //sets up LED1 pin as a digital output
    TRISBbits.TRISB7=0;

    ANSELBbits.ANSB3=0; //sets up LED1 pin as digital PWM output
    RPB3Rbits.RPB3R=0b0101;


    OC1CONbits.OCM=0b110; //enable OC1
    OC1CONbits.OCTSEL=0;
    OC1RS=0;
    OC1R=0;
    OC1CONbits.ON=1;

    OC2CONbits.OCM=0b110; //enable OC2
    OC2CONbits.OCTSEL=0;
    OC2RS=0;
    OC2R=0;
    OC2CONbits.ON=1;

    PR2=625-1; //sets up timer 2 to run at 1kHz
    TMR2=0;
    T2CONbits.TCKPS=0b110;
    T2CONbits.TGATE=0;
    T2CONbits.TCS=0;
    T2CONbits.ON=1;

    ANSELAbits.ANSA0 = 1; //sets up A0 as AN0
    AD1CON3bits.ADCS = 3;
    AD1CHSbits.CH0SA = 0;
    AD1CON1bits.ADON = 1;

}


int readADC(void) {
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