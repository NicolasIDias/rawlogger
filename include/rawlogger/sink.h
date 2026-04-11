#pragma once
#include <rawlogger/logger.h>

/* Convert a log level enum value into a human-readable string. */
const char *level_to_string(log_level lvl);

/* Create a console and file sink that can be registered with log_add_sink(). */
log_sink_t console_sink_create();
log_sink_t file_sink_create();

/* Erase the log file */
void clear_log_file();
