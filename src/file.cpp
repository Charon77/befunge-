#include "file.h"

#include <fstream>
#include "debug.h"
using namespace std;

char get_char_at_pos(int x, int y, fstream* fs) {
  fs->seekg(fs->beg); //rewind
  
  char linebuffer[900];
  
  while (y--) {
    fs->getline(linebuffer, 900);
  }
  
  char c = linebuffer[x-1];
  
  d("file.cpp::get_char_at_pos")<<"'"<<c<<"'"<<endl;
  
  return c;
}

fstream* open_file(char* filename) {
  static fstream fs;
  fs.open(filename, fstream::in);
  fs.exceptions ( fs.failbit);
  return &fs;
  
}