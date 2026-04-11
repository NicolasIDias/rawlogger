#include <rawlogger/logger.h>
#include <rawlogger/sink.h>

int main()
{
    /* Creates the console sink and logs it to the logger */
    log_add_sink(console_sink_create());
    log_add_sink(file_sink_create());

    /* Example of using logging macros. */
    LOG_INFO("Hello, %s!", "World");
    LOG_WARN("Value = %d", 42);
    LOG_ERROR("Fail %s", "sensor");
    LOG_FATAL("Fatal %s", "error");

    //for(int i=0;i<1000000000;i++);

    /* Cleaning the log sink file */
    clear_file_sink();

    return 0;
}