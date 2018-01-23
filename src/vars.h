#ifndef VARS_H
#define VARS_H


struct Vars {
  int int_vars[255][255];
  int flag_vars[255][255]; // 0 if unset, 1 if set
  int x_min;
  int x_max;
  int y_min;
  int y_max;
  Vars();
};

void put_var (Vars* s, int y, int x, int val);
int get_var (Vars* s, int y, int x);
bool has_var (Vars* s, int y, int x);

#endif