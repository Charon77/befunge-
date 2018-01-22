#include "io.h"
#include <iostream>
#include <conio.h>
#include <cstdlib>

using namespace std;

void print_int(int c) {
  cout<<c<<" ";
}

void print_char(char c) {
  cout<<c;
}

char prompt_char() {
  char x = (char) getch();
  
  if (x == 3) { // Ctrl + C
    cout << endl << endl << "Ctrl + C pressed! Stopping..." << endl;
    exit(1);
  }
  
  return x;
}

int prompt_int() {
  int x = (int) getch();
  
  if (x == 3) { // Ctrl + C
    cout << endl << endl << "Ctrl + C pressed! Stopping..." << endl;
    exit(1);
  }
  
  if (x >= '0' && x <= '9') {
    return x - '0';
  } else {
    // not a number
    return prompt_int() ; // TODO: UNROLL
  }
}