#include <stdint.h>
#include "../uart/uart.h"
#include <stdio.h>

#define GPIO ((NRF_GPIO_REGS*)0x50000000)

typedef struct {
	volatile uint32_t RESERVED0[321];
	volatile uint32_t OUT;
	volatile uint32_t OUTSET;
	volatile uint32_t OUTCLR;
	volatile uint32_t IN;
	volatile uint32_t DIR;
	volatile uint32_t DIRSET;
	volatile uint32_t DIRCLR;
	volatile uint32_t RESERVED1[120];
	volatile uint32_t PIN_CNF[32];
} NRF_GPIO_REGS;

ssize_t _write(int fd, const void *buf, size_t count){
	char * letter = (char *)(buf);
	for(int i = 0; i < count; i++){
		uart_send(*letter);
		letter++;
	}
	return count;
}

static int lights_on = 0;
int button_A_pressed();
int button_B_pressed();
void turn_on_lights();
void turn_off_lights();

int main(){
	// Configure LED Matrix
	for(int i = 4; i <= 15; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}
	// Configure buttons
	GPIO->PIN_CNF[17] = 0;
	GPIO->PIN_CNF[26] = 0;
	int sleep = 0;
	// Init UART
	uart_init();
	while(1){
			if(button_B_pressed()){
			turn_on_lights();
			//uart_send('B');
			iprintf("Norway has %d counties.\n\r", 18);
		}else if(button_A_pressed()){
			turn_off_lights();
			//uart_send('A');
			iprintf("Peru has %d counties.\n\r", 24);
		}
		if(uart_read()!='\0'){
			if(lights_on)
				turn_off_lights();
			else
				turn_on_lights();
		}
		sleep = 10000;
		while(--sleep);
	}
	return 0;
}

// utilities
int button_A_pressed(){
	return !(GPIO->IN & (1<<17));
}
int button_B_pressed(){
	return !(GPIO->IN & (1<<26));
}
void turn_on_lights(){
	for(int i=13;i<16;i++){
		GPIO->OUTSET=(1<<i);
	}
	lights_on=1;
}
void turn_off_lights(){
	for(int i=13;i<16;i++){
		GPIO->OUTCLR=(1<<i);
	}
	lights_on = 0;
}
