/************************
 *f3d_led.c - contains intializations/functions for the leds
 ************************/

/**********************************************************
* F3d_led.c
*
* These definitions set up the I/O interface led
*
*   Author: Robert Mulligan
*   Date Created: 2/5/2016
*   Last Modified by: Robert Mulligan
*   Date Last Modified: 2/8/2016
*   Assignment: Lighting LEDs
*   Part of: Lab4
*/






#include <stm32f30x.h>
#include <stm32f30x_gpio.h>
#include <stm32f30x_rcc.h>
#include <f3d_led.h>


//intializes the port and pins for the leds on the board
void f3d_led_init(void) {
  /*
   --ClockWise--
    PE9  - red
    PE8  - blue
    PE15 - green
    PE14 - orange
    PE13 - red
    PE12 - blue
    PE11 - green
    PE10 - orange
   */
 
  // Initiialize struct and port E clock
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_StructInit(&GPIO_InitStructure);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);

 // param settings for light 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;


  //set the port # macros and make sure they're off
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
  GPIOE->BRR = GPIO_Pin_9;  

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
  GPIOE->BRR = GPIO_Pin_8;  

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
  GPIOE->BRR = GPIO_Pin_15;  

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
  GPIOE->BRR = GPIO_Pin_14;  

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
  GPIOE->BRR = GPIO_Pin_13;  

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
  GPIOE->BRR = GPIO_Pin_12;  

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
  GPIOE->BRR = GPIO_Pin_11;  

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
  GPIOE->BRR = GPIO_Pin_10;  


}
/*Turns on the appropriate led as specified by the parameter.*/
void f3d_led_on(int led) {


  /*YOUR CODE HERE*/

  // a switch case that picks which led chosen to light up
  switch(led){
  case 0:
    GPIOE->BSRR = GPIO_Pin_9;
    break;

  case 1:
    GPIOE->BSRR = GPIO_Pin_8;
    break;


  case 2:
    GPIOE->BSRR = GPIO_Pin_15;
    break;


  case 3:
    GPIOE->BSRR = GPIO_Pin_14;
    break;


  case 4:
    GPIOE->BSRR = GPIO_Pin_13;
    break;

  case 5:
    GPIOE->BSRR = GPIO_Pin_12;
    break;

  case 6:
    GPIOE->BSRR = GPIO_Pin_11;
    break;

  case 7:
    GPIOE->BSRR = GPIO_Pin_10;
    break;

  default:
    break;

  }

}

/*Turns off the approiate led as specified by the parameter*/ 
void f3d_led_off(int led) {
  /*YOUR CODE HERE*/
  // a swtich led to turn off
  switch(led){
  case 0:
    GPIOE->BRR = GPIO_Pin_9;
    break;

  case 1:
    GPIOE->BRR = GPIO_Pin_8;
    break;


  case 2:
    GPIOE->BRR = GPIO_Pin_15;
    break;


  case 3:
    GPIOE->BRR = GPIO_Pin_14;
    break;


  case 4:
    GPIOE->BRR = GPIO_Pin_13;
    break;

  case 5:
    GPIOE->BRR = GPIO_Pin_12;
    break;

  case 6:
    GPIOE->BRR = GPIO_Pin_11;
    break;

  case 7:
    GPIOE->BRR = GPIO_Pin_10;
    break;

  default:
    break;

  }


} 

/*Turns on all LEDs*/
void f3d_led_all_on(void) {
  /*YOUR CODE HERE*/
  // turns them all off, going through each pin
 GPIOE->BSRR = GPIO_Pin_9;
 GPIOE->BSRR = GPIO_Pin_8;
 GPIOE->BSRR = GPIO_Pin_15;  
 GPIOE->BSRR = GPIO_Pin_14;
 GPIOE->BSRR = GPIO_Pin_13;
 GPIOE->BSRR = GPIO_Pin_12;
 GPIOE->BSRR = GPIO_Pin_11;
 GPIOE->BSRR = GPIO_Pin_10;

} 

/*Turns off all LEDs*/
void f3d_led_all_off(void) {
  /*YOUR CODE HERE*/

  // turns all off individually
 GPIOE->BRR = GPIO_Pin_9;
 GPIOE->BRR = GPIO_Pin_8;
 GPIOE->BRR = GPIO_Pin_15;  
 GPIOE->BRR = GPIO_Pin_14;
 GPIOE->BRR = GPIO_Pin_13;
 GPIOE->BRR = GPIO_Pin_12;
 GPIOE->BRR = GPIO_Pin_11;
 GPIOE->BRR = GPIO_Pin_10;


} 

/* led.c ends here */

