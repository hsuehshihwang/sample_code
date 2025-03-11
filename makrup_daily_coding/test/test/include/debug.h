#ifndef __debug_h__
#define __debug_h__
#include <stdio.h>
#include <string.h>
extern int __indent; 
#define __REPEATSTR_5 "     "
#define __REPEATSTR_10 __REPEATSTR_5 __REPEATSTR_5
#define __REPEATSTR_20 __REPEATSTR_10 __REPEATSTR_10
#define __REPEATSTR_40 __REPEATSTR_20 __REPEATSTR_20
#define __REPEATSTR_80 __REPEATSTR_40 __REPEATSTR_40
#define __REPEATSTR __REPEATSTR_80
#define __file__ strrchr(__FILE__,'/')?strrchr(__FILE__,'/')+1:__FILE__
#define dbg(fmt,...) do{\
	fprintf(stdout,"%s(%d)@%s: "fmt"\n",__FUNCTION__,__LINE__,__file__,##__VA_ARGS__); \
	fflush(stdout); \
}while(0); 
#define dbge(fmt,...) do{\
	fprintf(stderr,"%s(%d)@%s: "fmt"\n",__FUNCTION__,__LINE__,__file__,##__VA_ARGS__); \
	fflush(stderr); \
}while(0); 
#define enter_n_exit() \
	void __cleanup_func(const char **__str){         \
	    printf("%.*sExit %s()...\n", --__indent, __REPEATSTR, (char *)*__str); \
	} \
	const char __attribute__((cleanup(__cleanup_func))) *__func_str=__FUNCTION__; \
    printf("%.*sEnter %s()...\n", __indent++, __REPEATSTR, (char *)__func_str); 
void debug_main(int argc, char *argv[]);
#endif /*__debug_h__*/
