#include <rawlogger/sinks.h>
#include <stdio.h>
#include <time.h>

static const char *level_strings[] = {
    "TRACE", "DEBUG", "INFO", "WARN", "ERROR", "FATAL"
};

static const char *level_colors[] = {
    "\033[0;90m",   
    "\033[0;36m",   
    "\033[0;32m",   
    "\033[1;33m",   
    "\033[0;31m",   
    "\033[1;31m"   
};

static const char *color_reset = "\033[0m";

static void stdout_log_func(log_t *event, const char *format, va_list args)
{
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    char time_buf[32];
    strftime(time_buf, sizeof(time_buf), "%Y-%m-%d %H:%M:%S", tm_info);
    
    fprintf(stdout, "%s%s [%s] %s:%d - ", 
            level_colors[event->level],
            time_buf,
            level_strings[event->level],
            event->filepath,
            event->line);
    
    vfprintf(stdout, format, args);
    fprintf(stdout, "%s\n", color_reset);
    fflush(stdout);
}

log_sink_t stdout_sink(void)
{
    return (log_sink_t){.log_func = stdout_log_func};
}

typedef struct {
    FILE *file;
} file_sink_data_t;

static void file_log_func(log_t *event, const char *format, va_list args)
{
    FILE *file = fopen("/tmp/rawlogger.log", "a");
    if (!file) return;
    
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    char time_buf[32];
    strftime(time_buf, sizeof(time_buf), "%Y-%m-%d %H:%M:%S", tm_info);
    
    fprintf(file, "%s [%s] %s:%d - ", 
            time_buf,
            level_strings[event->level],
            event->filepath,
            event->line);
    
    vfprintf(file, format, args);
    fprintf(file, "\n");
    fclose(file);
}

log_sink_t file_sink(const char *path)
{
    (void)path;
    return (log_sink_t){.log_func = file_log_func};
}
