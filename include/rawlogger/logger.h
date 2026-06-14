#pragma once
#include <stdio.h>
#include <stdarg.h>
#include <time.h>

/* Minimal boolean definitions for compatibility with older C standards. */
#define bool _Bool
#define true 1
#define false 0

/* Maximum number of sinks that can be registered at runtime. */
#define RAWLOG_MAX_SINKS 16

/* Log levels supported by the library. */
typedef enum
{
    RAWLOG_LEVEL_TRACE,
    RAWLOG_LEVEL_DEBUG,
    RAWLOG_LEVEL_INFO,
    RAWLOG_LEVEL_WARN,
    RAWLOG_LEVEL_ERROR,
    RAWLOG_LEVEL_FATAL
} rawlog_level_t;

/* Metadata for a single log event. */
typedef struct
{
    rawlog_level_t level; /* Log severity level */
    const char *filepath; /* Source file where the log was generated */
    int line;             /* Source line where the log was generated */
    struct tm *time_info; /* Timestamp */
} rawlog_event_t;

/* A sink is a destination for log messages. */
typedef struct
{
    void *user_data;
    void (*log_func)(const rawlog_event_t *event, void *user_data, const char *format, va_list args);
    void (*free_func)(void *user_data);
} rawlog_sink_t;

/* Register a sink so it receives all future log events. */
void rawlog_add_sink(rawlog_sink_t sink);

/* Set the minimum log level to filter out lower severity logs. */
void rawlog_set_level(rawlog_level_t level);

/* Clean up registered sinks. Call on application exit. */
void rawlog_shutdown(void);

/* Core logging function. */
void rawlog_internal(const char *file, int line, rawlog_level_t level, const char *format, ...);

/* Convenience macros that capture source file and line number. */
#define RAWLOG_TRACE(format, ...) rawlog_internal(__FILE__, __LINE__, RAWLOG_LEVEL_TRACE, format, ##__VA_ARGS__)
#define RAWLOG_DEBUG(format, ...) rawlog_internal(__FILE__, __LINE__, RAWLOG_LEVEL_DEBUG, format, ##__VA_ARGS__)
#define RAWLOG_INFO(format, ...)  rawlog_internal(__FILE__, __LINE__, RAWLOG_LEVEL_INFO, format, ##__VA_ARGS__)
#define RAWLOG_WARN(format, ...)  rawlog_internal(__FILE__, __LINE__, RAWLOG_LEVEL_WARN, format, ##__VA_ARGS__)
#define RAWLOG_ERROR(format, ...) rawlog_internal(__FILE__, __LINE__, RAWLOG_LEVEL_ERROR, format, ##__VA_ARGS__)
#define RAWLOG_FATAL(format, ...) rawlog_internal(__FILE__, __LINE__, RAWLOG_LEVEL_FATAL, format, ##__VA_ARGS__)
