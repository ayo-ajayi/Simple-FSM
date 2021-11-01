#include "init.h"

struct State{
	uint8_t out;
	uint32_t wait;
	uint8_t next[2]; 
};
typedef struct State SType;

#define Even 0
#define Odd 1

SType FSM[2] = {
	{0, 100, {Even, Odd}},
	{1, 100, {Odd, Even}}
};

uint8_t cState; 

int main(){
	
	uint8_t input;

	PLL_Init();
	SysTick_Init();
	PortF_Init();
	PortA_Init();

	cState = Even;

	while(1){
	GPIOF->DATA = FSM[cState].out<<2;
	GPIOA->DATA = FSM[!cState].out<<2;
	SysTick_Wait10ms(FSM[cState].wait);
	input = !(GPIOF->DATA & 0x10);
	cState = FSM[cState].next[input];
	}
}




