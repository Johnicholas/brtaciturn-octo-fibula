#include <stdio.h>
#include <emscripten.h>

extern void new_bunny(int key, int x, int y);
extern void spin_bunny(int key);
extern void set_bunny_position(int key, int x, int y);

#define ceu_out_emit_NEWBUNNY(X) new_bunny(X->_1, X->_2, X->_3)
#define ceu_out_emit_SPINBUNNY(X) spin_bunny(X->_1)
#define ceu_out_emit_SETBUNNYPOSITION(X) set_bunny_position(X->_1, X->_2, X->_3)

#define ceu_out_assert(X)
#define ceu_out_log(X)

#include "_ceu_app.c"

static byte CEU_DATA[sizeof(CEU_Main)];
static tceu_app app;


int up_down = 0;
int left_down = 0;
int right_down = 0;
int x = 200;
int y = 300;

void up_key_down() {
  ceu_sys_go( &app, CEU_IN_UP_KEY_DOWN, NULL );
}

void left_key_down() {
  ceu_sys_go( &app, CEU_IN_LEFT_KEY_DOWN, NULL );
}

void right_key_down() {
  ceu_sys_go( &app, CEU_IN_RIGHT_KEY_DOWN, NULL );
}

void up_key_up() {
  ceu_sys_go( &app, CEU_IN_UP_KEY_UP, NULL );
}

void left_key_up() {
  ceu_sys_go( &app, CEU_IN_LEFT_KEY_UP, NULL );
}

void right_key_up() {
  ceu_sys_go( &app, CEU_IN_RIGHT_KEY_UP, NULL );
}

void update() {
  ceu_sys_go( &app, CEU_IN_UPDATE, NULL );
  /*
  if (up_down) {
    spin_bunny(1);
    y -= 1;
  }
  if (left_down) {
    spin_bunny(2);
    x -= 1;
  }
  if (right_down) {
    spin_bunny(3);
    x += 1;
  }
  set_bunny_position(4, x, y);
  */
}

void begin() {
  memset(CEU_DATA, 0, sizeof(CEU_Main));
  app.data = (tceu_org*) &CEU_DATA;
  app.init = &ceu_app_init;
  app.init(&app);

  /*
  new_bunny(1, 200, 100);
  new_bunny(2, 100, 200);
  new_bunny(3, 300, 200);
  new_bunny(4, x, y);
  */
}

