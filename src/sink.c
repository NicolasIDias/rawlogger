#include <rawlogger/sink.h>
#include <stdio.h>
#include <stdarg.h>

#define BLUE "\033[1;34m"
#define YELLOW "\033[1;33m"
#define RED "\033[1;31m"
#define RED_B "\033[1;41;97m"
#define GREEN "\033[1;32m"
#define CYAN "\033[1;36m"
#define RESET "\033[0m"

const char *rawlog_level_to_string(rawlog_level_t lvl)
{
    switch (lvl)
    {
    case RAWLOG_LEVEL_TRACE: return "TRACE";
    case RAWLOG_LEVEL_DEBUG: return "DEBUG";
    case RAWLOG_LEVEL_INFO:  return "INFO";
    case RAWLOG_LEVEL_WARN:  return "WARN";
    case RAWLOG_LEVEL_ERROR: return "ERROR";
    case RAWLOG_LEVEL_FATAL: return "FATAL";
    default:                 return "UNKNOWN";
    }
}

const char *rawlog_level_to_color(rawlog_level_t lvl)
{
    switch (lvl)
    {
    case RAWLOG_LEVEL_TRACE: return BLUE;
    case RAWLOG_LEVEL_DEBUG: return CYAN;
    case RAWLOG_LEVEL_INFO:  return GREEN;
    case RAWLOG_LEVEL_WARN:  return YELLOW;
    case RAWLOG_LEVEL_ERROR: return RED;
    case RAWLOG_LEVEL_FATAL: return RED_B;
    default:                 return RESET;
    }
}

/* Default console sink implementation. */
static void console_sink_func(const rawlog_event_t *event, void *user_data, const char *format, va_list args)
{
    char time_buf[64];
    if (event->time_info)
    {
        strftime(time_buf, sizeof(time_buf), "%Y-%m-%d %H:%M:%S", event->time_info);
    }
    else
    {
        time_buf[0] = '\0';
    }

    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), format, args);

    printf("[%s] [%s%s%s] %s:%d: %s\n", time_buf, rawlog_level_to_color(event->level), rawlog_level_to_string(event->level), RESET, event->filepath, event->line, buffer);
}

/* Create a reusable console sink object. */
rawlog_sink_t rawlog_console_sink_create(void)
{
    rawlog_sink_t sink = {0};
    sink.log_func = console_sink_func;
    return sink;
}

/* File sink implementation. */
static void file_sink_func(const rawlog_event_t *event, void *user_data, const char *format, va_list args)
{
    FILE *file = (FILE*)user_data;
    if (file == NULL)
        return;

    char time_buf[64];
    if (event->time_info)
    {
        strftime(time_buf, sizeof(time_buf), "%Y-%m-%d %H:%M:%S", event->time_info);
    }
    else
    {
        time_buf[0] = '\0';
    }

    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), format, args);

    fprintf(file, "[%s] [%s] %s:%d: %s\n", time_buf, rawlog_level_to_string(event->level), event->filepath, event->line, buffer);
    fflush(file);
}

static void file_sink_free(void *user_data)
{
    FILE *file = (FILE*)user_data;
    if (file)
    {
        fclose(file);
    }
}

/* Create a file sink. */
rawlog_sink_t rawlog_file_sink_create(const char *filepath)
{
    rawlog_sink_t sink = {0};
    FILE *file = fopen(filepath, "a");
    if (file)
    {
        sink.user_data = file;
        sink.log_func = file_sink_func;
        sink.free_func = file_sink_free;
    }
    else
    {
        fprintf(stderr, "Error: Could not open %s\n", filepath);
    }
    return sink;
}
