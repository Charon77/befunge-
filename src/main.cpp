#include <iostream>

using namespace std;

#include "befunge.h"
#include "file.h"

int main(int argc, char** argv) {
  
  if (argc == 1) {
    cout<<"Usage: befunge <filename>"<<endl;
    return -1;
  }
  
  State* s = init_befunge();
  
  try {
    fstream* fs = open_file(argv[1]);
    while ( !s->want_to_halt)  {
      
      char op = get_char_at_pos( s->cur_x, s->cur_y, fs);
      
      do_opcode(op, s);
    }
  
  
  } catch (std::exception e) {
    std::cerr << "Exception opening/reading/closing file\n";
  }
  
  
  return 1;
}