#pragma once

// Lightstick L - PWM6
// Lightstick R - PWM7
// Face Bottom L - PWM3
// Face Bottom C - PWM0
// Face Bottom R - PWM1
// Eye L - PWM5 Cathode 0
// Eye R - PWM4 Cathode 0
// Face Top L - PWM5 Cathode 1
// Face Top R - PWM4 Cathode 1
// Face Top C - PWM2

#define PWM0 PA0
#define PWM1 PA1
#define PWM2 PA2
#define PWM3 PA3
#define PWM4 PA4
#define PWM5 PA5

#define PWM6 PD4
#define PWM7 PD5

#define CATHODE_PORT PORTA
#define CAT0_bi PIN6_bi
#define CAT1_bi PIN7_bi
#define CAT0_bm PIN6_bm
#define CAT1_bm PIN7_bm

#define BTN PC1
