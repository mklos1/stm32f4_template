#include "stm32f4xx.h"

extern unsigned int _estack;
extern int main(void);

extern unsigned long _flash_data_start;
extern unsigned long _data_start;
extern unsigned long _data_end;
extern unsigned long _bss_start;
extern unsigned long _bss_end;



#define RAMFUNC __attribute__ ((long_call, section (".ramsection")))

void Reset_Handler (void);
void NMI_Handler (void);
void HardFault_Handler (void);
void MPU_Handler (void);
void BusFault_Handler (void);
void UsageFault_Handler (void);
void SVCall_Handler (void);
void DebugMonitor_Handler (void);
void PendSV_Handler (void);
void SysTick_Handler (void);
void WindowWatchDog_Handler (void);
void PVD_Handler (void);
void Tamper_Handler (void);
void RTC_Handler (void);
void Flash_Handler (void);
void RCC_Handler (void);
void EXTILine0_Handler (void);
void EXTILine1_Handler (void);
void EXTILine2_Handler (void);
void EXTILine3_Handler (void);
void EXTILine4_Handler (void);
void DMAStream0_Handler (void);
void DMAStream1_Handler (void);
void DMAStream2_Handler (void);
void DMAStream3_Handler (void);
void DMAStream4_Handler (void);
void DMAStream5_Handler (void);
void DMAStream6_Handler (void);
void ADC_Handler (void);
void EXTLine95_Handler (void);
void TIM1Break_Handler (void);
void TIM1Update_Handler (void);
void TIM1Trigger_Handler (void);
void TIM1Capture_Handler (void);
void TIM2_Handler (void);
void TIM3_Handler (void);
void TIM4_Handler (void);
void I2C1Event_Handler (void);
void I2C1Error_Handler (void);
void I2C2Event_Handler (void);
void I2C2Error_Handler (void);
void SPI1_Handler (void);
void SPI2_Handler (void);
void USART1_Handler (void);
void USART2_Handler (void);
void EXTLine1510_Handler (void);
void RTCAlarm_Handler (void);
void OTGWakeup_Handler (void);
void DMA1Stream7_Handler (void);
void SDIO_Handler (void);
void TIM5_Handler (void);
void DMA2Stream0_Handler (void);
void DMA2Stream1_Handler (void);
void DMA2Stream2_Handler (void);
void DMA2Stream3_Handler (void);
void DMA2Stream4_Handler (void);
void OTGFS_Handler (void);
void DMA2Stream5_Handler (void);
void DMA2Stream6_Handler (void);
void DMA2Stream7_Handler (void);
void USART6_Handler (void);
void I2C3Event_Handler (void);
void I2C3Error_Handler (void);
void FPU_Handler (void);
void SPI4_Handler (void);

__attribute__ ((section(".isr_vectors"),used))
void (*isr_vectors[]) (void) =
  {
   // Cortex-M Core Handlers
   (void*)&_estack,               // The initial stack pointer
   Reset_Handler,                     // The reset handler
   NMI_Handler,                       // The NMI handler
   HardFault_Handler,                 // The hard fault handler
   MPU_Handler,                 // The MPU fault handler
   BusFault_Handler,                  // The bus fault handler
   UsageFault_Handler,                // The usage fault handler
   0,                                 // Reserved
   0,                                 // Reserved
   0,                                 // Reserved
   0,                                 // Reserved
   SVCall_Handler,                       // SVCall handler
   DebugMonitor_Handler,                  // Debug monitor handler
   0,                                 // Reserved
   PendSV_Handler,                    // The PendSV handler
   SysTick_Handler,                   // The SysTick handler
   WindowWatchDog_Handler,                   // Window WatchDog
   PVD_Handler,                    // PVD through EXTI Line detection
   Tamper_Handler,             // Tamper and TimeStamps through the EXTI line
   RTC_Handler,               // RTC Wakeup through the EXTI line
   Flash_Handler,                  // FLASH
   RCC_Handler,                    // RCC
   EXTILine0_Handler,                  // EXTI Line0
   EXTILine1_Handler,                  // EXTI Line1
   EXTILine2_Handler,                  // EXTI Line2
   EXTILine3_Handler,                  // EXTI Line3
   EXTILine4_Handler,                  // EXTI Line4
   DMAStream0_Handler,           // DMA1 Stream 0
   DMAStream1_Handler,           // DMA1 Stream 1
   DMAStream2_Handler,           // DMA1 Stream 2
   DMAStream3_Handler,           // DMA1 Stream 3
   DMAStream4_Handler,           // DMA1 Stream 4
   DMAStream5_Handler,           // DMA1 Stream 5
   DMAStream6_Handler,           // DMA1 Stream 6
   ADC_Handler,                    // ADC1, ADC2 and ADC3s
   0,                                 // Reserved
   0,                                 // Reserved
   0,                                 // Reserved
   0,                                 // Reserved
   EXTLine95_Handler,                // External Line[9:5]s
   TIM1Break_Handler,          // TIM1 Break and TIM9
   TIM1Update_Handler,          // TIM1 Update and TIM10
   TIM1Trigger_Handler,     // TIM1 Trigger and Commutation and TIM11
   TIM1Capture_Handler,                // TIM1 Capture Compare
   TIM2_Handler,                   // TIM2
   TIM3_Handler,                   // TIM3
   TIM4_Handler,                   // TIM4
   I2C1Event_Handler,                // I2C1 Event
   I2C1Error_Handler,                // I2C1 Error
   I2C2Event_Handler,                // I2C2 Event
   I2C2Error_Handler,                // I2C2 Error
   SPI1_Handler,                   // SPI1
   SPI2_Handler,                   // SPI2
   USART1_Handler,                 // USART1
   USART2_Handler,                 // USART2
   0,                                 // Reserved
   EXTLine1510_Handler,              // External Line[15:10]s
   RTCAlarm_Handler,              // RTC Alarm (A and B) through EXTI Line
   OTGWakeup_Handler,            // USB OTG FS Wakeup through EXTI line
   0,                                 // Reserved
   0,                                 // Reserved
   0,                                 // Reserved
   0,                                 // Reserved
   DMA1Stream7_Handler,           // DMA1 Stream7
   0,                                 // Reserved
   SDIO_Handler,                   // SDIO
   TIM5_Handler,                   // TIM5
   0,                   // SPI3
   0,                                 // Reserved
   0,                                 // Reserved
   0,                                 // Reserved
   0,                                 // Reserved
   DMA2Stream0_Handler,           // DMA2 Stream 0
   DMA2Stream1_Handler,           // DMA2 Stream 1
   DMA2Stream2_Handler,           // DMA2 Stream 2
   DMA2Stream3_Handler,           // DMA2 Stream 3
   DMA2Stream4_Handler,           // DMA2 Stream 4
   0,                                 // Reserved
   0,                                 // Reserved
   0,                                 // Reserved
   0,                                 // Reserved
   0,                                 // Reserved
   0,                                 // Reserved
   OTGFS_Handler,                 // USB OTG FS
   DMA2Stream5_Handler,           // DMA2 Stream 5
   DMA2Stream6_Handler,           // DMA2 Stream 6
   DMA2Stream7_Handler,           // DMA2 Stream 7
   USART6_Handler,                 // USART6
   I2C3Event_Handler,                // I2C3 event
   I2C3Error_Handler,                // I2C3 error
   0,                                 // Reserved
   0,                                 // Reserved
   0,                                 // Reserved
   0,                                 // Reserved
   0,                                 // Reserved
   0,                                 // Reserved
   0,                                 // Reserved
   FPU_Handler,                    // FPU
   0,                                 // Reserved
   0,                                 // Reserved
   SPI4_Handler,                   // SPI4
};

void Reset_Handler (void) {

	unsigned long* ram_ptr;
	unsigned long* flash_ptr;

	ram_ptr = &_data_start;
	flash_ptr = &_flash_data_start;
	while (ram_ptr < &_data_end) {
		*(ram_ptr++) = *(flash_ptr++);
	}

	ram_ptr = &_bss_start;
	while (ram_ptr < &_bss_end) {
		*(ram_ptr++) = 0;
	}

    main();
    NVIC_SystemReset();
}

void __attribute__((weak)) NMI_Handler (void)
{
   while (1);
}

void __attribute__((weak)) HardFault_Handler (void)
{
   while (1);
}

void __attribute__((weak)) MPU_Handler (void)
{
   while (1);
}

void __attribute__((weak)) BusFault_Handler (void)
{
   while (1);
}

void __attribute__((weak)) UsageFault_Handler (void)
{
   while (1);
}

void __attribute__((weak)) SVCall_Handler (void)
{
   while (1);
}

void __attribute__((weak)) DebugMonitor_Handler (void)
{
   while (1);
}

void __attribute__((weak)) PendSV_Handler (void)
{
   while (1);
}

void __attribute__((weak)) SysTick_Handler (void)
{
   while (1);
}

void __attribute__((weak)) WindowWatchDog_Handler (void)
{
   while (1);
}

void __attribute__((weak)) PVD_Handler (void)
{
   while (1);
}

void __attribute__((weak)) Tamper_Handler (void)
{
   while (1);
}

void __attribute__((weak)) RTC_Handler (void)
{
   while (1);
}

void __attribute__((weak)) Flash_Handler (void)
{
   while (1);
}

void __attribute__((weak)) RCC_Handler (void)
{
   while (1);
}

void __attribute__((weak)) EXTILine0_Handler (void)
{
   while (1);
}

void __attribute__((weak)) EXTILine1_Handler (void)
{
   while (1);
}

void __attribute__((weak)) EXTILine2_Handler (void)
{
   while (1);
}

void __attribute__((weak)) EXTILine3_Handler (void)
{
   while (1);
}

void __attribute__((weak)) EXTILine4_Handler (void)
{
   while (1);
}

void __attribute__((weak)) DMAStream0_Handler (void)
{
   while (1);
}

void __attribute__((weak)) DMAStream1_Handler (void)
{
   while (1);
}

void __attribute__((weak)) DMAStream2_Handler (void)
{
   while (1);
}

void __attribute__((weak)) DMAStream3_Handler (void)
{
   while (1);
}

void __attribute__((weak)) DMAStream4_Handler (void)
{
   while (1);
}

void __attribute__((weak)) DMAStream5_Handler (void)
{
   while (1);
}

void __attribute__((weak)) DMAStream6_Handler (void)
{
   while (1);
}

void __attribute__((weak)) ADC_Handler (void)
{
   while (1);
}

void __attribute__((weak)) EXTLine95_Handler (void)
{
   while (1);
}

void __attribute__((weak)) TIM1Break_Handler (void)
{
   while (1);
}

void __attribute__((weak)) TIM1Update_Handler (void)
{
   while (1);
}

void __attribute__((weak)) TIM1Trigger_Handler (void)
{
   while (1);
}

void __attribute__((weak)) TIM1Capture_Handler (void)
{
   while (1);
}

void __attribute__((weak)) TIM2_Handler (void)
{
   while (1);
}

void __attribute__((weak)) TIM3_Handler (void)
{
   while (1);
}

void __attribute__((weak)) TIM4_Handler (void)
{
   while (1);
}

void __attribute__((weak)) I2C1Event_Handler (void)
{
   while (1);
}

void __attribute__((weak)) I2C1Error_Handler (void)
{
   while (1);
}

void __attribute__((weak)) I2C2Event_Handler (void)
{
   while (1);
}

void __attribute__((weak)) I2C2Error_Handler (void)
{
   while (1);
}

void __attribute__((weak)) SPI1_Handler (void)
{
   while (1);
}

void __attribute__((weak)) SPI2_Handler (void)
{
   while (1);
}

void __attribute__((weak)) USART1_Handler (void)
{
   while (1);
}

void __attribute__((weak)) USART2_Handler (void)
{
   while (1);
}

void __attribute__((weak)) EXTLine1510_Handler (void)
{
   while (1);
}

void __attribute__((weak)) RTCAlarm_Handler (void)
{
   while (1);
}

void __attribute__((weak)) OTGWakeup_Handler (void)
{
   while (1);
}

void __attribute__((weak)) DMA1Stream7_Handler (void)
{
   while (1);
}

void __attribute__((weak)) SDIO_Handler (void)
{
   while (1);
}

void __attribute__((weak)) TIM5_Handler (void)
{
   while (1);
}

void __attribute__((weak)) DMA2Stream0_Handler (void)
{
   while (1);
}

void __attribute__((weak)) DMA2Stream1_Handler (void)
{
   while (1);
}

void __attribute__((weak)) DMA2Stream2_Handler (void)
{
   while (1);
}

void __attribute__((weak)) DMA2Stream3_Handler (void)
{
   while (1);
}

void __attribute__((weak)) DMA2Stream4_Handler (void)
{
   while (1);
}

void __attribute__((weak)) OTGFS_Handler (void)
{
   while (1);
}

void __attribute__((weak)) DMA2Stream5_Handler (void)
{
   while (1);
}

void __attribute__((weak)) DMA2Stream6_Handler (void)
{
   while (1);
}

void __attribute__((weak)) DMA2Stream7_Handler (void)
{
   while (1);
}

void __attribute__((weak)) USART6_Handler (void)
{
   while (1);
}

void __attribute__((weak)) I2C3Event_Handler (void)
{
   while (1);
}

void __attribute__((weak)) I2C3Error_Handler (void)
{
   while (1);
}

void __attribute__((weak)) FPU_Handler (void)
{
   while (1);
}

void __attribute__((weak)) SPI4_Handler (void)
{
   while (1);
}
