#include <avr/io.h>
#include <util/delay.h>

void init_clock(void){
    // Select the HF RC oscillator
    CLKCTRL.MCLKCTRLA = CLKCTRL_CLKSEL_OSCHF_gc;
    // Select 1MHz, no run standby
    CLKCTRL.OSCHFCTRLA = CLKCTRL_FRQSEL_1M_gc;

}

void init_pins(void){
    PORTA.DIR = 0xFF;
    PORTD.DIR = PIN4_bm | PIN5_bm;
    PORTC.DIR = 0;
}

void init_timer(void){
    // Enable split mode
    TCA0.SPLIT.CTRLD = TCA_SPLIT_SPLITM_bm;
    TCA0.SPLIT.HPER = 0xff;
    TCA0.SPLIT.LPER = 0xff;

    TCA0.SPLIT.CTRLA = TCA_SPLIT_RUNSTDBY_bm | TCA_SPLIT_CLKSEL_DIV1_gc | TCA_SPLIT_ENABLE_bm;

}

int main(void){
    init_clock();

    init_pins();

    init_timer();

    while(1){
	PORTD.OUTTGL = PIN4_bm | PIN5_bm;
	_delay_ms(100);

    }
}
