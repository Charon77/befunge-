#ifndef STACK_H
#define STACK_H



class Stack {  
  public:
    Stack();
    void push(int x);
    int pop();
    int peek();
    
    bool want_to_halt;
    void swap();
    
  
  
  int int_arr[90];
  int stack_pointer;
};

#endif