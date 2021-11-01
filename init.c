#include "init.h"

void PortF_Init(void){ volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000020;     // 1) activate clock for Port F
  delay = SYSCTL_RCGC2_R;           // allow time for clock to start
  GPIO_PORTF_LOCK_R = 0x4C4F434B;   // 2) unlock GPIO Port F
  GPIO_PORTF_CR_R = 0x1F;           // allow changes to PF4-0
  // only PF0 needs to be unlocked, other bits can't be locked
  GPIO_PORTF_AMSEL_R = 0x00;        // 3) disable analog on PF
  GPIO_PORTF_PCTL_R = 0x00000000;   // 4) PCTL GPIO on PF4-0
  GPIO_PORTF_DIR_R = 0x0E;          // 5) PF4,PF0 in, PF3-1 out
  GPIO_PORTF_AFSEL_R = 0x00;        // 6) disable alt funct on PF7-0
  GPIO_PORTF_PUR_R = 0x11;          // enable pull-up on PF0 and PF4
  GPIO_PORTF_DEN_R = 0x1F;          // 7) enable digital I/O on PF4-0
}

void PortA_Init(void){ volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x01;           // 1) activate clock for Port A
  delay = SYSCTL_RCGC2_R;           // allow time for clock to start
                                    // 2) no need to unlock PA2
  GPIO_PORTA_PCTL_R &= ~0x00000F00; // 3) regular GPIO
  GPIO_PORTA_AMSEL_R &= ~0x04;      // 4) disable analog function on PA2
  GPIO_PORTA_DIR_R |= 0x04;         // 5) set direction to output
  GPIO_PORTA_AFSEL_R &= ~0x04;      // 6) regular port function
  GPIO_PORTA_DEN_R |= 0x04;         // 7) enable digital port
}
void SysTick_Init(void){

  NVIC_ST_CTRL_R = 0;              
  NVIC_ST_CTRL_R = 0x00000005;     
}
// The delay parameter is in units of the 80 MHz core clock. (12.5 ns)
void SysTick_Wait(uint32_t delay){

  NVIC_ST_RELOAD_R = delay-1; 
  NVIC_ST_CURRENT_R = 0;    
  while((NVIC_ST_CTRL_R&0x00010000)==0){}
}
// 800000*12.5ns equals 10ms
void SysTick_Wait10ms(uint32_t delay){

  uint32_t i;
  for(i=0; i<delay; i++){
    SysTick_Wait(800000);  // wait 10ms
  }
}

void PLL_Init(){
	SYSCTL_RCC2_R |= 0x80000000; // Use RCC2
	SYSCTL_RCC2_R |= 0x800; //set BYPASS2 bit
	SYSCTL_RCC_R = (SYSCTL_RCC_R & ~0x07C0) + 0x0540; //specify XTAL freq. using xtal bits
	SYSCTL_RCC2_R &= ~0x70; //OSCSRC bits cleared to select main osc as the clock source
	SYSCTL_RCC2_R &= ~0x2000; // clear PWRDN2 to activate PLL;
	SYSCTL_RCC2_R = (SYSCTL_RCC2_R & ~0x1FC00000) + (4 << 22); //configure the sysdiv2 to set the divisor for the 400MHz
	while( (SYSCTL_RIS_R & 0x40) == 0){} // wait for PLL to stabilize using the raw interrupt status
	SYSCTL_RCC2_R &= ~0x800; // connect the bypass2 bit to connect the PLL
}
