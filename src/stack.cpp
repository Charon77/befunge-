#include "stack.h"
#include "debug.h"

Stack::Stack() {
  stack_pointer=0;
  want_to_halt = false;
}

void Stack::push(int x) {
  d("stack.cpp::push")<<x<<endl;
  int_arr[++stack_pointer] = x;
}

int Stack::pop() {
  int x = int_arr[stack_pointer--];
  d("stack.cpp::pop")<<x<<endl;
  return x;
}

int Stack::peek() {
  int x = int_arr[stack_pointer];
  d("stack.cpp::peek")<<x<<endl;
  return x;
}

void Stack::swap() {
  // Swap top 2 values
  int_arr[stack_pointer    ] = int_arr[stack_pointer    ] + int_arr[stack_pointer - 1] ;
  int_arr[stack_pointer - 1] = int_arr[stack_pointer    ] - int_arr[stack_pointer - 1] ;
  int_arr[stack_pointer    ] = int_arr[stack_pointer    ] - int_arr[stack_pointer - 1] ;
} 