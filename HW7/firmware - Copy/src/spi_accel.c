#include "accel.h"
#include <xc.h>
// interface with the LSM303D accelerometer/magnetometer using spi
// Wire GND to GND, VDD to 3.3V, 
// SDO1             -> SDI (labeled SDA),
// SDI1             -> SDO
// SCK1 (B14)       -> SCL
// some digital pin -> CS

#define CS LATAbits.LATA4 // replace x with some digital pin

// send a byte via spi and return the response
unsigned char spi_io(unsigned char o) {
  SPI1BUF = o;
  while(!SPI1STATbits.SPIRBF) { // wait to receive the byte
    ;
  }
  return SPI1BUF;
}


// read data from the accelerometer, given the starting register address.
// return the data in data
void acc_read_register(unsigned char reg, unsigned char data[], unsigned int len) {
  unsigned int i;
  reg |= 0x80; // set the read bit (as per the accelerometer's protocol)
  if(len > 1) {
    reg |= 0x40; // set the address auto increment bit (as per the accelerometer's protocol)
  }
  CS = 0;
  spi_io(reg);
  for(i = 0; i != len; ++i) {
    data[i] = spi_io(0); // read data from spi
  }
  CS = 1;
}


void acc_write_register(unsigned char reg, unsigned char data) {
  CS = 0;               // bring CS low to activate SPI
  spi_io(reg);
  spi_io(data);
  CS = 1;               // complete the command
}


void acc_setup() {
  TRISAbits.TRISA4 = 0; // set CS to output and digital if necessary
  CS = 1;

  // select a pin for SDI1

  SDI1Rbits.SDI1R = 0b0001;
  // select a pin for SD01
  RPB2Rbits.RPB2R = 0b0011;

  // Setup the master Master - SPI1
  // we manually control SS as a digital output 
  // since the pic is just starting, we know that spi is off. We rely on defaults here
 
  // setup spi1
  SPI1CON = 0;              // turn off the spi module and reset it
  SPI1BUF;                  // clear the rx buffer by reading from it
  SPI1BRG = 0x3;            // baud rate to 5MHz [SPI1BRG = (40000000/(2*desired))-1]
  SPI1STATbits.SPIROV = 0;  // clear the overflow bit
  SPI1CONbits.CKE = 1;      // data changes when clock goes from active to inactive
                            //    (high to low since CKP is 0)
  SPI1CONbits.MSTEN = 1;    // master operation
  SPI1CONbits.ON = 1;       // turn on spi
 
  // set the accelerometer data rate to 1600 Hz. Do not update until we read values
  acc_write_register(CTRL1, 0xAF); 

  // 50 Hz magnetometer, high resolution, temperature sensor on
  acc_write_register(CTRL5, 0xF0); 

  // enable continuous reading of the magnetometer
  acc_write_register(CTRL7, 0x0);

  acc_write_register(SENSITIVITY, 0x0); // sets sensitivity to +-2g
}

double acc_mouse_x(int x_accel_data, long div) {
    
   double x_weight=(double) x_accel_data /(double)div;
   return(x_weight);
    
}

double acc_mouse_y(int y_accel_data, long div) {

   double y_weight=(double) y_accel_data/(double) div ;
   return(y_weight);

}


void acc_bar_display(int x_accel_data, int y_accel_data) {

    display_clear();

    int i;
    int j;

    //x bars

    int number_of_bars=x_accel_data/500;

    if (number_of_bars<0) {

        for (i=64; i<=(64-number_of_bars); i++) {

            for (j=28; j<=36; j++) {
                display_pixel_set(j, i, 1);
            }

        }

    }

    else {
         for (i=64; i>=(64-number_of_bars); i--) {

            for (j=28; j<=36; j++) {
                display_pixel_set(j,i,1);
            }

        }
    }
       

    //y bars

    number_of_bars=y_accel_data/500;

    if (number_of_bars<0) {

        for (i=32; i<=(32-number_of_bars); i++) {

            for (j=60; j<=68; j++) {
                display_pixel_set(i, j, 1);
            }

        }

    }

    else {

        for (i=32; i>=(32-number_of_bars); i--) {

            for (j=60; j<=68; j++) {
                display_pixel_set(i,j,1);
            }

        }

    }
        
    display_draw();

}