#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>

#define __file__ strrchr(__FILE__, '/')?strrchr(__FILE__, '/')+1:__FILE__
#define dbg(fmt, ...) do{\
	fprintf(stdout, "%s(%d)@%s: " fmt "\n", __FUNCTION__, __LINE__, __file__, ## __VA_ARGS__); \
	fflush(stdout); \
}while(0); 
#define dbge(fmt, ...) do{\
	fprintf(stderr, "%s(%d)@%s: " fmt "\n", __FUNCTION__, __LINE__, __file__, ## __VA_ARGS__); \
	fflush(stdout); \
}while(0); 

#define FUNC_BAR "=================================="
#define FUNC_TITLE \
    do { \
        printf("%.*s %s %.*s\n", (int)(strlen(FUNC_BAR)-strlen(__FUNCTION__)/2), FUNC_BAR, __FUNCTION__, (int)(strlen(FUNC_BAR)-strlen(__FUNCTION__)/2-strlen(__FUNCTION__)%2), FUNC_BAR); \
		fflush(stdout); \
    } while(0); 

int SYSTEM(const char *format, ...)
{
    char buf[512]={0};
    va_list arg;
    int ret = 0;

    va_start(arg, format);
    vsnprintf(buf, 512, format, arg);
    va_end(arg);

    ret = system(buf);
    usleep(1);
    return ret;
}

int main(int argc, char *argv[]){
	dbg(); 
	SYSTEM("ls %s", argv[1]?argv[1]:"/bin"); 
    exit(EXIT_SUCCESS);
}

