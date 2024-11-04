#include <avr/io.h>
#include "pwm.h"

// Taken almost straight from the TCA Technical Brief
static void init_timera(void){
    // Enable split mode
    TCA0.SPLIT.CTRLD = TCA_SPLIT_SPLITM_bm;
    // Enable all PWM outputs
    TCA0.SPLIT.CTRLB = TCA_SPLIT_HCMP0EN_bm | TCA_SPLIT_HCMP1EN_bm | TCA_SPLIT_HCMP2EN_bm |
	TCA_SPLIT_LCMP0EN_bm | TCA_SPLIT_LCMP1EN_bm | TCA_SPLIT_LCMP2EN_bm;
    // Configure both halves of the timer for a full period
    TCA0.SPLIT.HPER = 0xff;
    TCA0.SPLIT.LPER = 0xff;
    // With a 1MHz clock, the PWM will have a period of 3KHz, which seems like plenty
    TCA0.SPLIT.CTRLA = TCA_SPLIT_RUNSTDBY_bm | TCA_SPLIT_CLKSEL_DIV1_gc | TCA_SPLIT_ENABLE_bm;
}

static void timerd_enable_sync(void){
    while(!(TCD0.STATUS & TCD_ENRDY_bm)) {}
}

static void timerd_command_sync(void){
    while(!(TCD0.STATUS & TCD_CMDRDY_bm)) {}
}


// Taken almost straight from the TCD Technical Brief
static void init_timerd(void){
    // Configure the waveform generation for one slope mode - most similar to TCA PWM
    TCD0.CTRLB = TCD_WGMODE_ONERAMP_gc;

    // Set the CMPC and CMPD outputs to output from PWMA and PWMB
    TCD0.CTRLC = TCD_CMPCSEL_PWMA_gc | TCD_CMPDSEL_PWMB_gc | TCD_AUPDATE_bm;

    TCD0.CMPBCLRL = 0xff;
    TCD0.CMPBCLRH = 0;
    TCD0.CMPACLRL = 0xff;
    TCD0.CMPACLRH = 0;


    // Wait for the enable bit to be synchronized to the clock domain
    timerd_enable_sync();
    // Enable the timer, select the system clock as the clock source, divide by 1
    TCD0.CTRLA = TCD_CLKSEL_CLKPER_gc | TCD_CNTPRES_DIV1_gc | TCD_SYNCPRES_DIV1_gc | TCD_ENABLE_bm;

    // Enable CMPC and CMPD outputs
    _PROTECTED_WRITE(TCD0.FAULTCTRL, TCD_CMPCEN_bm | TCD_CMPDEN_bm);

}

void init_pwm(void){
    init_timera();
    init_timerd();
}

void write_pwm(const pwm_settings *pwm_settings){
    TCA0.SPLIT.LCMP0 = pwm_settings->face_bot_c;
    TCA0.SPLIT.LCMP1 = pwm_settings->face_bot_r;
    TCA0.SPLIT.LCMP2 = pwm_settings->face_top_c;
    TCA0.SPLIT.HCMP0 = pwm_settings->face_bot_l;

    timerd_command_sync();
    TCD0.CMPASET = 255-pwm_settings->light_l;
    TCD0.CMPBSET = 255-pwm_settings->light_r;
    TCD0.CMPBCLRH = 0;
}


void write_pwm_multiplexed(const pwm_settings *pwm_settings, uint8_t eye_sel){
    if(eye_sel){
	TCA0.SPLIT.HCMP1 = pwm_settings->eye_r;
	TCA0.SPLIT.HCMP2 = pwm_settings->eye_l;
    } else {
	TCA0.SPLIT.HCMP1 = pwm_settings->face_top_r;
	TCA0.SPLIT.HCMP2 = pwm_settings->face_top_l;
    }

}