/* main.c --- 
 * 
 * Filename: main.c
 * Description: main program 
 * Author: Robert Mulligan
 * Maintainer: Robert Mulligan
 * Created: Thu Feb 11:23:43 2016
 * Last-Updated: 
 *           By: 
 *     Update #: 0
 * Keywords: 
 * Compatibility: 
 * 
 */

/* Commentary: 
 * 
 * 
 * 
 */

/* Change log:
 * 
 * 
 */
/* Code: */

#include <f3d_uart.h>
#include <stdio.h>
#include <stm32f30x.h>  // Pull in include files for F30x standard drivers 
#include <f3d_led.h>     // Pull in include file for the local drivers

// Simple looping delay function
void delay(void) {
  int i = 2000000;
  while (i-- > 0) {
    asm("nop"); /* This stops it optimising code out */
  }
}

int main(void) {
  f3d_uart_init();

  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);


  /* 
  while(1) {
    putchar('a');
    }*/
  

  /*
putchar(getchar());
  
  while (1){
    putstring("hello"); 
    }*/


 
 while(1) {
int lines = 0;
	int words = 0;
	int characters = 0; 
	int c;	//initializing origin counters
	while ((c = getchar()) != 0x1b) {
	characters++;
	if (c == '\n') {
	lines++;
	words++;
	}
	if (c == ' ' || c == '\t' || c ==  '\r' || c =='\f' || c=='\v') {
	words++;
		}
	}

  printf("%d,  ",lines);
  printf("%d,  ",words);
  printf("%d\n",characters);

	}
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
/* Infinite loop */
/* Use GDB to find out why we're here */
  while (1);
}
#endif

/* main.c ends here */
