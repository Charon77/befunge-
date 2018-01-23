#include "vars.h"
#include "debug.h"

void put_var (Vars* s, int val, int x, int y) {
  d("vars.h")<<"PUT " << val << " to " << x << "," << y <<endl ;
  s->int_vars[x][y] = val;
  s->flag_vars[x][y] = 1;
  
  s->x_min = std::min(s->x_min, x);
  s->x_max = std::max(s->x_max, x);
  s->y_min = std::min(s->y_min, y);
  s->y_max = std::max(s->y_max, y);
}

int get_var (Vars* s, int x, int y) {
  d("vars.h")<<"GET " << " FROM " << x << "," << y <<endl ;
  return s->int_vars[x][y];
}

bool has_var (Vars* s, int x, int y) {
  return (s->flag_vars[x][y] == 1);
}

Vars::Vars() {
  x_min = 1;
  x_max = 50;
  y_min = 1;
  y_max = 20;
}