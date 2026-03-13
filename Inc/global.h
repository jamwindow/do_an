/*
 * global.h
 *
 *  Created on: Mar 13, 2026
 *      Author: ASUS
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include <math.h>
#include <stdint.h>

#define CONTROL_DT 0.001f
#define MAX_WHEEL_SPEED 10.0f
#define CMD_TIMEOUT_MS 200
#define PWM_MAX 1000
#define PPR 2400
#define MAX_ACCEL 20.0f

typedef struct{
    float kp,ki,kd;
    float integral;
    float prev_err;
    float prev_deriv;
}PID;

typedef struct{
    float z1;
    float z2;
    float beta1;
    float beta2;
}ESO;

typedef struct{
    float J;
    float B;
    float Kt;
}Motor;

extern Motor motor;
extern PID pidL,pidR;
extern ESO esoL,esoR;

extern float cmd_v;
extern float cmd_w;

extern uint32_t last_cmd_time;
////////////////////////////////////////////
extern float wheel_base;
extern float wheel_radius;

extern float wL_ref;
extern float wR_ref;

extern float wL_meas;
extern float wR_meas;

extern int32_t lastL;
extern int32_t lastR;
////////////////////////////////////////////
extern uint8_t rx_buf[8];

typedef struct
{
    float v;
    float w;
} cmd_vel_packet;

extern cmd_vel_packet rx_packet;

#endif /* INC_GLOBAL_H_ */
