#include <rawlogger/logger.h>

/* Registered sinks are stored here. Each sink receives all log events. */
static log_sink_t sinks[MAX_SINKS];
static int sink_counter = 0;

static log_level current_base_level = LOG_TRACE;

/* Register a new sink destination. */
void log_add_sink(log_sink_t sink)
{
    if (sink_counter < MAX_SINKS)
    {
        sinks[sink_counter++] = sink;
    }
}


void set_log_level(log_level level)
{
    current_base_level = level;
}

/*
 * Main logger function.
 * It builds a log event and forwards the formatted message to every sink.
 */
void internal_log(const char *file, int line, const char *format, log_level level, ...)
{
    if (level < current_base_level)
        return;

    log_t event = {level, file, line};

    va_list args;
    va_start(args, level);

    for (int i = 0; i < sink_counter; i++)
    {
        va_list tmp_args;
        va_copy(tmp_args, args);

        sinks[i].log_func(&event, format, tmp_args);

        va_end(tmp_args);
    }

    va_end(args);
}
