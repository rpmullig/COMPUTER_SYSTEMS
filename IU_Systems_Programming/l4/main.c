/**********************************************************
* main.c
*
*  The main file for the led and button ussage on the board
*
*   Author: Robert Mulligan
*   Date Created: 2/5/2016
*   Last Modified by: Robert Mulligan
*   Date Last Modified: 2/8/2016
*   Purpose: Lighting LEDs and using the button
*/

#include <stm32f30x.h>  // Pull in include files for F30x standard drivers 
#include <f3d_led.h>     // Pull in include file for the local drivers
#include <f3d_user_btn.h>

// Simple looping delay function
void delay(void) {
  int i = 2000000;
  while (i-- > 0) {
    asm("nop"); /* This stops it optimising code out */
  }
}

int main(void) {

  //create button instance
  f3d_user_btn_init();
  f3d_led_init();

  // turn all led's off
  f3d_led_all_off();

  //incrementor
  int x = 0; 

  //a while loop
  while(1){

    // runs through the loop but stops if the button is hit
    if(user_btn_read() & x < 9 ) {   f3d_led_all_off();  f3d_led_on(x-1);}
    else {
      // adds a delay and then head to next button
      delay();
      delay();
      f3d_led_on(x);
      f3d_led_off(x-1);
      x++;
    }
    // if the incrementor reaches the end restart it again after delay
    if(x==9) {   
      f3d_led_all_on(); 
      delay();
      delay();
      delay();
      delay();
      x = 0;
      f3d_led_all_off();
    }
  }


  /*
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE); // port E 0
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE); // port A 0 

  
  GPIO_InitTypeDef GPIO_InitStructure;
  
  //initialize the led buton
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOE, &GPIO_InitStructure);


  //initialize the user button
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  
  while (1) { 
    if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)){
      GPIOE->BSRR = GPIO_Pin_9;
    }else {GPIOE->BRR = GPIO_Pin_9;}
  }
  */
  
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
/* Infinite loop */
/* Use GDB to find out why we're here */
  while (1);
}
#endif

/* main.c ends here */
