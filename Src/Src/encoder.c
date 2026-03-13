/*
 * encoder.c
 *
 *  Created on: Mar 11, 2026
 *      Author: ASUS
 */


#include "encoder.h"
#include "tim.h"
#include <math.h>


//#define PPR 2400
//
//float wL_meas = 0;
//float wR_meas = 0;
//
//static int32_t lastL = 0;
//static int32_t lastR = 0;

void encoder_update(float dt)
{
	int32_t cntL = __HAL_TIM_GET_COUNTER(&htim5);// left
	int32_t cntR = __HAL_TIM_GET_COUNTER(&htim2);// right

    int32_t dL = cntL - lastL;
    int32_t dR = cntR - lastR;

    // Handle 16-bit counter wrap-around (TIM2/5 configured with period 65535)
    if (dL > 32767)  dL -= 65536;
    else if (dL < -32767) dL += 65536;

    if (dR > 32767)  dR -= 65536;
    else if (dR < -32767) dR += 65536;

    lastL = cntL;
    lastR = cntR;

    wL_meas = (float)dL * 2.0f * M_PI / PPR / dt;
    wR_meas = (float)dR * 2.0f * M_PI / PPR / dt;
}
