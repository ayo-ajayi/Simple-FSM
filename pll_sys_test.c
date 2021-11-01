#include "init.h"

int main(){
	PLL_Init();
	SysTick_Init();
	PortF_Init();
	
	while(1){
		if(!(GPIOF->DATA & 0x10)){
		GPIOF->DATA |= 0x02;
		SysTick_Wait10ms(100);
		GPIOF->DATA &= ~0x02;
		SysTick_Wait10ms(100);
		GPIOF->DATA |= 0x04;
		SysTick_Wait10ms(100);
		GPIOF->DATA &= ~0x04;
		SysTick_Wait10ms(100);
		}	
	}
}
