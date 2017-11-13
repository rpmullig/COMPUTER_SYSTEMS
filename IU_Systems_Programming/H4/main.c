/* main.c --- 
 * 
 * Filename: main.c
 * Description: Main Method
 * Author: Robert Mulligan
 * Maintainer: 
 * Created:  March 20 2016
 * Last-Updated: 
 *           By: Robert Mulligan
 *     Update #: 
 * Keywords: Main Method
 * 
 */

/* Commentary: 
 *  	I worked with James Mantz - Some of our functions will be similar
 * 
 * 
 */

/* Change log:
 *  None
 * 
 */

/* Copyright (c) 2015 The Trustees of Indiana University and 
 * Indiana University Research and Technology Corporation.  
 * 
 * All rights reserved. 
 * 
 * Additional copyrights may follow 
 */

/* Code: */
#include <stdio.h> 
#include <stddef.h> 
#include <stdint.h> 
#include "testvector.h"
#include "machine.h"
#include "flags.h"

uint32_t reg[16];
uint32_t psr;

int i = 0; // for use in for loops

int main(int argc, unsigned long long a, unsigned long long b) {




  printf("printing a: %d\n  printing b: %d\n", &a, &b); 

  uint32_t a_1 = ((a & 0xFFFFFFFF00000000) >> 32);
  uint32_t a_2 = (a & 0xFFFFFFFF);
  
  uint32_t b_1 = ((b & 0xFFFFFFFF00000000) >> 32);
  uint32_t b_2 = (b & 0xFFFFFFFF);


  reg[0] = a_1;
  reg[1] = a_2;
  reg[2] = b_1;
  reg[3] = b_2;
  adds(1,3);
  adcs(0,2);

  unsigned long long ans = ( (reg[0] >> 32) | reg[1]); // & 0x0000000000000000);
  printf("%x\n", ans);
  

  
  // Argument to test_instructions can be ALL to run all of tests or a specific
  // instruction can be tested by passing the name. 
  // ADCS, ADDS, SUBS, ANDS, BICS, LSLS, ASRS
  // To run the instruction tests for all of the instructions, pass ALL
   test_instructions(ANDS); 
   test_instructions(ADCS); 
   test_instructions(ADDS); 
   test_instructions(BICS); 
   test_instructions(LSLS);
   test_instructions(ASRS); 
 return (0);
}

void ands(int rn, int rm) {
  // Include your code to emulate the "and" instruction:
  // subs rn, rm
  // rn = index where operand1 is located in reg[], also destination for result
  // rm = index where operand2 is located in reg[]

  reg[rn] &= reg[rm];

  // Negative Flag 
  if (reg[rn]&0x80000000) SET_N;
  else CLEAR_N;
 
  // Zero Flag 
  if (!reg[rn]) SET_Z;
  else CLEAR_Z;
 }

void adcs(int rn, int rm) {
  // Include your code to emulate the "adc" instruction:
  // adcs rn, rm
  // rn = index where operand1 is located in reg[], also destination for result
  // rm = index where operand2 is located in reg[]
  // reg[rn] &= reg[rm];
  int c = reg[rn];
  if (psr == 0x20000000) reg[rn] += reg[rm] + 1;
  else reg[rn] += reg[rm];

  int xrn = reg[rn];
  int xrm = reg[rm];
  
  //zero
  psr = 0;
  if (reg[rn] == 0 && c > reg[rn]) {
      SET_C;
      SET_Z;
    }
    else { SET_Z; }
  
  
  //negative
  if (reg[rn] & 0x80000000) { SET_N; }

  //carry
  if(c > reg[rn]) { SET_C; }

  //overflow
  if (c > 0 && xrm > 0 && xrn < 0){ SET_V; }

}

void adds(int rn, int rm) {
  // Include your code to emulate the "add" instruction:
  // adds rn, rm
  // rn = index where operand1 is located in reg[], also destination for result
  // rm = index where operand2 is located in reg[]
  //reg[rn] &= reg[rm];
  int c = reg[rn];
  reg[rn] += reg[rm];

  psr = 0;

  //zero
  if (reg[rn] == 0) {
    if (c > reg[rn]) {
      SET_C;
      SET_Z;
    }
    else { SET_Z; }
  }
  
  //negative
  if (reg[rn] & 0x80000000) {
    SET_N;
  }

  //carry
  if(c > reg[rn]) {
    SET_C;
  }

  //overflow
  int xrn = reg[rn];
  int xrm = reg[rm];
  if (c > 0 && xrm > 0 && xrn < 0){
      SET_V;
	}
}

void bics(int rn, int rm) {
  // Include your code to emulate the "bics" instruction:
  // subs rn, rm
  // rn = index where operand1 is located in reg[], also destination for result
  // rm = index where operand2 is located in reg[]
  //reg[rn] &= reg[rm];

  int xrn = reg[rn];
  int xrm = reg[rm];

  int xrn_c = xrn;
  int xrm_c = xrm;

  int xrnarr[32];
  int xrmarr[32];

 

  for (i = 0; i < 32; i++) {
    xrnarr[i] = 0;
    xrmarr[i] = 0;
  }

 
  if (xrn_c >= 0) {
    for (i = 31; i >= 0; i--) {
      xrnarr[i] = xrn_c % 2;
      xrn_c = xrn_c / 2;
    }
  }
  else {
    xrn_c = -1 * xrn_c;
    xrn_c = xrn_c - 1;
    for(i = 31; i >= 0; i--) {
      xrnarr[i] = xrn_c % 2;
      xrn_c = xrn_c / 2;
    }
    i = 0;
    for(i; i < 32; i++) {
      if (xrnarr[i] == 0)
	xrnarr[i] = 1;
      else
	xrnarr[i] = 0;
    }
  }

    //rm
    if (xrm_c >= 0) {
      for (i = 31; i >= 0; i--) {
	xrmarr[i] = xrm_c % 2;
	xrm_c = xrm_c / 2;
      }
    }
    else {
 
      xrm_c = -1 * xrm_c;
      xrm_c = xrm_c - 1;
      for(i = 31; i >= 0; i--) {
	xrmarr[i] = xrm_c % 2;
	xrm_c = xrm_c / 2;
      }
      i = 0;
      for(i; i < 32; i++) {
	if (xrmarr[i] == 0)
	  xrmarr[i] = 1;
	else
	  xrmarr[i] = 0;
      }
    }

    int result[32];
    for (i = 0; i < 32; i++) {
      if((xrnarr[i] == 1) && (xrmarr[i] == 0))
	result[i] = 1;
      else
	result[i] = 0;
    }

    int re = 0;
    int pow = 1;
    i = 31;
    for (i; i >= 0; i--) {
      re = re + pow * result[i];
      pow = pow * 2;
    }

    reg[rn] = re;
    int c = reg[rn];


    //negative
    if (reg[rn] & 0x80000000) {
      SET_N;
    }

    //zero
    if (reg[rn] == 0) {
      if (c > reg[rn]) {
	SET_C;
	SET_Z;
      }
      else { SET_Z; } 
}
}

void lsls(int rn, int rm) {
  // Include your code to emulate the "lsls" instruction:
  // subs rn, rm
  // rn = index where operand1 is located in reg[], also destination for result
  // rm = index where operand2 is located in reg[]
  //reg[rn] &= reg[rm];

  int xrn = reg[rn];
  int xrm = reg[rm];

  int c = reg[rn];
  int x = 0;
  int b = 0; 
  int rem = 0;
  int y = 0;

  //positive
  if (xrm > 0) {
    if (xrm % 32 == 0) {
      if (xrm == 32)
	x = 0;
      else if (xrm <= 128) {
	y = 1;
	x = 0;
      }
      else
	x = reg[rn];
    }
    else {
      rem = xrm % 32;
      if (rem == 31) {
	y = 1;
	x = 0;
      }
      else {
	x = reg[rn] << rem;
      }
    }
    
  }
  //negative
  else {
    if (xrm == -2147483648) {
      x = reg[rn];
    }
    else {
    x = 0;
    y = 1;
    }
  }
  //Test
  //printf("%x\n", x);

  reg[rn] = x;

  psr = 0;

  //zero
  if (reg[rn] == 0) {
    if (c > reg[rn]) {
      if (y == 0)
	SET_C;
      SET_Z;
    }
    else
      SET_Z;
  }

  //negative
  if (reg[rn] & 0x80000000) {
    SET_N;
  }

  //carry
  if((b == 1 || c > reg[rn]) && y == 0) {
    SET_C;
  }

}

void asrs(int rn, int rm) {
  // Include your code to emulate the "asrs" instruction:
  // subs rn, rm
  // rn = index where operand1 is located in reg[], also destination for result
  // rm = index where operand2 is located in reg[]
  reg[rn] &= reg[rm];



}





/* main.c ends here */
