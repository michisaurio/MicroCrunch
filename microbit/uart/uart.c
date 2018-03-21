#include "uart.h"
#include "gpio.h"

void uart_init(){
  GPIO->DIRSET = (1<<24); //Pin 24 to output
  GPIO->DIRCLR = (1<<25); //Pin 25 to input

  UART->PSELTXD = 24;//TXD at pin 24
  UART->PSELRXD = 25;//RXD at pin 25
  UART->PSELCTS = 0xFFFFFFFF; //CTS disabled
  UART->PSELRTS = 0xFFFFFFFF; //RTS disabled

  UART->BAUDRATE = 0x00275000;
  UART->ENABLE  = 4;  // enable <-> = 4, because of reasons...
  UART->STARTRX = 1;  // Start UART receiver

}

void uart_send(char letter){
  UART->STARTTX = 1;
  UART->TXDRDY = 0;
  UART->TXD = letter;
  while(!(UART->TXDRDY)){
  }
  UART->STOPTX = 1;
}

char uart_read(){
  if (UART->RXDRDY) {
          UART->STARTRX = 1;
          char letter = UART->RXD;
          UART->STOPRX = 1;
          return letter;
      } else {
          return '\0';
  }
}
