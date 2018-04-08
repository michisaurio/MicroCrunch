// Oppgave 2: UART
#include <stdint.h>
#include <stdio.h>
#include "uart.h"
#include "../gpio/gpio.h"

ssize_t _write(int fd, const void *buf, size_t count){
	char * letter = (char *)(buf);
	for(int i = 0; i < count; i++){
		uart_send(*letter);
		letter++;
	}
	return count;
}
/*
ssize_t _read(int fd, void *buf, size_t count){
char *str = (char *)(buf);
char letter;
do {
letter = uart_read();
} while(letter == '\0');
*str = letter;
return 1;
}
*/
int main(){
	// Configure LED Matrix
	for(int i = 4; i <= 15; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}
	// Configure buttons
	GPIO->PIN_CNF[17] = 0;
	GPIO->PIN_CNF[26] = 0;
	// Initialize UART_UART
	uart_init();
	// If a button is pressed, write something once.
	// When reading toggle the lights.
	int sleep = 0;
	int lights_on = 0;
	while(1){
		if(!(GPIO->IN & (1<<17))){ // A pressed
			iprintf("Norway has %d counties.\n\r", 18); ////uart_send('A');
			while(!(GPIO->IN & (1<<17)));
		} else if(!(GPIO->IN & (1<<26))){ // B pressed
			iprintf("Norway has %d municipalitites.\n\r", 422); //uart_send('B');
			while(!(GPIO->IN & (1<<26)));
		}
		if(uart_read()!='\0'){// toggle the lights
			if(lights_on){
				for(int i=13;i<16;i++){
					GPIO->OUTCLR=(1<<i);
				}
				lights_on=0;
			} else{
				for(int i=13;i<16;i++){
	    		GPIO->OUTSET=(1<<i);
	    	}
				lights_on=1;
			}
		}
		// sleep
		sleep = 10000;
		while(--sleep);
	}
	return 0;
}
