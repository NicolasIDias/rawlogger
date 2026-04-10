#include <rawlogger/logger.h>
#include <rawlogger/sink.h>

int main()
{
    log_sink_t console = console_sink_create();

    log_add_sink(console);

    LOG_INFO("Hello, %s!", "World");
    LOG_WARN("Value = %d", 42);
    LOG_ERROR("Fail %s", "sensor");

    return 0;
}