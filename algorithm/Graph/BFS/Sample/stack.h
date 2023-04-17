#ifndef __stack_h__
#define __stack_h__

#include <stdio.h>
#include <stdlib.h>
#include "debug.h"

typedef struct stack stack; 
typedef int stackData; 
struct stack {
	stackData *data; 
	int capacity; 
	int size; 
}; 

stack *newStack(int capacity);
stack *pushStack(stack *s, stackData val);
stack *popStack(stack *s);
stack *dumpStack(stack *s);
stackData *topStack(stack *s);
stackData *peekStack(stack *s, int i);
stackData *buttomStack(stack *s);
void destroyStack(stack *s);
void stackTest(void); 

#endif /*__stack_h__*/

