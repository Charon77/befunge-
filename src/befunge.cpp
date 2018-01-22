#include "befunge.h"
#include "state.h"
#include "debug.h"
#include "util.h"
#include "io.h"


State* init_befunge() {
  return new_state();
}

State* do_opcode(char c, State* s) {
  
  Stack* stack = s->stack;
  
  d("befunge.cpp::FETCH_FROM_POS")<<s->cur_x<<", " <<s->cur_y<<endl;
  
  if (s->want_to_skip) {
    s->want_to_skip = false;
    advance_cursor(s);
    return s;
  }
  
  if (c == '"') {
    s->string_mode = !s->string_mode;
    advance_cursor(s);
    return s;
  }
  
  if (s->string_mode) {
    stack->push( (int) c) ;
    advance_cursor(s);
    return s;
  }
  
  
  if (c >= '0' && c<= '9') {
    d("befunge.cpp::NUM")<<c<<endl;
    stack->push( chr_to_int(c) );
  }
  
  
  
  int res;
  
  switch (c) {    
    case '@' :
      s->want_to_halt = true;
    break;
    case '.':
      print_int( stack->pop() );
    break;
    
    case ',':
      print_char( (char)stack->pop() );
    break;
    
    case ':':
      stack->push( stack->peek() );
    break;
    
    case '+':
      stack->push ( stack->pop() + stack->pop() );
    break;
    
    case '-':
      res = stack->pop();
      res = stack->pop() - res;
      stack->push (res);
    break;
    
    case '*':
      stack->push ( stack->pop() * stack->pop() );
    break;
    
    case '/':
      res = stack->pop();
      res = stack->pop() / res;
      stack->push (res);
    break;
    
    case '%':
      res = stack->pop();
      res = stack->pop() % res;
      stack->push (res);
    break;
    
    case '!':
      res = stack->pop();
      if (res == 0)
        stack->push(1);
      else
        stack->push(0);
    break;
    
    case '`':
      res = stack->pop();
      if( stack->pop() > res )
        stack->push(1);
      else
        stack->push(0);
    break;
    
    case '\\':
      stack->swap();
    break;
    
    case '$':
      stack->pop();
    break;
    
    
    case '&':
      stack->push (prompt_int());
    break;
    
    case '~':
      stack->push (prompt_char());
    break;
    
    case '#':
      s->want_to_skip = true;
    break;
    
    case '?':
      s->direction = random_dir();
    break;
      
    case '_':
      res = stack->pop();
      if (res == 0 )
        s->direction = RIGHT;
      else
        s->direction = LEFT;
    break;
    
    case '|':
      res = stack->pop();
      if (res == 0 )
        s->direction = DOWN;
      else
        s->direction = UP;
    break;
    
    case 'v':
      s->direction = DOWN;
    break;
    
    case '>':
      s->direction = RIGHT;
    break;
    
    case '^':
      s->direction = UP;
    break;
    
    case '<':
      s->direction = LEFT;
    break;
    
    case 'p':
      put_var(s->vars, stack->pop(), stack->pop(), stack->pop());
    break;
    
    case 'g':
      stack->push ( get_var(s->vars, stack->pop(), stack->pop() ) );
    break;
    
    default:
      if (c != ' ' && (c < '0' || c > '9'))
        e("befunge.cpp")<<"Unrecognized symbol: '"<< c<<"'" << "[" << (int) c << "]" << endl;
      
    break;
    
  }
  
  if (s->want_to_halt) {
    return s; // Don't advance cursor
  }
  
  advance_cursor(s);
  
  return s;
}

void advance_cursor(State* s) {
  switch (s->direction) {
    case RIGHT:
      s->cur_x += 1;
    break;
    case DOWN:
      s->cur_y += 1;
    break;
    case UP:
      s->cur_y -= 1;
    break;
    case LEFT:
      s->cur_x -= 1;
    break;
    default:
      s->cur_x += 1;
    break;
  }
  
}

