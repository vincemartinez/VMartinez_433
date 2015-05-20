#include "initialize.h"
#include <xc.h>
#include <sys/attribs.h>


/* Hi Curtis!!!! to control the speed of the drive motors, change the value of
 * OC1RS. It ranges from 0 to 625. To change motors 1 and 2
 * from forward to backward, invert pin B14 (digital output 1). to change
 * motors 3 and 4 from forward to backward, invert pin B15 (digital output 2).
 *
 * To change the position of servo motors 1 and 2, change OC2RS. It ranges
 * from 85 (-90 degrees) to 385 (90 degrees). To change the position of servo
 * motors 3 and 4, change OC3RS (it is the same range as OC2RS).*/


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
//#pragma config FWDTWINSZ = WINSZ_25 // wdt window at 25%

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

    ANSELBbits.ANSB14=0;

    TRISBbits.TRISB14=0; //sets B14 to digital output 1 for motor direction
    TRISBbits.TRISB15=0; //sets B15 to digital output 2 for motor direction (also controls LED2)
    
    RPB7Rbits.RPB7R=0b0101; //sets B7 to PWM signal for left (or right) drive motor speed (also controls LED3)
    RPB8Rbits.RPB8R=0b0101; //sets B8 to PWM signal for servo motor position
    RPB9Rbits.RPB9R=0b0101; //sets B9 to PWM signal for servo motor position
    RPA4Rbits.RPA4R=0b0101; //sets A4 to PWM signal for arm servo motor position
    RPB2Rbits.RPB2R=0b0110; //sets B2 to PWM signal for left (or right) drive motor speed

    OC1CONbits.OCM=0b110; //enable OC1
    OC1CONbits.OCTSEL=0;
    OC1RS=0;
    OC1R=0;
    OC1CONbits.ON=1;

    OC2CONbits.OCM=0b110; //enable OC2
    OC2CONbits.OCTSEL=1;
    OC2RS=0;  //set OC2RS to 85 for maximum in one direction, 385 for max in other direction
    OC2R=0;
    OC2CONbits.ON=1;

    OC3CONbits.OCM=0b110; //enable OC3
    OC3CONbits.OCTSEL=1;
    OC3RS=0;  //set OC3RS to 85 for maximum in one direction, 385 for max in other direction
    OC3R=0;
    OC3CONbits.ON=1;

    OC4CONbits.OCM=0b110; //enable OC4
    OC4CONbits.OCTSEL=1;
    OC4RS=0;  //set OC4RS to 85 for maximum in one direction, 385 for max in other direction
    OC4R=0;
    OC4CONbits.ON=1;

    OC5CONbits.OCM=0b110; //enable OC5
    OC5CONbits.OCTSEL=0;
    OC5RS=0;  
    OC5R=0;
    OC5CONbits.ON=1;

    /*PR1=1000-1; //sets up timer 1 to run at 5kHz for wall sensor interrupt
    TMR1=0;
    T1CONbits.TCKPS=0b01;
    T1CONbits.TGATE=0;
    T1CONbits.TCS=0;
    IPC1bits.T1IP=6;
    IPC1bits.T1IS=0;
    IFS0bits.T1IF=0;
    IEC0bits.T1IE=1;
    T1CONbits.ON=1;*/

    PR2=625-1; //sets up timer 2 to run at 1kHz for motor drive
    TMR2=0;
    T2CONbits.TCKPS=0b110;
    T2CONbits.TGATE=0;
    T2CONbits.TCS=0;
    T2CONbits.ON=1;

    PR3=3125-1; //sets up timer 2 to run at 50Hz for servo control
    TMR3=0;
    T3CONbits.TCKPS=0b111;
    T3CONbits.TGATE=0;
    T3CONbits.TCS=0;
    T3CONbits.ON=1;





    /*
    ANSELAbits.ANSA0 = 1; //sets up A0 as AN0
    AD1CON3bits.ADCS = 3;
    AD1CHSbits.CH0SA = 0;
    AD1CON1bits.ADON = 1;
    */

    //ANSELBbits.ANSB13 = 1; //sets up B13 as AN0

}




