// Oppgave 1: GPIO
#include <stdint.h>
#include "gpio.h"

int main(){
	// Configure LED Matrix
	for(int i = 4; i <= 15; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}
	// Configure buttons
	GPIO->PIN_CNF[17] = 0;
	GPIO->PIN_CNF[26] = 0;
  // A pressed: turn off. B pressed: turn on
	int sleep = 0;
	while(1){
    if(!(GPIO->IN & (1<<17))){// A pressed:turn off
      for(int i=13;i<16;i++){
    		GPIO->OUTCLR=(1<<i);
    	}
    }
    if(!(GPIO->IN & (1<<26))){// B pressed: turn on
      for(int i=13;i<16;i++){
    		GPIO->OUTSET=(1<<i);
    	}
    }
    // sleep
		sleep = 10000;
		while(--sleep);
	}
	return 0;
}
