#ifndef __SYSTEM_h__
#define __SYSTEM_h__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include "debug.h"

int SYSTEM(const char *format, ...);
void SYSTEM_test(void);

#endif /*__SYSTEM_h__*/
