/**********************************************************
* f3d_uart.c
*
* The UART initialization and functions for I/O
*
* Author: Robert Mulligan
* Date Created: 2/11/2016
* Last Modified by: Robert Mulligan
* Date Last Modified: 2/17/2016
* Assignment: 
* Part of: lab5 lab6
*/


/************************** 
 *f3d_uart.c 
 *contains the initialization basic i/o functions for UART
****************************/ 

/* Code: */

#include <stm32f30x.h>
#include <f3d_uart.h>
//the initialization function to call
void f3d_uart_init(void) {

  //make the constructor for GPIO and the clock   
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);

  //initialize the designated port C pin 4 for the TX   
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOC,&GPIO_InitStructure);

  //initialize the designated port C pin 5 for the Rx
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOC,&GPIO_InitStructure);

  //Altnerate Function Configuration
  GPIO_PinAFConfig(GPIOC,4,GPIO_AF_7);
  GPIO_PinAFConfig(GPIOC,5,GPIO_AF_7);

  //
  //UART1 Module Configuration
  // -initialize the clock and constructor
  USART_InitTypeDef USART_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);


  // UART1 configuration by setting parameters
  USART_StructInit(&USART_InitStructure);
  USART_InitStructure.USART_BaudRate = 9600;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(USART1 ,&USART_InitStructure);
  USART_Cmd(USART1 , ENABLE);


}
//sends a character
int putchar(int c) {

  //routine to put char on the transmitter
  while (USART_GetFlagStatus(USART1,USART_FLAG_TXE) == (uint16_t)RESET);
  USART_SendData(USART1, c);

  return 0; 

} 
//gets a character
int getchar(void) {

  //reads the characters from UART
  while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == (uint16_t)RESET);
  int c = USART_ReceiveData(USART1);

  return c; 

}
//sends a string
void putstring(char *s) {
	while (*s) {
		putchar(*s);
		s++;
	}
}



/* f3d_uart.c ends here */
