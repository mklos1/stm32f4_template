#include "stm32f4xx.h"

#include "stm32f4xx_conf.h"

#include "common.h"
#include "port_config.h"

void clocks_init(void);
void interrupts_init(void);
void gpio_init(void);

void MCU_init(void) {
	clocks_init();
	interrupts_init();
	gpio_init();

	// Uruchamiamy nadzór nad poprawnoœci¹ dzia³ania zegara
	RCC_ClockSecuritySystemCmd(ENABLE);

	// Zapalamy diodê, gdy init sprzêtu siê zakoñczy³.
	GPIO_SetBits(LED_PORT, LED_PIN);
}

/*
 * Procesor po resecie dzia³a z wewnêtrznego zegara HSI o czêstotliwoœci 16MHz. Generator RC jest
 * niestabilny, dlatego w pierwszej kolejnoœci nale¿y spróbowaæ uruchomiæ procesor z zegara bazowanego
 * na kwarcu.
 * W przypadku p³ytki Nucleo do MCU doprowadzony jest sygna³ zegarowy z ST-LINK'a, dlatego HSE jest
 * w trybie "bypass", normalnie musi byæ w trybie "w³¹czony".
 * Je¿eli zamontowany jest inny kwarc lub doprowadzony jest inny zegar, parametry funkcji RCC_PLLConfig()
 * musz¹ ulec zmianie.
 * Je¿eli procesor nie jest w stanie przejœæ na pracê z pêtli PLL, wtedy kod utyka w martwej pêtli.
 * Próba podjêcia pracy wprost na HSI nie ma wiêkszego sensu, gdy¿ to mo¿e oznaczaæ problem sprzêtowy
 * ju¿ na starcie procesora.
 */
void clocks_init(void) {
	RCC_DeInit();
	FLASH_PrefetchBufferCmd(ENABLE);
	FLASH_SetLatency(FLASH_Latency_3);
	RCC_HSEConfig(RCC_HSE_Bypass); //NucleoF4
	if(RCC_WaitForHSEStartUp() == SUCCESS) {
		/* 8MHz HSE, typowo stosowany kwarc */
		RCC_PLLConfig(RCC_PLLSource_HSE, 8, 336, 4, 7);
	} else {
		/* 16MHz HSI */
		RCC_HSEConfig(RCC_HSE_OFF);
		RCC_PLLConfig(RCC_PLLSource_HSI, 16, 336, 4, 7);
	}
	RCC_PLLCmd(ENABLE);
	while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
	RCC_HCLKConfig(RCC_SYSCLK_Div1);
	RCC_PCLK1Config(RCC_HCLK_Div2);
	RCC_PCLK2Config(RCC_HCLK_Div1);
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
	while (RCC_GetSYSCLKSource() != 0x08);

}

void interrupts_init(void) {
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = RCC_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void gpio_init(void) {
	GPIO_InitTypeDef GPIO_InitDef;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	GPIO_InitDef.GPIO_Pin = LED_PIN;
	GPIO_InitDef.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitDef.GPIO_OType = GPIO_OType_PP;
	GPIO_InitDef.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitDef.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(LED_PORT, &GPIO_InitDef);

}

/*
 * Przerwanie NMI jest generowanie m.in. gdy zegar ulegnie awarii. Próbujemy przywróciæ HSE do dzia³ania,
 * je¿eli to nie poskutkuje, mo¿emy prze³¹czyæ siê na HSI.
 * Je¿eli nie uda siê przywróciæ zegara, kod utyka w pêtli. Nie ma sensu próbowaæ z niej wychodziæ, bo
 * oznacza to awariê sprzêtow¹.
 *
 * TODO: Przerwanie mo¿e zwracaæ licznik/status awarii, mo¿e byæ to przydatna informacja dla dalszych decyzji,
 * czy np zg³osiæ b³¹d u¿ytkownikowi, czy kontynuuowaæ pracê.
 */
void NMI_Handler(void)
{
	if (RCC_GetITStatus(RCC_IT_CSS) == SET) {
		RCC_HSEConfig(RCC_HSE_ON);
		if (RCC_WaitForHSEStartUp() == SUCCESS) {
			RCC_PLLConfig(RCC_PLLSource_HSE, 8, 336, 4, 7);
			RCC_PLLCmd(ENABLE);
			while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
			RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
			while (RCC_GetSYSCLKSource() != 0x08);
		} else {
			RCC_HSEConfig(RCC_HSE_OFF);
			RCC_PLLConfig(RCC_PLLSource_HSI, 16, 336, 4, 7);
			RCC_PLLCmd(ENABLE);
			while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
			RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
			while (RCC_GetSYSCLKSource() != 0x08);
		}
		RCC_ClearITPendingBit(RCC_IT_CSS);
	}
}
