#ifndef BEFUNGE_H
#define BEFUNGE_H

#include "state.h"

State* init_befunge();

State* do_opcode(char c, State* s);


// Private

void advance_cursor(State* s);

#endif