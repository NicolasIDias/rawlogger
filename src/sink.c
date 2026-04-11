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

/* Convert a log level enum to a human-readable string. */
const char *level_to_string(log_level lvl)
{
    switch (lvl)
    {
    case LOG_TRACE:
        return BLUE "TRACE" RESET; /* blue */

    case LOG_DEBUG:
        return CYAN "DEBUG" RESET; /* cyan */

    case LOG_INFO:
        return GREEN "INFO" RESET; /* green */

    case LOG_WARN:
        return YELLOW "WARN" RESET; /* yellow */

    case LOG_ERROR:
        return RED "ERROR" RESET; /* red */

    case LOG_FATAL:
        return RED_B "FATAL" RESET; /* red background */

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

/* File sink implementation that writes logs to app.log. */
void file_sink_func(log_t *event, const char *format, va_list args)
{
    FILE *file = fopen("app.log", "a");

    if (file == NULL)
    {
        printf("Error: Could not open app.log\n");
        return;
    }

    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), format, args);

    fprintf(file, "[%s] %s\n", level_to_string(event->level), buffer);

    fclose(file);
}

/* Create a file sink that writes to app.log. */
log_sink_t file_sink_create()
{
    return (log_sink_t){.log_func = file_sink_func}; 
}

void clear_file_sink()
{
    FILE *file = fopen("app.log", "w");
    if(file == NULL)
    {
        printf("Error: Could not open app.log\n");
        return;
    }    
    fclose(file);
}