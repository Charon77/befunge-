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
  
  
  if ( s-> want_to_load_char ) {
    // This is the new char we want. Add to cache
    d("befunge.cpp::LOADED_FROM_FILE")<<s->cur_x<<", " <<s->cur_y<<endl;
    put_var (s->vars, c, s->cur_x, s->cur_y);
    s->want_to_load_char = false;
  }
  
  if ( s->get_value_from_file ) {
    // See 'g'
    s->get_value_from_file = 0;
    
    
    // Return cursor
    
    
    s->cur_y = stack->pop();
    s->cur_x = stack->pop();
    
    stack->push (c);
    
    advance_cursor(s);
    
    d("befunge.cpp::RETURNING")<<s->cur_x<<", " <<s->cur_y<<endl;
    return s;
  }
  
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
  int g_x ;
  int g_y ;
  
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
      g_y = stack->pop();
      g_x = stack->pop();
      if ( has_var(s->vars, g_x, g_y ) ) {
        // push val from the Vars
        stack->push ( get_var(s->vars, g_x, g_y ) );
      } else {
        // Oh no, we need to fetch from file
        
        s->get_value_from_file = 1; // We're going to get this from file
        
        // save current position
        stack->push (s->cur_x);
        stack->push (s->cur_y);
        
        d("befunge.cpp::STORE POSITION")<<s->cur_x<<", " <<s->cur_y<<endl;
        
        s->cur_x = g_x;
        s->cur_y = g_y;
        s->want_to_load_char = 1; // Tell main that we want a char from cursor location
        
        
        
        
        
        return s;
      }
    break;
    
    default:
      if (c != ' ' && (c < '0' || c > '9'))
        e("befunge.cpp")<<"Unrecognized symbol: '"<< c<<"'" << "[" << (int) c << "]" << " at: " << s->cur_x << "," << s->cur_y<< endl;
      
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
  
  // TODO: handle overflow (EOF)
  if (s->cur_x < s->vars->x_min) {
    s->cur_x = s->vars->x_max;
  }
  if (s->cur_y < s->vars->y_min) {
    s->cur_y = s->vars->y_max;
  }
  if (s->cur_x > s->vars->x_max) {
    s->cur_x = s->vars->x_min;
  }
  if (s->cur_y > s->vars->y_max) {
    s->cur_y = s->vars->y_min;
  }
  
  // Do we need to load op?
  if ( has_var (s->vars, s->cur_x, s->cur_y ) ) {
    d("befunge.cpp")<<"Cache HIT: " << s->cur_x << "," << s->cur_y << endl;
    s-> op = get_var( s->vars, s->cur_x, s->cur_y );
  } else {
    s->want_to_load_char = true; // yes we do
    d("befunge.cpp")<<"Cache MISS: " << s->cur_x << "," << s->cur_y << endl;
    
  }
  
  
}

