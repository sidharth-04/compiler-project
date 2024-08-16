#include "logger.h"

void log_message(LogLevel level, const char *format, ...) {
    va_list args;
    va_start(args, format);

    // Choose color based on log level
    const char *color;
    const char *prefix;
    
    switch (level) {
        case LOG_ERROR:
            color = RED_COLOR;
            prefix = "ERROR: ";
            break;
        case LOG_INFO:
            color = GREEN_COLOR;
            prefix = "INFO: ";
            break;
        default:
            color = RESET_COLOR;
            prefix = "UNKNOWN: ";
            break;
    }

    // Print log message with color
    printf("%s%s", color, prefix);
    vprintf(format, args);
    printf("%s", RESET_COLOR);

    va_end(args);
}

int main() {
    log_message(LOG_INFO, "This is an info message.\n");
    log_message(LOG_ERROR, "This is an error message.\n");
	char *error = "Oh no an error!!!";
    log_message(LOG_ERROR, "This is an error message with the following error: %s.\n", error);
    return 0;
}
