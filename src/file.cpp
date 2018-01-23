#include "file.h"

#include <fstream>
#include "debug.h"
using namespace std;

char get_char_at_pos(int x, int y, fstream* fs) {
  fs->seekg(fs->beg); //rewind
  
  char linebuffer[900];
  
  while (y-- >= 0) {
    
    
    fs->getline(linebuffer, 900);
    
    d("file.cpp::BITS")<<fs->good()<<fs->bad()<<fs->eof();
    
  }
  
  char c = linebuffer[x];
  
  d("file.cpp::get_char_at_pos")<<"'"<<c<<"'"<<endl;
  
  return c;
}

fstream* open_file(char* filename) {
  static fstream fs;
  fs.open(filename, fstream::in);
  fs.exceptions ( fs.failbit | fs.eofbit );
  return &fs;
  
}