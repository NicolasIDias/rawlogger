#include <rawlogger/logger.h>
#include <rawlogger/sink.h>

int main()
{
    /* Creates the console sink and file sink */
    rawlog_add_sink(rawlog_console_sink_create());
    rawlog_add_sink(rawlog_file_sink_create("app.log"));

    /* Example of using logging macros. */
    RAWLOG_INFO("Hello, %s!", "World");
    RAWLOG_WARN("Value = %d", 42);
    RAWLOG_ERROR("Fail %s", "sensor");
    RAWLOG_FATAL("Fatal %s", "error");

    /* Shutdown to flush and close file descriptors */
    rawlog_shutdown();

    return 0;
}
