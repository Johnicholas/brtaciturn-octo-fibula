#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif

#include <stdio.h>
#include <assert.h>

#define ceu_out_assert(v) ceu_sys_assert(v)
void ceu_sys_assert (int v) {
  assert(v);
}

#define ceu_out_log(m,s) ceu_sys_log(m,s)
void ceu_sys_log (int mode, long s) {
  switch (mode) {
  case 0:
    printf("%s", (char*)s);
    break;
  case 1:
    printf("%lX", s);
    break;
  case 2:
    printf("%ld", s);
    break;
  }
}

#define PLAYER_SPEED 0.5
#define CHASER_SPEED 0.4
#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 1000
#define PLAYER_SIZE 20

float player_x = 100;
float player_y = 100;
float player_dx;
float player_dy;
  
float chaser_x = 100;
float chaser_y = 100;
float chaser_dx;
float chaser_dy;
int chaser_will_think;

#include "_ceu_app.c"

extern void ceu_app_init (tceu_app* app);

byte CEU_DATA[sizeof(CEU_Main)];
tceu_app app;

#include <stdlib.h>
#include <math.h>
#include "SDL.h"

#define TRUE 1

SDL_Surface *screen;
int running = TRUE;

// returns the number of millisecons between decisions,
// the speed of the chaser's reflexes.
int reflex() {
  // TODO: some jitter?
  return 50;
}

void render() {   
  struct SDL_Rect rect;
  rect.x = 0;
  rect.y = 0;
  rect.w = SCREEN_WIDTH;
  rect.h = SCREEN_HEIGHT;
  SDL_FillRect(screen, &rect, 0);
  rect.x = player_x;
  rect.y = player_y;
  rect.w = PLAYER_SIZE;
  rect.h = PLAYER_SIZE;
  SDL_FillRect(screen, &rect, 0xffff0000);
  rect.x = chaser_x;
  rect.y = chaser_y;
  rect.w = PLAYER_SIZE;
  rect.h = PLAYER_SIZE;
  SDL_FillRect(screen, &rect, 0x000000ff);

}


void mainloop() {
  // Render stuff
  render();

  SDL_Flip(screen);  

  // Poll for events, and handle the ones we care about.
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT: exit(0); break;
    case SDL_MOUSEBUTTONDOWN: /* TODO */ break;
    case SDL_MOUSEBUTTONUP: /* TODO */ break;
    case SDL_KEYDOWN: /* TODO */ break;
    case SDL_KEYUP:
      switch (event.key.keysym.sym) {
      case SDLK_ESCAPE: exit(0); break;
      case SDLK_UP: 
        if (player_dy > -1*PLAYER_SPEED) {
          player_dy -= PLAYER_SPEED;
        }
        break;
      case SDLK_DOWN:
        if (player_dy < PLAYER_SPEED) {
          player_dy += PLAYER_SPEED;
        }
        break;
      case SDLK_LEFT:
        if (player_dx > -1*PLAYER_SPEED) {
          player_dx -= PLAYER_SPEED;
        }
        break;
      case SDLK_RIGHT:
        if (player_dx < PLAYER_SPEED) {
          player_dx += PLAYER_SPEED;
        }
        break;
      }
    }
  }
  // physics
  chaser_x += chaser_dx;
  player_x += player_dx;
  if (player_x + PLAYER_SIZE > SCREEN_WIDTH) {
    player_x = SCREEN_WIDTH - PLAYER_SIZE;
    player_dx = 0;
  } else if (player_x < 0) {
    player_x = 0;
    player_dx = 0;
  }
  chaser_y += chaser_dy;
  player_y += player_dy;
  if (player_y + PLAYER_SIZE > SCREEN_HEIGHT) {
    player_y = SCREEN_HEIGHT - PLAYER_SIZE;
    player_dy = 0;
  } else if (player_y < 0) {
    player_y = 0;
    player_dy = 0;
  }
  // possibly tick the chaser's behavior
  int now = SDL_GetTicks();
  if (now > chaser_will_think) {
    chaser_will_think = now + reflex();
    ceu_sys_go(&app, CEU_IN_TICK, NULL);
  }
}

// Entry point
int main(int argc, char *argv[]) {
  app.data = (tceu_org*) &CEU_DATA;
  app.init = &ceu_app_init;
  app.init(&app);

  SDL_Init(SDL_INIT_VIDEO);
  atexit(SDL_Quit);
  chaser_will_think = SDL_GetTicks() + reflex();
  screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_SWSURFACE);  
  if ( screen == NULL ) 
  {
    exit(1);
  }
#ifdef EMSCRIPTEN
  emscripten_set_main_loop(mainloop, 30, 0);
#else
  while (1)
  {
    mainloop();
  }
#endif    
  return 0;
}

