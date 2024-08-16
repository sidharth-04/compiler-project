#include "logger.h"

// Basic logging capabilities
void log_message(LogLevel level, int include_prefix, const char *format, ...) {
    va_list args;
    va_start(args, format);

    const char *color;
    const char *prefix;
    
    switch (level) {
        case LOG_ERROR:
            color = RED_COLOR;
            prefix = "ERROR: ";
            break;
        case LOG_INFO:
            color = BLUE_COLOR;
            prefix = "INFO: ";
            break;
		case LOG_SUCCESS:
			color = GREEN_COLOR;
            prefix = "SUCCESS: ";
            break;
        default:
            color = RESET_COLOR;
            prefix = "UNKNOWN: ";
            break;
    }

	if (!include_prefix) prefix = "";
    printf("%s%s", color, prefix);
    vprintf(format, args);
    printf("%s", RESET_COLOR);

    va_end(args);
}
