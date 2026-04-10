#include <rawlogger/logger.h>
#include <rawlogger/sink.h>

int main()
{
    /* Creates the console sink and logs it to the logger */
    log_sink_t console = console_sink_create();
    log_add_sink(console);

    /* Example of using logging macros. */
    LOG_INFO("Hello, %s!", "World");
    LOG_WARN("Value = %d", 42);
    LOG_ERROR("Fail %s", "sensor");
    LOG_FATAL("Fatal %s", "error");

    return 0;
}