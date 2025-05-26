#include "util.h"
#include <stdio.h>
#include <stdarg.h>

void ProError(const string __restrict format, ...) {
    va_list args;
    va_start(args, format);

    vfprintf(stderr, format, args);

    va_end(args);
}
