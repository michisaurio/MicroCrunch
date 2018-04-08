// Oppgave 3: GPIOTE
#include <stdint.h>
#include "gpiote.h"
#include "ppi.h"
#include "../gpio/gpio.h"

int main(){
  // Configure LED Matrix
	for(int i = 4; i <= 15; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}
  // Configure voltage supplies. Tasks
  GPIOTE->CONFIG[0] = 0x00030D03;
  GPIOTE->CONFIG[1] = 0x00030E03;
  GPIOTE->CONFIG[2] = 0x00030F03;
  // Configure A buttons. Event
  GPIOTE->CONFIG[3] = 0x00021101;

  PPI->CHENSET = 0x00000007;
  PPI->PPI_CH[0].EEP = (uint32_t)&(GPIOTE->IN[3]);
  PPI->PPI_CH[0].TEP = (uint32_t)&(GPIOTE->OUT[0]);
  PPI->PPI_CH[1].EEP = (uint32_t)&(GPIOTE->IN[3]);
  PPI->PPI_CH[1].TEP = (uint32_t)&(GPIOTE->OUT[1]);
  PPI->PPI_CH[2].EEP = (uint32_t)&(GPIOTE->IN[3]);
  PPI->PPI_CH[2].TEP = (uint32_t)&(GPIOTE->OUT[2]);

	int sleep = 0;
  while(1){
		sleep = 10000;
		while(--sleep);
	}
	return 0;
}
