#include <rawlogger/sink.h>
#include <stdio.h>
#include <stdarg.h>

const char *level_to_string(log_level lvl)
{
    switch (lvl)
    {
    case LOG_TRACE:
        return "TRACE";

    case LOG_INFO:
        return "INFO";

    case LOG_WARN:
        return "WARN";

    case LOG_DEBUG:
        return "DEBUG";

    case LOG_ERROR:
        return "ERROR";

    case LOG_FATAL:
        return "FATAL";

    default:
        return "UNKNOWN";
    }
}

void console_sink_func(log_t *event, const char* format, va_list args)
{
    char buffer[1024];

    vsnprintf(buffer, 1024, format, args);
    printf("[%s] %s\n", level_to_string(event->level), buffer);
}

log_sink_t console_sink_create(void)
{
    return (log_sink_t){ .log_func = console_sink_func };
}