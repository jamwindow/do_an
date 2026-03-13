/*
 * global.c
 *
 *  Created on: Mar 13, 2026
 *      Author: ASUS
 */

#include"global.h"


///////////////////////////////////////////
Motor motor = {0.02,0.2,1.0};
PID pidL,pidR;
ESO esoL,esoR;
float cmd_v = 0;
float cmd_w = 0;

uint32_t last_cmd_time = 0;
///////////////////////////////////////////
float wheel_base = 0.5;
float wheel_radius = 0.1;

float wL_ref = 0;
float wR_ref = 0;
////////////////////////////////////////////
float wL_meas = 0;
float wR_meas = 0;

int32_t lastL = 0;
int32_t lastR = 0;
////////////////////////////////////////////
uint8_t rx_buf[8];
cmd_vel_packet rx_packet;
