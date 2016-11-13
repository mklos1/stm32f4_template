/*
 * common.c
 *
 *  Created on: 12.11.2016
 *      Author: x
 */

#include "stm32f4xx_conf.h"
#include "port_config.h"

void delay_pool(unsigned int msec){
	RCC_ClocksTypeDef temp;
	unsigned int cnt;
	RCC_GetClocksFreq(&temp);
	for (cnt = msec * (temp.HCLK_Frequency/4000); cnt > 0; cnt--);
}

void led_blink(unsigned int msec_on, unsigned int msec_off, unsigned int count) {
	for (; count > 0; count--) {
		GPIO_SetBits(LED_PORT, LED_PIN);
		delay_pool(msec_on);
		GPIO_ResetBits(LED_PORT, LED_PIN);
		delay_pool(msec_off);
	}

}

void blink_hex_byte (unsigned int num, unsigned int count) {
	for (; count > 0; count--) {
		led_blink(50, 500, (num & 0xF0) >> 4);
		delay_pool(2000);
		led_blink(50, 500, num & 0xF);
		delay_pool(5000);
	}
}

void blink_hex_word (unsigned int num, unsigned int count) {
	for (; count > 0; count--) {
		led_blink(50, 500, (num & 0xF000) >> 12);
		delay_pool(2000);
		led_blink(50, 500, (num & 0x0F00) >> 8);
		delay_pool(2000);
		led_blink(50, 500, (num & 0x00F0) >> 4);
		delay_pool(2000);
		led_blink(50, 500, num & 0xF);
		delay_pool(5000);
	}
}
