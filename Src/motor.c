/*
 * motor.c
 *
 *  Created on: Mar 11, 2026
 *      Author: ASUS
 */
#include "motor.h"
#include "tim.h"
#include <math.h>
#include "gpio.h"
#include "main.h"

#define PWM_MAX 1000

void motor_set_pwm(float uL, float uR)
{
    int pwmL = (int)(fabs(uL) / 12.0f * PWM_MAX);
    int pwmR = (int)(fabs(uR) / 12.0f * PWM_MAX);

    if(pwmL > PWM_MAX) pwmL = PWM_MAX;
    if(pwmR > PWM_MAX) pwmR = PWM_MAX;

    if(pwmL < 20) pwmL = 0;
    if(pwmR < 20) pwmR = 0;

    HAL_GPIO_WritePin(GPIOD, EnableLeft_Pin,
                      (uL >= 0) ? GPIO_PIN_SET : GPIO_PIN_RESET);

    HAL_GPIO_WritePin(GPIOD, EnableRight_Pin,
                      (uR >= 0) ? GPIO_PIN_SET : GPIO_PIN_RESET);

    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, pwmL);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, pwmR);


}

