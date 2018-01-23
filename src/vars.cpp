#include "vars.h"
#include "debug.h"

void put_var (Vars* s, int val, int x, int y) {
  d("vars.cpp")<<"PUT " << val << " to " << x << "," << y <<endl ;
  s->int_vars[x][y] = val;
  s->flag_vars[x][y] = 1;
  
  s->x_min = std::min(s->x_min, x);
  s->x_max = std::max(s->x_max, x);
  s->y_min = std::min(s->y_min, y);
  s->y_max = std::max(s->y_max, y);
}

int get_var (Vars* s, int x, int y) {
  d("vars.cpp")<<"GET " << " FROM " << x << "," << y <<endl ;
  return s->int_vars[x][y];
}

bool has_var (Vars* s, int x, int y) {
  return (s->flag_vars[x][y] == 1);
}

Vars::Vars() {
  x_min = 0;
  x_max = 120;
  y_min = 0;
  y_max = 30;
  
  int i;
  for (i = x_min; i<= x_max; i++ ) {
    int j;
    for (j = y_min; j<= y_max; j++ ) {
      int_vars[i][j] = (int)' ';
      flag_vars[i][j] = 0;
    }
  }
}