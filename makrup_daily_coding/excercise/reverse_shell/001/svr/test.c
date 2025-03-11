#include <stdio.h>
#define CALLTRACE() __attribute__((cleanup(calltrace))) const char *__calltrace_name=__FUNCTION__; printf("%s(): enter!!\n", __FUNCTION__); 
void test002(void){
	void calltrace(const char **name);
	CALLTRACE(); 
	printf("test002()!!\n"); 
}
