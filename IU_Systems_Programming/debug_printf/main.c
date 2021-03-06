/**********************************************************
* main.c
*
* debugging lab7 main file
*
* Author: Robert Mulligan
* Date Created: 2/17/2016
* Last Modified by: Robert Mulligan
* Date Last Modified: 2/24/2016
* Assignment: main
* Part of: lab7
*/


//main.c for lab6
#include <f3d_uart.h>
#include <stdio.h>
#include <f3d_gyro.h>
#include <f3d_led.h>
#include <f3d_user_btn.h>

void delay(void) {
  int i = 7000000;
  while (i-- > 0) {
    asm("nop"); /* This stops it optimising code out */
  }
}

int main(void){
  f3d_uart_init();
  f3d_gyro_init();
  f3d_user_btn_init();
  f3d_led_init();
 
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);


  while(1) {
    
    f3d_led_all_on();
    delay();
    
    //this takes quite some time :/ 
    int i; 
    for(i = 0; i < 100; i++){ 
      printf("call_%d\n", i);
    }


    f3d_led_all_off();
    delay();
  }
}
void assert_failed(uint8_t* file, uint32_t line) {
/* Infinite loop */
/* Use GDB to find out why we're here */
  while (1);
}
