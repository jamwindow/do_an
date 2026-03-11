/*
 * uart.c
 *
 *  Created on: Mar 11, 2026
 *      Author: ASUS
 */
#include "usart.h"
#include "uart.h"
#include "diff_drive.h"


uint8_t rx_buf[8];

void set_cmd_vel(float v, float w)
{
    float L = 0.30;   // khoảng cách 2 bánh
    float R = 0.05;   // bán kính bánh

    wL_ref = (v - 0.5*L*w)/R;
    wR_ref = (v + 0.5*L*w)/R;
}
