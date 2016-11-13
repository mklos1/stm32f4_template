/*
 * main.c
 *
 *  Created on: 07.11.2016
 *      Author: x
 */

#include "stm32f4xx.h"

#include "stm32f4xx_conf.h"
#include "common.h"
#include "port_config.h"

extern int main(void);

int main (void) {

	MCU_init();

	while(1) {
		delay_pool(5000);
		GPIO_ResetBits(LED_PORT, LED_PIN);
		while (1) {
			led_blink(500, 500, 1);
		}
	}

	return 0;
}

