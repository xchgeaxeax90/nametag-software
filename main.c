#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "pwm.h"
#include "pins.h"
#include "timer.h"
#include "animation.h"


void init_clock();

// Called periodically by TCB0 to update the multiplexing for the eyes and top LEDs
static volatile uint8_t eye_en = 0;
void multiplex_update(void){
    CATHODE_PORT.OUTSET = CAT0_bm | CAT1_bm;
    // Toggle the multiplex driver pins
    if(update_animation()){

	write_pwm(&animation_ptr->pwm_settings);
    }
    write_pwm_multiplexed(&animation_ptr->pwm_settings, ~eye_en);
    eye_en = ~eye_en;
    // Set the actual multiplex pins on the TCA interrupt, so they're synced to the PWM period
    TCA0.SPLIT.INTFLAGS = TCA_SPLIT_HUNF_bm;
    TCA0.SPLIT.INTCTRL = TCA_SPLIT_HUNF_bm;
}

ISR(TCA0_HUNF_vect) {
    if(eye_en){
	CATHODE_PORT.OUTCLR = CAT0_bm;
    } else {
	CATHODE_PORT.OUTCLR = CAT1_bm;
    }
    TCA0.SPLIT.INTFLAGS = TCA_SPLIT_HUNF_bm;
    TCA0.SPLIT.INTCTRL = 0;
}


int main(void){
    init_clock();

    init_pins();
    //init_button_interrupt();

    init_pwm();

    init_timer();

    sei();
    while(1){
	_delay_ms(500);

    }
}


void init_clock(void){
    // Select the HF RC oscillator
    _PROTECTED_WRITE(CLKCTRL.MCLKCTRLA, CLKCTRL_CLKSEL_OSCHF_gc);
    // Wait until clock switch is over
    while(CLKCTRL.MCLKSTATUS & CLKCTRL_SOSC_bm) {}

    // Select 1MHz, no run standby
    _PROTECTED_WRITE(CLKCTRL.OSCHFCTRLA, CLKCTRL_FRQSEL_1M_gc);

}

