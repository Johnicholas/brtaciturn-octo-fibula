#include <stdio.h>
#include <emscripten.h>

int done = 0;

extern void new_bunny(int key, int x, int y);
extern void spin_bunny(int key);

void update() {
  spin_bunny(1);
}

void begin() {
  new_bunny(1, 100, 100);
}
