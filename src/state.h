#ifndef STATE_H
#define STATE_H

#include "stack.h"
#include "vars.h"

enum Direction {RIGHT=0, DOWN, LEFT, UP};

struct State {
  int cur_x;
  int cur_y;
  bool want_to_halt;
  bool want_to_skip;
  bool want_to_load_char;
  bool string_mode;
  char op;
  Stack* stack;
  Direction direction;
  Vars* vars;
};

State* new_state();

Direction random_dir();


#endif