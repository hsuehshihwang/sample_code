#include "main.h"
int main(void){
	printf("%s@%d: \n", __FUNCTION__, __LINE__); 
	dbge(); 
	debug_test(); 
	vector_test(); 
	return 0; 
}
