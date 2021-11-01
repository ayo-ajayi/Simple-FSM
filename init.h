#include "C:\Keil\TExaSware\tm4c123gh6pm.h"
#include <stdint.h>
#include <TM4C123.h>

void PLL_Init(void);
void PortF_Init(void);
void PortA_Init(void);
void SysTick_Init(void);
void SysTick_Wait(uint32_t delay);
void SysTick_Wait10ms(uint32_t delay);
