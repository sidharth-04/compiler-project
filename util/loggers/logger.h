#ifndef logger_h
#define logger_h

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#define RESET_COLOR   "\033[0m"
#define RED_COLOR     "\033[31m"
#define GREEN_COLOR   "\033[32m"

typedef enum {
	LOG_ERROR,
	LOG_INFO
} LogLevel;

void log_message(LogLevel level, int include_prefix, const char *format, ...);
void log_error_header(const char *format, ...);
void log_error(const char *format, ...);
void log_info_header(const char *format, ...);
void log_info(const char *format, ...);
void indent_by(int amount);

#endif
