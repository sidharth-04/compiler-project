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

#define LOG_MESSAGE(LEVEL, HEADER, ...) log_message(LEVEL, HEADER, __VA_ARGS__)

void log_error_header(const char *format, ...) {
	LOG_MESSAGE(LOG_ERROR, 1, format);
}
void log_error(const char *format, ...) {
	LOG_MESSAGE(LOG_ERROR, 0, format);
}
void log_info_header(const char *format, ...) {
	LOG_MESSAGE(LOG_INFO, 1, format);
}
void log_info(const char *format, ...) {
	LOG_MESSAGE(LOG_INFO, 0, format);
}
void log_success_header(const char *format, ...) {
	LOG_MESSAGE(LOG_SUCCESS, 1, format);
}
void log_success(const char *format, ...) {
	LOG_MESSAGE(LOG_SUCCESS, 0, format);
}

// Add indentation in tabs
void indent_by(int amount) {
	for (int i = 0; i < amount; i ++) printf("\t");
}
