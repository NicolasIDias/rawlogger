#pragma once
#include <stdio.h>
#include <stdarg.h>

void internal_log(const char *file, int line, const char *format, ...)
{
    va_list args;
    va_start(args, format);

    printf("FILE: %s\n", file);
    printf("LINE: %d\n", line);
    vprintf(format, args);
    printf("\n");

    va_end(args);
}
#define LOG(format, ...) internal_log(__FILE__, __LINE__, format, __VA_ARGS__)