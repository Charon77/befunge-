#ifndef FILE_H
#define FILE_H

#include <fstream>
using namespace std;

char get_char_at_pos(int x, int y, fstream* f);

fstream* open_file(char* filename);



#endif