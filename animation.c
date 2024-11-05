#include "animation.h"
#include <avr/interrupt.h>
#include <avr/io.h>

#include "python/animation.inc"
const __flash animation_data_t *animation_ptr = &animation[0];

uint16_t timeout_counter = 0;
uint8_t animation_idx = 0;
uint8_t update_animation(void){
    if(timeout_counter >= animation_ptr->timeout){
	timeout_counter = 0;
	animation_idx += 1;
	if(animation_idx >= sizeof(animation)/sizeof(animation[0])){
	    animation_idx = 0;
	}
	cli();
	animation_ptr = &animation[animation_idx];
	sei();
	return 1;
    } else {
	timeout_counter = timeout_counter + 1;
	return 0;
    }
}
