#include "debug.h"
void debug_main(int argc, char *argv[]){
	enter_n_exit(); 
	dbg(); 
	dbge(); 
	void cleanup_func(const char **__func){
		dbge("__func(%s)", *__func); 
	}
	const char __attribute__((cleanup(cleanup_func))) *func=__FUNCTION__; 
	printf("__file__: %s\n", __file__); 
}
