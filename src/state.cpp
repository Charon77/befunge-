#include "state.h"
#include <cstdlib>
#include <ctime>

State* new_state() {
  
  
  State* s = new State();
  
  s->cur_x = 1;
  s->cur_y = 1;
  
  s->stack = new Stack();
  s->direction = RIGHT;
  s->vars = new Vars();
  s->want_to_load_char = true; // Load first instruction
  
  return s;
}

Direction random_dir() {
  srand (time(NULL));
  int random = rand();
  
  if (random < 1*RAND_MAX/4 ) {
    return UP;
  }
  
  if (random < 2*RAND_MAX/4 ) {
    return LEFT;
  }
  
  if (random < 3*RAND_MAX/4 ) {
    return RIGHT;
  }
  
  if (random < 4*RAND_MAX/4 ) {
    return DOWN;
  }
  
  // catch all
  return RIGHT;
}