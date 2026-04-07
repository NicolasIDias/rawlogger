#pragma once
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#define bool _Bool
#define true 1
#define false 0

typedef enum LOG_LEVEL
{
    LOG_TRACE,
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR,
    LOG_FATAL
} log_level;

typedef struct log_event
{

    log_level level;
    const char *filepath;
    int line;

} log_t;

bool log_init()
{
}

void internal_log(const char *file, int line, const char *format, log_level level, ...)
{
    log_t log = {level, file, line};

    va_list args;
    va_start(args, format);

    printf("FILE: %s\n", file);
    printf("LINE: %d\n", line);
    vprintf(format, args);
    printf("\n");

    va_end(args);
}

// #define LOG(format, ...) internal_log(__FILE__, __LINE__, format, ##__VA_ARGS__)
#define LOG_TRACE(format, ...) internal_log(__FILE__, __LINE__, format, LOG_TRACE, ##__VA_ARGS_)
#define LOG_DEBUG(format, ...) internal_log(__FILE__, __LINE__, format, LOG_DEBUG, ##__VA_ARGS__)
#define LOG_INFO(format, ...) internal_log(__FILE__, __LINE__, format, LOG_INFO, ##__VA_ARGS__)
#define LOG_WARN(format, ...) internal_log(__FILE__, __LINE__, format, LOG_WARN, ##__VA_ARGS__)
#define LOG_ERROR(format, ...) internal_log(__FILE__, __LINE__, format, LOG_ERROR, ##__VA_ARGS__)
#define LOG_FATAL(format, ...) internal_log(__FILE__, __LINE__, format, LOG_FATAL##__VA_ARGS__)
