#include <stdlib.h>
int printf(const char *format, ...){
	system("echo hijack printf!!"); 
	return 0; 
}
