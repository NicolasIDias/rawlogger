#pragma once
#include <rawlogger/logger.h>

log_sink_t stdout_sink(void);

log_sink_t file_sink(const char *path);
