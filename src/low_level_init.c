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

	// Uruchamiamy nadz�r nad poprawno�ci� dzia�ania zegara
	RCC_ClockSecuritySystemCmd(ENABLE);

	// Zapalamy diod�, gdy init sprz�tu si� zako�czy�.
	GPIO_SetBits(LED_PORT, LED_PIN);
}

/*
 * Procesor po resecie dzia�a z wewn�trznego zegara HSI o cz�stotliwo�ci 16MHz. Generator RC jest
 * niestabilny, dlatego w pierwszej kolejno�ci nale�y spr�bowa� uruchomi� procesor z zegara bazowanego
 * na kwarcu.
 * W przypadku p�ytki Nucleo do MCU doprowadzony jest sygna� zegarowy z ST-LINK'a, dlatego HSE jest
 * w trybie "bypass", normalnie musi by� w trybie "w��czony".
 * Je�eli zamontowany jest inny kwarc lub doprowadzony jest inny zegar, parametry funkcji RCC_PLLConfig()
 * musz� ulec zmianie.
 * Je�eli procesor nie jest w stanie przej�� na prac� z p�tli PLL, wtedy kod utyka w martwej p�tli.
 * Pr�ba podj�cia pracy wprost na HSI nie ma wi�kszego sensu, gdy� to mo�e oznacza� problem sprz�towy
 * ju� na starcie procesora.
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
 * Przerwanie NMI jest generowanie m.in. gdy zegar ulegnie awarii. Pr�bujemy przywr�ci� HSE do dzia�ania,
 * je�eli to nie poskutkuje, mo�emy prze��czy� si� na HSI.
 * Je�eli nie uda si� przywr�ci� zegara, kod utyka w p�tli. Nie ma sensu pr�bowa� z niej wychodzi�, bo
 * oznacza to awari� sprz�tow�.
 *
 * TODO: Przerwanie mo�e zwraca� licznik/status awarii, mo�e by� to przydatna informacja dla dalszych decyzji,
 * czy np zg�osi� b��d u�ytkownikowi, czy kontynuuowa� prac�.
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
