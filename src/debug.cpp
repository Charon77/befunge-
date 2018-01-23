#include "debug.h"


class NullBuffer : public std::streambuf
{
public:
  int overflow(int c) { return c; }
};



ostream& d(char* filename) {
  
  // Enable debugging?
  if (false){
    return cout<<"D["<<filename<<"]: ";
  } else {
    static NullBuffer null_buffer;
    static std::ostream null_stream(&null_buffer);
    return null_stream;
  }
}


ostream& e(char* filename) {
  
  // Enable Error?
  if (true){
    return cout<<"ERROR! E["<<filename<<"]: ";
  } else {
    static NullBuffer null_buffer;
    static std::ostream null_stream(&null_buffer);
    return null_stream;
  }
}