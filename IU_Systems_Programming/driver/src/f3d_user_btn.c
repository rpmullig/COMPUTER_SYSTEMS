/**********************************
 *f3d_user_btn.c 
 *contains the init and read functions for the User Button
 *********************************/

/**********************************************************
* F3d_user_btn.c
*
* These definitions set up the I/O interface for the button
*
*   Author: Robert Mulligan
*   Date Created: 2/5/2016
*   Last Modified by: Robert Mulligan
*   Date Last Modified: 2/8/2016
*   Assignment: using the button
*   Part of: Lab4
*/


#include <stm32f30x.h>
#include <stm32f30x_gpio.h>
#include <stm32f30x_rcc.h>


/*Initialization of the UserButton*/
void f3d_user_btn_init(void){

  // initialized
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_StructInit(&GPIO_InitStructure);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

  //sets parameters
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

  //adds the pin_0
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_Init(GPIOA, &GPIO_InitStructure);


}

/*reads the User Button*/
int user_btn_read(void){
  // returns through this function already in the library
  return GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0);
  
}
