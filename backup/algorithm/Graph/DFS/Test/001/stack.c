#include "stack.h"
stack *newStack(int capacity){
	stack *s=malloc(sizeof(stack)); 
	if(s){
		s->size=0; 
		s->capacity=capacity; 
		s->data=malloc(sizeof(stackData)*s->capacity); 
	}
	return s; 
}
stackData *searchStack(stack *s, stackData val){
	for(int i=0; i<s->size; i++){
		if(s->data[i]==val){
			return &(s->data[i]); 
		}
	}
	return NULL; 
}
stack *pushStack(stack *s, stackData val){
	if(s){
		if(s->size<s->capacity){
			stackData *tmp=s->data; 
			if((s->data=realloc(s->data, sizeof(stackData)*s->capacity*2))!=NULL){
				s->capacity*=2; 
				pushStack(s, val); 
			}else{
				s->data=tmp; 
			}
		}else{
			if(!searchStack(s, val)){
				s->data[s->size]=val; 
				s->size++; 
			}
		}
	}
	return s; 
}
stack *popStack(stack *s){
	if(s){
		if(s->size>0){
			s->size--; 
		}
	}
	return s; 
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
void destroyStack(stack *s){
	if(s){
		if(s->data) free(s->data); 
		free(s); 
	}
}
void stackTest(void){
	stack *s=newStack(2); 
	pushStack(s, 5); 
	pushStack(s, 9); 
	pushStack(s, 7); 
	dumpStack(s); 
	popStack(s); 
	dumpStack(s); 
	popStack(s); 
	popStack(s); 
	dumpStack(s); 
	pushStack(s, 5); 
	pushStack(s, 9); 
	pushStack(s, 7); 
	dumpStack(s); 
	popStack(s); 
	pushStack(s, 5); 
	pushStack(s, 9); 
	pushStack(s, 7); 
	dumpStack(s); 
	printf("top(%d)\n", *((stackData *)topStack(s))); 
	printf("buttom(%d)\n", *((stackData *)buttomStack(s))); 
	printf("peek(%d)\n", *((stackData *)peekStack(s, 1))); 
	destroyStack(s); 
}
