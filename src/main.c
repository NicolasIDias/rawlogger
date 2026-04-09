#include <rawlogger/logger.h>
#include <rawlogger/sink.h>

int main(void)
{
    log_sink_t console_sink = console_sink_create();
    log_add_sink(console_sink);

    LOG_INFO("Hello from raw logger!");

    return 0;
}
