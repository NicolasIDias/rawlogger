#pragma once
#include <stdio.h>
#include <stdarg.h>

/* Minimal boolean definitions for compatibility with older C standards. */
#define bool _Bool
#define true 1
#define false 0

/* Maximum number of sinks that can be registered at runtime. */
#define MAX_SINKS 8 // Value for test

/* Log levels supported by the library. */
typedef enum
{
    LOG_TRACE,
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR,
    LOG_FATAL
} log_level;

/* Metadata for a single log event. */
typedef struct
{
    log_level level;      /* Log severity level */
    const char *filepath; /* Source file where the log was generated */
    int line;             /* Source line where the log was generated */
} log_t;

/* A sink is a destination for log messages. */
typedef struct
{
    void (*log_func)(log_t *event, const char *format, va_list args);
} log_sink_t;

/* Register a sink so it receives all future log events. */
void log_add_sink(log_sink_t sink);

/*
 * Core logging function.
 * It receives file/line metadata, a format string, and variadic arguments.
 * This function forwards the formatted message to each registered sink.
 */
/* Convenience macros that capture source file and line number. */

void set_log_level(log_level level);
void internal_log(const char *file, int line, const char *format, log_level level, ...);

#define LOG_TRACE(format, ...) internal_log(__FILE__, __LINE__, format, LOG_TRACE, ##__VA_ARGS__)
#define LOG_DEBUG(format, ...) internal_log(__FILE__, __LINE__, format, LOG_DEBUG, ##__VA_ARGS__)
#define LOG_INFO(format, ...) internal_log(__FILE__, __LINE__, format, LOG_INFO, ##__VA_ARGS__)
#define LOG_WARN(format, ...) internal_log(__FILE__, __LINE__, format, LOG_WARN, ##__VA_ARGS__)
#define LOG_ERROR(format, ...) internal_log(__FILE__, __LINE__, format, LOG_ERROR, ##__VA_ARGS__)
#define LOG_FATAL(format, ...) internal_log(__FILE__, __LINE__, format, LOG_FATAL, ##__VA_ARGS__)