#pragma once
#include <rawlogger/logger.h>

/* Convert a log level enum value into a human-readable string. */
const char *level_to_string(log_level lvl);

/* Default console sink implementation.
 * It formats the message and writes it to stdout. */
void console_sink_func(log_t *event, const char *format, va_list args);
void file_sink_func(log_t *event, const char *format, va_list args);

/* Create a console and file sink that can be registered with log_add_sink(). */
log_sink_t console_sink_create();
log_sink_t file_sink_create();

void clear_file_sink();
