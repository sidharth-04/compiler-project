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
            color = GREEN_COLOR;
            prefix = "INFO: ";
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


// Utility to print a log error header
void log_error_header(const char *format, ...) {
	va_list args;
    va_start(args, format);
	log_message(LOG_ERROR, 1, format, args);
	va_end(args);
}

// Utility to print a log error
void log_error(const char *format, ...) {
	va_list args;
    va_start(args, format);
	log_message(LOG_ERROR, 0, format, args);
	va_end(args);
}

// Utility to print a log info header
void log_info_header(const char *format, ...) {
	va_list args;
    va_start(args, format);
	log_message(LOG_INFO, 1, format, args);
	va_end(args);
}

// Utility to print log info
void log_info(const char *format, ...) {
	va_list args;
    va_start(args, format);
	log_message(LOG_INFO, 0, format, args);
	va_end(args);
}

// Add indentation in tabs
void indent_by(int amount) {
	for (int i = 0; i < amount; i ++) printf("\t");
}

int main() {
    log_message(LOG_INFO, 1, "This is an info message.\n");
    log_message(LOG_ERROR, 1, "This is an error message.\n");
	char *error = "Oh no an error!!!";
    log_message(LOG_ERROR, 0, "This is an error message with the following error: %s\n", error);
    log_message(19, 1, "This is an unknown message with the following error: %s\n", error);
    return 0;
}
