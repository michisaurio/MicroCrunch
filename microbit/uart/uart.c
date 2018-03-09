#include "uart.h"
#include "gpio.h"

void uart_init(){
  GPIO->DIRSET = (1<<24);
  GPIO->DIRCLR = (1<<25);

  UART->PSELTXD &= !(1<<24);
  UART->PSELRXD &= !(1<<25);

  UART->BAUDRATE = 0x00275000;
  UART->ENABLE  = 4;
  UART->STARTRX = 1;


}

void uart_send(char letter){
/*A UART transmission sequence is started by triggering the STARTTX task. Bytes are transmitted by writing to the TXD
register. When a byte has been successfully transmitted the UART will generate a TXDRDY event after which a new
byte can be written to the TXD register. A UART transmission sequence is stopped immediately by triggering the
STOPTX task.
*/
  UART->STARTTX = 1;
  // write to TXD
  while(!(UART->TXDRDY)){

  }

}

char uart_read(){

}
