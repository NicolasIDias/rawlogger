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

void log_add_sink(log_sink_t sink);
void internal_log(const char *file, int line, const char *format, log_level level, ...);

#define LOG_TRACE(format, ...) internal_log(__FILE__, __LINE__, format, LOG_TRACE, ##__VA_ARGS__)
#define LOG_DEBUG(format, ...) internal_log(__FILE__, __LINE__, format, LOG_DEBUG, ##__VA_ARGS__)
#define LOG_INFO(format, ...)  internal_log(__FILE__, __LINE__, format, LOG_INFO, ##__VA_ARGS__)
#define LOG_WARN(format, ...)  internal_log(__FILE__, __LINE__, format, LOG_WARN, ##__VA_ARGS__)
#define LOG_ERROR(format, ...) internal_log(__FILE__, __LINE__, format, LOG_ERROR, ##__VA_ARGS__)
#define LOG_FATAL(format, ...) internal_log(__FILE__, __LINE__, format, LOG_FATAL, ##__VA_ARGS__)