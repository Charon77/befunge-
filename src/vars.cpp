#include "vars.h"
#include "debug.h"

void put_var (Vars* s, int val, int x, int y) {
  d("vars.h")<<"PUT " << val << " to " << x << "," << y <<endl ;
  s->int_vars[x][y] = val;
}

int get_var (Vars* s, int x, int y) {
  d("vars.h")<<"GET " << " FROM " << x << "," << y <<endl ;
  return s->int_vars[x][y];
}
