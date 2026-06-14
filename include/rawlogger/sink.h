#pragma once
#include <rawlogger/logger.h>

/* Convert a log level enum value into a human-readable string. */
const char *rawlog_level_to_string(rawlog_level_t lvl);
const char *rawlog_level_to_color(rawlog_level_t lvl);

/* Create a console sink that can be registered with rawlog_add_sink(). */
rawlog_sink_t rawlog_console_sink_create(void);

/* Create a file sink that can be registered with rawlog_add_sink(). */
rawlog_sink_t rawlog_file_sink_create(const char *filepath);
