/* pong.c --- 
 * 
 * Filename: pong.c
 * Description: 
 * Author: Robert Mulligan
 * Maintainer: 
 * Created: Mon Aug 11 10:50:08 2014
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

/* Copyright (c) 2004-2007 The Trustees of Indiana University and 
 * Indiana University Research and Technology Corporation.  
 * 
 * All rights reserved. 
 * 
 * Additional copyrights may follow 
 */

/* Code: */

#include "c335sim.h"
#include "rect.h"
#include "screen.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL/SDL.h>

#define PADDLE_MOVE_INCREMENT 3
#define PADDLE_HEIGHT 25
#define PADDLE_THICKNESS 3
#define BALL_DIM 3
#define EVENT_LOOP_TIME 20

rect_t left_paddle;
rect_t right_paddle;
rect_t ball;

int ball_vx = 1;
int ball_vy = 2;

int flip; 

/*The event loop that handles the key input*/
void event_loop(void) {
  static int paddle_left_move = 0; 
  static int paddle_right_move = 0;
  SDL_Event event;
  SDL_PollEvent(&event);
  switch(event.type) {
  case SDL_KEYUP:
    switch (event.key.keysym.sym) {
    case SDLK_UP:
      paddle_right_move = 0;
      break;
    case SDLK_DOWN:
      paddle_right_move = 0;
      break;
    case SDLK_a:
      paddle_left_move = 0;
      break;
    case SDLK_z:
      paddle_left_move = 0;
      break;
    default:
      break;
    }
    break;
  case SDL_KEYDOWN:
    switch (event.key.keysym.sym) {
    case SDLK_UP:
      paddle_right_move = -PADDLE_MOVE_INCREMENT;
      break;
    case SDLK_DOWN:
      paddle_right_move = PADDLE_MOVE_INCREMENT;
      break;
    case SDLK_a:
      paddle_left_move = -PADDLE_MOVE_INCREMENT; 
      break;
    case SDLK_z:
      paddle_left_move = PADDLE_MOVE_INCREMENT; 
      break;
    case SDLK_q:
      printf("Q PRESSED - Exit Program\n");
      exit(0);
      break;
    case SDLK_n:
      printcords();
    default:
      break;
    }
    break;
  }
  if (paddle_left_move) {
    moveRect(&left_paddle, 0, paddle_left_move, BLACK);
  }
  if (paddle_right_move) {
    moveRect(&right_paddle, 0, paddle_right_move, BLACK);
  }
}


void printcords(void) {
  
  int rand_line = (int) (abs(rand() % 32)); // random line
  // printf("this is the random line variable: %d \n", rand_line); 
  FILE *file;
  char *mode = "r";
  
  file = fopen("cords.txt", mode);
  
  if (file == NULL) {
    fprintf(stderr, "Can't open input file in.list!\n");
    exit(1);
  }
  
  char *line; 
  int count = 0;
  while (count < 9)
    {
      count++;
      fgets(line, 30, file);
      
      if ( count == rand_line && line != NULL )
	{  
	  printf("%s", line);
	  //  printf("------- printed line number: %d --------- \n", count); 
	    drawString(40,100,line,WHITE,BLACK);
	}
    }
 

  fclose(file); 

}

/*Where the collisions are handled*/
void pong_game(void) {
  int collision;

  drawString(40,60,"hit q to quit",WHITE,BLACK);
  redrawRect(&left_paddle);
  redrawRect(&right_paddle);
  event_loop();
  collision = moveRect(&ball, ball_vx, ball_vy, BLACK);

  switch (collision) {
  case COLLISION_TOP:
    ball_vy = -ball_vy;
    break;
  case COLLISION_BOTTOM:
    ball_vy = -ball_vy;
    break;
  case COLLISION_LEFT:
    ball_vx = -ball_vx;
    break;
  case COLLISION_RIGHT:
    ball_vx = -ball_vx;
    break;
  }
}

/*Where the pong_game() is called the rectangels are initialized. */
int c335_main( int argc, char *argv[] ) {

  int  capL = 'L', lowL = 'l';

  flip = 0; 

  if(argc > 0){ 
    if(argv[0] == capL ||  argv[0] == lowL)
      { flip = 1; }
      }



  fillScreen(BLACK);
  initRect(&left_paddle,0,ST7735_height/2-(PADDLE_HEIGHT/2),PADDLE_THICKNESS,PADDLE_HEIGHT,WHITE,flip);
  initRect(&right_paddle,ST7735_width-PADDLE_THICKNESS,ST7735_height/2-(PADDLE_HEIGHT/2),PADDLE_THICKNESS,PADDLE_HEIGHT,WHITE,flip);
  initRect(&ball,ST7735_width/2-(BALL_DIM/2),ST7735_height/2-(BALL_DIM/2),BALL_DIM,BALL_DIM,WHITE,flip);



  while (1) {
    pong_game();
    Delay(EVENT_LOOP_TIME);
  }
} 

/* pong.c ends here */
