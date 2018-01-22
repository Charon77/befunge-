#ifndef VARS_H
#define VARS_H


struct Vars {
  int int_vars[255][255];
};

void put_var (Vars* s, int y, int x, int val);
int get_var (Vars* s, int y, int x);


#endif