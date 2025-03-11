#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */
#include <arpa/inet.h>

#undef __Enter_n_Exit
#define __Enter_n_Exit void __exit_func(const char **__func_name_arg){ \
		printf("Exit(%s)\n", *__func_name_arg);  \
	} \
	const char *__attribute__((cleanup(__exit_func))) __func_name=__FUNCTION__;  \
	printf("Enter(%s)\n", __func_name); 

void child_func(void){
	__Enter_n_Exit; 
	printf("run child_func!!\n"); 
}

#undef __Enter_n_Exit
#define __Enter_n_Exit void __exit_func(const char **__func_name_arg){ \
		printf("Exit(%s)\n", *__func_name_arg);  \
	} \
	const char *__attribute__((cleanup(__exit_func))) __func_name=__FUNCTION__;  \
	printf("Enter(%s)\n", __func_name); 
void parent_func(void){
	__Enter_n_Exit; 
	printf("run father_func!!\n"); 
	printf("before child_func!!\n"); 
	child_func(); 
}

int main(int argc, char *argv[]){
	printf("%s@%d: \n", __FUNCTION__, __LINE__); 
	// prototype: enter and exit function prompt
	void _exit_func(const char **__func_name_arg){
		// printf("%s@%d: __func_name_arg(%s)\n", __FUNCTION__, __LINE__, *__func_name_arg); 
		printf("Exit(%s)\n", *__func_name_arg); 
	}
	const char *__attribute__((cleanup(_exit_func))) __func_name=__FUNCTION__; 
	printf("Enter(%s)\n", __func_name); 
	parent_func(); 
	return 0; 
}
