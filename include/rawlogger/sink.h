#pragma once
#include <rawlogger/logger.h>

const char *level_to_string(log_level lvl);
void console_sink_func(log_t *event, const char *format, va_list args);
log_sink_t console_sink_create(void);
