
#include "stack.h"

stack *newStack(int capacity){
	stack *s=malloc(sizeof(*s)); 
	if(s){
		s->capacity=capacity;
		s->size=0; 
		s->data=malloc(sizeof(stackData)*s->capacity); 
	}
	return s; 
}

stack *pushStack(stack *s, stackData val){
	// printf("pushStack(%d)\n", val);  
	if(s){
		if(s->size<s->capacity){
			if(s->data){
				s->data[s->size]=val; 
				s->size++; 
			}
		}else{
			stackData *dataBkp=s->data; 
			if((s->data=realloc(s->data, sizeof(stackData)*s->capacity*2))!=NULL){
				s->capacity*=2; 
				// printf("enlarge capacity(%d)\n", s->capacity); 
				pushStack(s, val); 
			}else{
				s->data=dataBkp; 
			}
		}
	}
	return s; 
}

stack *popStack(stack *s){
	// printf("popStack()\n");  
	if(s){
		if(s->size){
			s->size--;
		}
	}
	return s; 
}

void destroyStack(stack *s){
	if(s){
		if(s->data) free(s->data); 
		free(s); 
	}
}

stack *dumpStack(stack *s){
	if(s){
		printf("s(%d): ", s->size); 
		for(int i=0; i<s->size; i++){
			printf("(%d)%s", s->data[i], i!=s->size-1?"->":""); 
		}
		printf("\n"); 
	}
	return s; 
}

stackData *topStack(stack *s){
	if(s){
		if(s->size){
			return &(s->data[s->size-1]); 
		}
	}
	return NULL; 
}
stackData *peekStack(stack *s, int i){
	if(s){
		if(i<s->size){
			return &(s->data[i]); 
		}
	}
	return NULL; 
}
stackData *buttomStack(stack *s){
	if(s){
		if(s->size){
			return &(s->data[0]); 
		}
	}
	return NULL; 
}
void stackTest(void){
	stack *s=newStack(2); 
	if(s){
		dumpStack(pushStack(s, 5)); 
		dumpStack(pushStack(pushStack(s, 9), 7)); 
		dumpStack(popStack(s)); 
		dumpStack(popStack(popStack(s))); 
		dumpStack(pushStack(pushStack(pushStack(pushStack(pushStack(s, 9), 7), 3), 2), 1)); 
		destroyStack(s); 
	}
}

