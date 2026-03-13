/*
 * control.c
 *
 *  Created on: Mar 11, 2026
 *      Author: ASUS
 */


#include "control.h"
#include "encoder.h"
#include "motor.h"
#include "diff_drive.h"
#include <math.h>

#include "stm32f4xx_hal.h"



//
//Motor motor = {0.02,0.2,1.0};
//
//PID pidL,pidR;
//ESO esoL,esoR;
//
//float cmd_v = 0;
//float cmd_w = 0;
//
//uint32_t last_cmd_time = 0;
//
//#define CMD_TIMEOUT_MS 200

float pid_update(PID *pid,float ref,float meas,float dt)
{
    float err = ref-meas;

    if(fabs(ref)<0.01)
        pid->integral = 0;

    pid->integral += err*dt;

    if(pid->integral>5) pid->integral=5;
    if(pid->integral<-5) pid->integral=-5;

    float deriv=(err-pid->prev_err)/dt;
    deriv = 0.7*deriv + 0.3*pid->prev_deriv;

    pid->prev_deriv = deriv;
    pid->prev_err = err;

    return pid->kp*err + pid->ki*pid->integral + pid->kd*deriv;
}

float feedforward(float w_ref,float *prev,float dt)
{
    float u = motor.B*w_ref +
              motor.J*(w_ref-*prev)/dt;

    *prev = w_ref;

    return u;
}

void eso_update(ESO *eso,float y,float u,float dt)
{
	float e = y - eso->z1;

    float b0=motor.Kt/motor.J;

    eso->z1 += dt*(eso->z2 + b0*u - eso->beta1*e);
    eso->z2 += dt*(-eso->beta2*e);
}

float control_step(PID *pid,ESO *eso,
                   float ref,float meas,float u_ff,float dt)
{
    float u_pid = pid_update(pid,ref,meas,dt);

    float u = u_pid + u_ff;

    if(u>12) u=12;
    if(u<-12) u=-12;

    u -= eso->z2;

    eso_update(eso,meas,u,dt);

    return u;
}

void control_init()
{
    pidL.kp=3;
    pidL.ki=10;
    pidL.kd=0.05;

    pidR=pidL;

    esoL.beta1=50;
    esoL.beta2=1500;

    esoR=esoL;
}

void control_loop()
{
//    float dt=0.001;

    if(HAL_GetTick() - last_cmd_time > CMD_TIMEOUT_MS)
    {
        cmd_v = 0;
        cmd_w = 0;
    }

    encoder_update(CONTROL_DT);

    diff_drive_compute(cmd_v, cmd_w);

    /* wheel speed limit */
    if(wL_ref > MAX_WHEEL_SPEED)  wL_ref = MAX_WHEEL_SPEED;
    if(wL_ref < -MAX_WHEEL_SPEED) wL_ref = -MAX_WHEEL_SPEED;

    if(wR_ref > MAX_WHEEL_SPEED)  wR_ref = MAX_WHEEL_SPEED;
    if(wR_ref < -MAX_WHEEL_SPEED) wR_ref = -MAX_WHEEL_SPEED;

    /* acceleration limit */
    static float prev_wL = 0;
    static float prev_wR = 0;

    float max_step = MAX_ACCEL * CONTROL_DT;

    if(wL_ref - prev_wL > max_step)  wL_ref = prev_wL + max_step;
    if(wL_ref - prev_wL < -max_step) wL_ref = prev_wL - max_step;

    if(wR_ref - prev_wR > max_step)  wR_ref = prev_wR + max_step;
    if(wR_ref - prev_wR < -max_step) wR_ref = prev_wR - max_step;

    prev_wL = wL_ref;
    prev_wR = wR_ref;

    static float prevL = 0;
    static float prevR = 0;

    float u_ffL = feedforward(wL_ref,&prevL,CONTROL_DT);
    float u_ffR = feedforward(wR_ref,&prevR,CONTROL_DT);

    float uL=control_step(&pidL,&esoL,wL_ref,wL_meas,u_ffL,CONTROL_DT);
    float uR=control_step(&pidR,&esoR,wR_ref,wR_meas,u_ffR,CONTROL_DT);

    motor_set_pwm(uL,uR);
}
