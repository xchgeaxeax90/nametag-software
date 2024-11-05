#include "animation.h"
#include <avr/interrupt.h>
#include <avr/io.h>

#include "python/animation_circle.inc"
#include "python/animation_breathe.inc"

const __flash animation_data_t* animation_array[] = {
    animation_circle,
    animation_breathe
};
const __flash uint8_t animation_sizes[] = {
    sizeof(animation_circle)/sizeof(animation_circle[0]),
    sizeof(animation_breathe)/sizeof(animation_breathe[0]),
};

const __flash animation_data_t *animation_ptr = &animation_circle[0];

uint16_t timeout_counter = 0;
uint8_t animation_idx = 0;
uint8_t selected_animation = 0;
uint8_t update_animation(void){
    if(timeout_counter >= animation_ptr->timeout){
	timeout_counter = 0;
	animation_idx += 1;
	if(animation_idx >= animation_sizes[selected_animation]){
	    animation_idx = 0;
	}
	cli();
	animation_ptr = &animation_array[selected_animation][animation_idx];
	sei();
	return 1;
    } else {
	timeout_counter = timeout_counter + 1;
	return 0;
    }
}

void select_animation(void){
    cli();
    selected_animation += 1;
    if(selected_animation >= sizeof(animation_sizes)/sizeof(animation_sizes[0])){
	selected_animation = 0;
    }
    animation_idx = 0;
    timeout_counter = 0;
    sei();
}
