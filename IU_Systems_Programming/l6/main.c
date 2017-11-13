/**********************************************************
* main.c
*
* The main function for lab6
*
* Author: Robert Mulligan
* Date Created: 2/17/2016
* Last Modified by: Robert Mulligan
* Date Last Modified: 2/24/2016
* Purpose: main
*/


//main.c for lab6
#include <f3d_uart.h>
#include <stdio.h>
#include <f3d_gyro.h>
#include <f3d_led.h>
#include <f3d_user_btn.h>

void delay(void) {
  int i = 2000000;
  while (i-- > 0) {
    asm("nop"); /* This stops it optimising code out */
  }
}

void bar_lights(float val) {
  int east[4] = {0,1,2,3};
  int west[4] = {7,6,4,3};
  if(val > 0) {
    if(val > 5) {
      f3d_led_on(0);
    }
    if(val > 10) {
      f3d_led_on(1);
    }
    if(val > 35) {
      f3d_led_on(2);
    }
    if(val > 85) {
      f3d_led_on(3);
    }
    if(val > 160) {
      f3d_led_on(4);
    }
  }
  if(val <= 0){
    if(val < -5) {
      f3d_led_on(0);
    }
    if(val < -10) {
      f3d_led_on(7);
    }
    if(val < -35) {
      f3d_led_on(6);
    }
    if(val < -85) {
      f3d_led_on(5);
    }
    if(val < -160) {
      f3d_led_on(4);
    }
  }
  delay();
  f3d_led_all_off();

}

int main(void){
  f3d_uart_init();
  f3d_gyro_init();
  f3d_user_btn_init();
  f3d_led_init();
 
  delay();
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);
  int pressed = 0;
  int axis = 0;
  float xval;
  float yval;
  float zval;
  char keypress;
  while(1) {
    delay();
    while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) != (uint16_t)RESET){
      keypress = getchar();
      pressed = 1;
      }
    if(pressed) {
      if(keypress == 'x'){
	axis = 0;
      }
      if(keypress == 'y'){
	axis = 1;
      }
      if(keypress == 'z'){
	axis = 2;
      }
      pressed = 0;
    }
    if(user_btn_read()){
      axis++;
    }
    float test[3];
    f3d_gyro_getdata(test);
    xval = test[0];
    yval = test[1];
    zval = test[2];
    if (axis % 3 == 0) {
        printf("x = %f \n", test[0]);
	bar_lights(test[0]);
    }
    else if (axis % 3 == 1) {
        printf("y = %f \n", test[1]);
	bar_lights(test[1]);
    }
    else if (axis % 3 == 2) {
        printf("z = %f \n", test[2]);
	bar_lights(test[2]);
    }
    delay();

    
  }
}

void assert_failed(uint8_t* file, uint32_t line) {
/* Infinite loop */
/* Use GDB to find out why we're here */
  while (1);
}
