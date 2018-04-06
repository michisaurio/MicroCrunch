#include <stdint.h>
#include <stdlib.h>
#include "twi.h"
#include "utility.h"
#include <stdio.h>
#include "../gpiote/gpio.h"
#include "../uart/uart.h"

int main(){
  // Configure LED Matrix
	for(int i = 4; i <= 15; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}

  uart_init();
  utility_print(&uart_send, "Hei!\n\r");

  //TWI dance
  uint8_t accelerometer_address = 0x1D;
  uint8_t whoiam_register = 0x0D;
  int registers_to_read = 8;
  uint8_t * data_buffer;
  data_buffer = (uint8_t *)malloc(8 * sizeof(uint8_t));

  twi_init();
  twi_multi_read(accelerometer_address,whoiam_register,registers_to_read,data_buffer);

  if(data_buffer[0]==0x5A){
    for(int i=13;i<16;i++){
      GPIO->OUTSET=(1<<i);
    }
  }
  free(data_buffer);

  utility_print(&uart_send, "WhoIAm: %d\n\r",data_buffer[0]);

  while(1);


  return 0;
}


//slave_address =
