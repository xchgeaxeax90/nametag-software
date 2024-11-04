#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "pwm.h"
#include "pins.h"
#include "timer.h"


void init_clock();

pwm_settings_t pwm_settings;

// Called periodically by TCB0 to update the multiplexing for the eyes and top LEDs
static volatile uint8_t eye_en = 0;
void multiplex_update(void){
    // Toggle the multiplex driver pins
    CATHODE_PORT.OUTTGL = CAT0_bm | CAT1_bm;
    eye_en = ~eye_en;
    write_pwm_multiplexed(&pwm_settings, eye_en);
}

int main(void){
    init_clock();

    init_pins();
    init_button_interrupt();

    init_pwm();

    init_timer();

    pwm_settings.light_l = 0x40;
    pwm_settings.light_r = 0x20;
    pwm_settings.face_top_l = 0x40;
    pwm_settings.face_top_r = 0x50;
    pwm_settings.eye_l = 0x20;
    pwm_settings.eye_r = 0x10;

    sei();
    while(1){
	PORTD.OUTTGL = PIN4_bm | PIN5_bm;
	_delay_ms(100);

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

