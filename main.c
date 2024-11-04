#include <avr/io.h>
#include <util/delay.h>
#include "pwm.h"

void init_clock(void){
    // Select the HF RC oscillator
    _PROTECTED_WRITE(CLKCTRL.MCLKCTRLA, CLKCTRL_CLKSEL_OSCHF_gc);
    // Wait until clock switch is over
    while(CLKCTRL.MCLKSTATUS & CLKCTRL_SOSC_bm) {}

    // Select 1MHz, no run standby
    _PROTECTED_WRITE(CLKCTRL.OSCHFCTRLA, CLKCTRL_FRQSEL_1M_gc);

}

void init_pins(void){
    PORTA.DIR = 0xFF;
    PORTD.DIR = PIN4_bm | PIN5_bm;
    PORTC.DIR = 0;
}


int main(void){
    init_clock();

    init_pins();

    init_pwm();

    while(1){
	PORTD.OUTTGL = PIN4_bm | PIN5_bm;
	_delay_ms(100);

    }
}
