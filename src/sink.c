#include <rawlogger/sink.h>
#include <stdio.h>
#include <stdarg.h>

/* Convert a log level enum to a human-readable string. */
const char *level_to_string(log_level lvl)
{
    switch (lvl)
    {
    case LOG_TRACE:
        return "\033[1;34mTRACE\033[0m";  /* blue */

    case LOG_DEBUG:
        return "\033[1;36mDEBUG\033[0m";  /* cyan */

    case LOG_INFO:
        return "\033[1;32mINFO\033[0m";   /* green */

    case LOG_WARN:
        return "\033[1;33mWARN\033[0m";   /* yellow */

    case LOG_ERROR:
        return "\033[1;31mERROR\033[0m";  /* red */

    case LOG_FATAL:
        return "\033[1;41;97mFATAL\033[0m"; /* red background */

    default:
        return "UNKNOWN";
    }
}

/* Default console sink implementation. */
void console_sink_func(log_t *event, const char *format, va_list args)
{
    char buffer[1024];

    vsnprintf(buffer, sizeof(buffer), format, args);
    printf("[%s] %s\n", level_to_string(event->level), buffer);
}

/* Create a reusable console sink object. */
log_sink_t console_sink_create()
{
    return (log_sink_t){.log_func = console_sink_func};
}