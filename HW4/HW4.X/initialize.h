/*
 * File:   initialize.h
 * Author: Vince
 *
 * Created on April 1, 2015, 9:50 PM
 */



#ifndef __INITIALIZE_H
#define	__INITIALIZE_H

#define LED1 LATBbits.LATB7
#define LED2 LATBbits.LATB15
#define USER LATBbits.LATB13



int readADC(void);
void PIC32startup(void);


#endif