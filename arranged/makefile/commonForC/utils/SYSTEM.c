#include "SYSTEM.h"
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

