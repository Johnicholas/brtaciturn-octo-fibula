#include <stdio.h>
#include <emscripten.h>

int done = 0;

// extern void set_knob_position(int x, int y);
extern void spin_bunny();

void update() {
  spin_bunny();
}

void tick() {
  EM_ASM(
         renderer.render(stage);
         );
  update();
  if (done) {
    emscripten_cancel_main_loop();
  }
}

void begin() {
  emscripten_set_main_loop(tick, 0, 0);
}
