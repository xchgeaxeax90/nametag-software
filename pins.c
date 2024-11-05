#include <avr/io.h>
#include "pins.h"
#include <avr/interrupt.h>

void init_pins(void){
    PORTA.DIR = 0;
    PORTC.DIR = 0;
    PORTD.DIR = 0;

    PWM0to5_PORT.DIRSET = PWM0_bm | PWM1_bm | PWM2_bm | PWM3_bm | PWM4_bm | PWM5_bm;
    CATHODE_PORT.DIRSET = CAT0_bm | CAT1_bm;

    PWM67_PORT.DIRSET = PWM6_bm | PWM7_bm;
    BTN_PORT.DIRCLR = BTN_bm;
    BTN_PORT.PINCONFIG = PORT_PULLUPEN_bm | PORT_INVEN_bm;
    BTN_PORT.PINCTRLUPD = BTN_bm;

    // Select the cathode controlling the top by driving CAT1 LOW. 
    CATHODE_PORT.OUTSET = CAT0_bm;
    CATHODE_PORT.OUTCLR = CAT1_bm;
}

void init_button_interrupt(void){
    // Set the button pin as a pin change interrupt on both edges, and enable the pullup

}


// In the future we might want to set the button up as the TCB1 input
// and have it sense how long the button is held
ISR(PORTC_PORT_vect) {

    // Clear the CAPT interrupt
    PORTC.INTFLAGS = BTN_bm;
}
