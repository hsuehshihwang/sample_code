#include "vector.h"
#include "debug.h"
#include <functional>
using namespace std; 
void vector_test(void){
	printf("%s@%d: \n", __FUNCTION__, __LINE__); 
	vector<function<void(void)>> v; 
	int fd=1; 
	v.push_back([&](void){
		printf("%s@%d: fd(%d)\n", __FUNCTION__, __LINE__, fd); 
	}); 
	v.push_back([&](void){
		fd=0; 
		printf("%s@%d: fd(%d)\n", __FUNCTION__, __LINE__, fd); 
	}); 
	v[1](); 	
	v[0](); 	
}
