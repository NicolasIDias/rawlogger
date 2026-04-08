#pragma once
#include <stdio.h>
#include <stdarg.h>

#define bool _Bool
#define true 1
#define false 0

#define MAX_SINKS 8

typedef enum { 
    LOG_TRACE,
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR,
    LOG_FATAL
} log_level;

typedef struct {
    log_level level;
    const char *filepath;
    int line;
} log_t;

typedef struct {
    void (*log_func)(log_t *event, const char *format, va_list args);
} log_sink_t;

static log_sink_t sinks[MAX_SINKS];
static int sink_counter = 0;

void log_add_sink(log_sink_t sink)
{
    if(sink_counter < MAX_SINKS) {
        sinks[sink_counter++] = sink;
    }
}

void internal_log(const char *file, int line, const char *format, log_level level, ...)
{
    log_t event = {level, file, line};

    va_list args;

    va_start(args, level); 

    for (int i = 0; i < sink_counter; i++) {
        va_list tmp_args;
        va_copy(tmp_args, args);
        
        sinks[i].log_func(&event, format, tmp_args); 
        
        va_end(tmp_args);
    }

    va_end(args);
}

#define LOG_TRACE(format, ...) internal_log(__FILE__, __LINE__, format, LOG_TRACE, ##__VA_ARGS__)
#define LOG_DEBUG(format, ...) internal_log(__FILE__, __LINE__, format, LOG_DEBUG, ##__VA_ARGS__)
#define LOG_INFO(format, ...)  internal_log(__FILE__, __LINE__, format, LOG_INFO, ##__VA_ARGS__)
#define LOG_WARN(format, ...)  internal_log(__FILE__, __LINE__, format, LOG_WARN, ##__VA_ARGS__)
#define LOG_ERROR(format, ...) internal_log(__FILE__, __LINE__, format, LOG_ERROR, ##__VA_ARGS__)
#define LOG_FATAL(format, ...) internal_log(__FILE__, __LINE__, format, LOG_FATAL, ##__VA_ARGS__)