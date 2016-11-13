/*
 * common.h
 *
 *  Created on: 12.11.2016
 *      Author: x
 */

#ifndef INC_COMMON_H_
#define INC_COMMON_H_


void delay_pool(unsigned int msec);
void led_blink(unsigned int msec_on, unsigned int msec_off, unsigned int count);
void blink_hex_byte (unsigned int num, unsigned int count);
void blink_hex_word (unsigned int num, unsigned int count);

#endif /* INC_COMMON_H_ */
