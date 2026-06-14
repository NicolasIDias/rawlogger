#include <rawlogger/logger.h>
#include <time.h>
#include <pthread.h>

/* Registered sinks are stored here. Each sink receives all log events. */
static rawlog_sink_t sinks[RAWLOG_MAX_SINKS];
static int sink_counter = 0;

static rawlog_level_t current_base_level = RAWLOG_LEVEL_TRACE;
static pthread_mutex_t logger_mutex = PTHREAD_MUTEX_INITIALIZER;

/* Register a new sink destination. */
void rawlog_add_sink(rawlog_sink_t sink)
{
    pthread_mutex_lock(&logger_mutex);
    if (sink_counter < RAWLOG_MAX_SINKS)
    {
        sinks[sink_counter++] = sink;
    }
    pthread_mutex_unlock(&logger_mutex);
}

void rawlog_set_level(rawlog_level_t level)
{
    pthread_mutex_lock(&logger_mutex);
    current_base_level = level;
    pthread_mutex_unlock(&logger_mutex);
}

void rawlog_shutdown(void)
{
    pthread_mutex_lock(&logger_mutex);
    for (int i = 0; i < sink_counter; i++)
    {
        if (sinks[i].free_func)
        {
            sinks[i].free_func(sinks[i].user_data);
        }
    }
    sink_counter = 0;
    pthread_mutex_unlock(&logger_mutex);
}

/*
 * Main logger function.
 * It builds a log event and forwards the formatted message to every sink.
 */
void rawlog_internal(const char *file, int line, rawlog_level_t level, const char *format, ...)
{
    pthread_mutex_lock(&logger_mutex);

    if (level < current_base_level)
    {
        pthread_mutex_unlock(&logger_mutex);
        return;
    }

    time_t t = time(NULL);
    struct tm time_info;
    localtime_r(&t, &time_info);

    rawlog_event_t event = {level, file, line, &time_info};

    va_list args;
    va_start(args, format);

    for (int i = 0; i < sink_counter; i++)
    {
        if (sinks[i].log_func)
        {
            va_list tmp_args;
            va_copy(tmp_args, args);
            sinks[i].log_func(&event, sinks[i].user_data, format, tmp_args);
            va_end(tmp_args);
        }
    }

    va_end(args);
    pthread_mutex_unlock(&logger_mutex);
}
