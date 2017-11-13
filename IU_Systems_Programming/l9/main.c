/* main.c ---
*
* Filename: main.c
* Description: main program to build a compass
* Author: Robert Mulligan
* Maintainer: Robert Mulligan
* Created: Thu Feb 10 2016
/* Code: */

#include <stm32f30x.h> // Pull in include files for F30x standard drivers
#include <f3d_uart.h>
#include <f3d_user_btn.h>
#include <f3d_lcd_sd.h>
#include <f3d_i2c.h>
#include <f3d_accel.h>
#include <f3d_mag.h>
#include <stdio.h>
#include <math.h>
#include <f3d_led.h>
#include <f3d_nunchuk.h>
#include <f3d_gyro.h>



#define TIMER 20000

void gyro_display(void);
void tilt(void);
void compass(void);
void nun_tilt(void);


uint16_t colors[25];
uint16_t colors2[25];
uint16_t colors3[25];

// floats arrays
float mag_data[3];
float accel_data[3];


float roll;
float pitch;
float heading;
float degrees;   
int led;
int inc, size;
int row, col;


//gyro float data
float val[3];

//for the strings that print out
char data_string_x[30]; 
char data_string_y[30]; 
char data_string_z[30]; 

uint16_t x_0,y_0,x_1,y_1;

// nunchuk data
float nun_data[3];

int main(void) {


  // Set up your inits before you go ahead
  f3d_uart_init();
  delay(10);
  f3d_lcd_init();
  delay(10);
  f3d_i2c1_init();
  delay(10); 
  f3d_accel_init();
  delay(10);
  f3d_mag_init();
  delay(10); 
  f3d_led_init();
  delay(10); 
  f3d_nunchuk_init();
  delay(10);
  f3d_gyro_init();
  delay(10);


  // Setup buffers
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);


  int steven = 0;
  for(steven=0; steven < 25; steven++) {
    colors[steven] = WHITE;
    colors2[steven] = BLACK;
    colors3[steven] = RED;
  }

  f3d_lcd_fillScreen(WHITE); 

  nunchuk_t nunchuk; 
  int mode = 0;
  int next = 0;
  int prev = 0;
  int counter = 0;
  char* nun_title;
  nun_title = "Nunchuk Tilt";
  char* board_title;
  board_title = "Board Tilt";
  char* compass_title;
  compass_title = "Compass";
  char* gyro_title;
  gyro_title = "Gyro Data";
  while(1) {
    if(mode == 2) {
      // the while loop runs very quickly when in compass mode
      // this prevents the next and previous buttons from being sensitive when in compass mode
      delay(250);
    }
    counter = counter + 1;
    f3d_nunchuk_read(&nunchuk);
    
    //reads if next or previous is being held
    if((nunchuk.jx > 154 || nunchuk.c == 1)&& counter > 3) { next = 1; counter = 0; }
    if((nunchuk.jx < 100 || nunchuk.z == 1)&& counter > 3) { prev = 1; counter = 0; }
    
    //switch mode based upon whether is it next or previous
    if(next) {
      switch (mode){
      case 0: //mode is currently 0, change to mode 1
	mode = 1;
	f3d_lcd_fillScreen(BLACK);
       	f3d_lcd_drawString(30, 50, board_title, WHITE, BLACK);
	delay(500);
	f3d_lcd_fillScreen(WHITE);
	break;
      case 1:  //mode is currently 1, change to mode 2
	mode = 2;
	f3d_lcd_fillScreen(BLACK);
       	f3d_lcd_drawString(30, 50, compass_title, WHITE, BLACK);
	delay(500);
	f3d_lcd_fillScreen(WHITE);
	break;
      case 2:  //mode is currently 2, change to mode 3
	mode = 3;
	f3d_led_all_off();
	f3d_lcd_fillScreen(BLACK);
       	f3d_lcd_drawString(30,50, nun_title, WHITE, BLACK);
	delay(500);
	f3d_lcd_fillScreen(WHITE);
	break;
      case 3: //mode is currently 3, change to mode 0
	mode = 0;
	f3d_lcd_fillScreen(BLACK);
       	f3d_lcd_drawString(30, 50, gyro_title, WHITE, BLACK);
	delay(500);
	f3d_lcd_fillScreen(WHITE);
	break;
      }
    } else if (prev) {
      switch (mode){
      case 0: //mode is currently 0, change to mode 3
	mode = 3;
	f3d_lcd_fillScreen(BLACK);
       	f3d_lcd_drawString(30, 50, nun_title, WHITE, BLACK);
	delay(500);
	f3d_lcd_fillScreen(WHITE);
	break;
      case 1:  //mode is currently 1, change to mode 0
	mode = 0;
	f3d_lcd_fillScreen(BLACK);
       	f3d_lcd_drawString(30, 50, gyro_title, WHITE, BLACK);
	delay(500);
	f3d_lcd_fillScreen(WHITE);
	break;
      case 2:  //mode is currently 2, change to mode 1
	mode = 1;
	f3d_led_all_off();
	f3d_lcd_fillScreen(BLACK);
       	f3d_lcd_drawString(30, 50, board_title, WHITE, BLACK);
	delay(500);
	f3d_lcd_fillScreen(WHITE);
	break;
      case 3: //mode is currently 3, change to mode 2
	mode = 2;
	f3d_lcd_fillScreen(BLACK);
       	f3d_lcd_drawString(30, 50, compass_title, WHITE, BLACK);
	delay(500);
	f3d_lcd_fillScreen(WHITE);
	break;
      }
    }

    //based on mode tell which function to run
    if (mode == 0){
      gyro_display();
    } else if (mode == 1){
      tilt(); 
    } else if (mode == 2) {
      compass(); 
    } else if (mode == 3) {
      nun_data[0] = nunchuk.ax;
      nun_data[1] = nunchuk.ay;      
      nun_data[2] = nunchuk.az;
      nun_tilt();
    }
  
    //reset next and previous
    next = 0;
    prev = 0; 
    // nun_data[0] = nunchuk.ax;
    // nun_data[1] = nunchuk.ay;      
    // nun_data[2] = nunchuk.az;


  }

}



void gyro_display(void) {

  //place gyro data into array
  f3d_gyro_getdata(val);
  
  //Strings for text values printed on lcd
  char xaxis[20];
  sprintf(xaxis, "X-Axis: %f", val[0]);
  char yaxis[20];
  sprintf(yaxis, "Y-Axis: %f", val[1]);
  char zaxis[20];
  sprintf(zaxis, "Z-Axis: %f", val[2]);
  
    
  //draw string for x-axis
  f3d_lcd_drawString(10, 20, xaxis, BLACK, WHITE);
  //clear any previous rectangle with white rectangle
  f3d_lcd_drawRectangle(WHITE, 10, 35, 125, 45);
  //based on x-axis value, create a green rectangle for a positive value
  //and a red rectangle for negative values
  if(val[0] > 300){
    f3d_lcd_drawRectangle(GREEN, 10, 35, 125, 45);
  } else if (val[0] > 200) {
    f3d_lcd_drawRectangle(GREEN, 10, 35, 100, 45);
  } else if (val[0] > 100) {
    f3d_lcd_drawRectangle(GREEN, 10, 35, 75, 45);
  } else if (val[0] > 5) {
    f3d_lcd_drawRectangle(GREEN, 10, 35, 50, 45);
  } else if (val[0] < -300) {
    f3d_lcd_drawRectangle(RED, 10, 35, 125, 45);
  }  else if (val[0] < -200) {
    f3d_lcd_drawRectangle(RED, 10, 35, 100, 45);
  } else if (val[0] < -100) {
    f3d_lcd_drawRectangle(RED, 10, 35, 75, 45);
  }  else if (val[0] < -5) {
    f3d_lcd_drawRectangle(RED, 10, 35, 50, 45);
  }

  //same process as the x-axis for y-axis
  f3d_lcd_drawString(10, 50, yaxis, BLACK, WHITE);
  f3d_lcd_drawRectangle(WHITE, 10, 65, 125, 75);
  if(val[1] > 300){
    f3d_lcd_drawRectangle(GREEN, 10, 65, 125, 75);
  } else if (val[1] > 200) {
    f3d_lcd_drawRectangle(GREEN, 10, 65, 100, 75);
  } else if (val[1] > 100) {
    f3d_lcd_drawRectangle(GREEN, 10, 65, 75, 75);
  } else if (val[1] > 5) {
    f3d_lcd_drawRectangle(GREEN, 10, 65, 50, 75);
  } else if (val[1] < -300) {
    f3d_lcd_drawRectangle(RED, 10, 65, 125, 75);
  }  else if (val[1] < -200) {
    f3d_lcd_drawRectangle(RED, 10, 65, 100, 75);
  } else if (val[1] < -100) {
    f3d_lcd_drawRectangle(RED, 10, 65, 75, 75);
  }  else if (val[1] < -5) {
    f3d_lcd_drawRectangle(RED, 10, 65, 50, 75);
  }
  
  //same process as x and y-axis for z-axis
  f3d_lcd_drawString(10, 80, zaxis, BLACK, WHITE);
  f3d_lcd_drawRectangle(WHITE, 10, 95, 125, 105);
  if(val[2] > 300){
    f3d_lcd_drawRectangle(GREEN, 10, 95, 125, 105);
  } else if (val[2] > 200) {
    f3d_lcd_drawRectangle(GREEN, 10, 95, 100, 105);
  } else if (val[2] > 100) {
    f3d_lcd_drawRectangle(GREEN, 10, 95, 75, 105);
  } else if (val[2] > 5) {
    f3d_lcd_drawRectangle(GREEN, 10, 95, 50, 105);
  } else if (val[2] < -300) {
    f3d_lcd_drawRectangle(RED, 10, 95, 125, 105);
  }  else if (val[2] < -200) {
    f3d_lcd_drawRectangle(RED, 10, 95, 100, 105);
  } else if (val[2] < -100) {
    f3d_lcd_drawRectangle(RED, 10, 95, 75, 105);
  }  else if (val[2] < -5) {
    f3d_lcd_drawRectangle(RED, 10, 95, 50, 105);
  }

}

void compass(void){
  
  f3d_accel_read(accel_data); 
  f3d_mag_read(mag_data);
  double angle1 = atan(accel_data[0]/sqrt(pow(accel_data[1],2)+pow(accel_data[2],2)));
  double angle2 = atan(accel_data[1]/sqrt(pow(accel_data[0],2)+pow(accel_data[2],2)));
  double Xh = mag_data[0]*cos(angle1)+mag_data[2]*sin(angle1);
  double Yh = mag_data[0]*sin(angle2)*sin(angle1)+mag_data[1]*cos(angle2)-mag_data[2]*sin(angle2)*cos(angle1);
  double heading = atan2(Yh, Xh);
  heading *= 180/M_PI;
  f3d_led_all_off();
  //determine which LED to turn on that points north
  if(heading < 22.5 && heading >= -22.5){ //pointing south
    f3d_led_on(4);
  } else if (heading < -22.5 && heading >= -67.5){
    f3d_led_on(5);
  }  else if (heading < -67.5 && heading >= -112.5){
    f3d_led_on(6);
  } else if (heading < -112.5 && heading >= -157.5){
    f3d_led_on(7);
  }  else if (heading < -157.5 || heading >= 157.5){ //pointing north
    f3d_led_on(0);
  } else if (heading < 157.5 && heading >= 112.5){
    f3d_led_on(1);
  } else if (heading < 112.5 && heading >= 67.5){
    f3d_led_on(2);
  } else if (heading < 67.5 && heading >=  22.5){
    f3d_led_on(3);
  }
 }


void tilt(void) {
  
    f3d_accel_read(accel_data); 

    float x_a = accel_data[0];
    float y_a = accel_data[1];
    float z_a = accel_data[2];

    printf("board x_a: %f\n", x_a);
    printf("board y_a: %f\n", y_a);
    printf("board z_a: %f\n", z_a);

    pitch = atanf(x_a/sqrt(pow(y_a,2) + pow(z_a,2)));
    roll  = atanf(y_a/sqrt(pow(x_a,2) + pow(z_a,2)));


    f3d_lcd_setAddrWindow(64, 80, 64+4, 80+4, MADCTLGRAPHICS);
    f3d_lcd_pushColor(colors3, 25); 

    x_0 = 64+(roll*35)   ;
    y_0 = 80+(pitch*43)  ;    
    x_1 = 64+(roll*35)   +4;
    y_1 = 80+(roll*43)   +4;

    f3d_lcd_setAddrWindow(x_0, y_0, x_1, y_1, MADCTLGRAPHICS);
    f3d_lcd_pushColor(colors2, 25); 

    delay(225); 

    f3d_lcd_setAddrWindow(x_0, y_0, x_1, y_1, MADCTLGRAPHICS);
    f3d_lcd_pushColor(colors, 25); 

}

void nun_tilt(void){
 
  float x_a = nun_data[0]-511.5;
  float y_a = nun_data[1]-511.5;
  float z_a = nun_data[2]-511.5;


  pitch = atanf(x_a/sqrt(pow(y_a,2) + pow(z_a,2)));
  roll  = atanf(y_a/sqrt(pow(x_a,2) + pow(z_a,2)));


  f3d_lcd_setAddrWindow(64, 80, 64+4, 80+4, MADCTLGRAPHICS);
  f3d_lcd_pushColor(colors3, 25); 

  x_0 = 64+(roll*35)   ;
  y_0 = 80+(pitch*43)  ;    
  x_1 = 64+(roll*35)   +4;
  y_1 = 80+(roll*43)   +4;

  f3d_lcd_setAddrWindow(x_0, y_0, x_1, y_1, MADCTLGRAPHICS);
  f3d_lcd_pushColor(colors2, 25); 

  delay(225); 

  f3d_lcd_setAddrWindow(x_0, y_0, x_1, y_1, MADCTLGRAPHICS);
  f3d_lcd_pushColor(colors, 25); 

}







#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
  /* Infinite loop */
  /* Use GDB to find out why we're here */
  while (1);
}
#endif

/* main.c ends here */
