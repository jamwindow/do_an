/*
 * uart.h
 *
 *  Created on: Mar 11, 2026
 *      Author: ASUS
 */

#ifndef INC_UART_H_
#define INC_UART_H_

extern uint8_t rx_buf[8];

typedef struct
{
    float v;
    float w;
} cmd_vel_packet;

extern cmd_vel_packet rx_packet;

void set_cmd_vel(float v, float w);

#endif /* INC_UART_H_ */
