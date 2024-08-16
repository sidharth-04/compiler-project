#ifndef logger_h
#define logger_h

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#define RESET_COLOR   "\033[0m"
#define RED_COLOR     "\033[31m"
#define GREEN_COLOR   "\033[32m"
#define BLUE_COLOR	  "\033[34m"

typedef enum {
	LOG_ERROR,
	LOG_INFO,
	LOG_SUCCESS
} LogLevel;


// Define macro for logging messages
#define LOG_MESSAGE(LEVEL, HEADER, ...) log_message(LEVEL, HEADER, __VA_ARGS__)

// Macros for logging error messages with header and without header
#define LOG_ERROR_HEADER(format, ...) LOG_MESSAGE(LOG_ERROR, 1, format, ##__VA_ARGS__)
#define LOG_ERROR(format, ...) LOG_MESSAGE(LOG_ERROR, 0, format, ##__VA_ARGS__)

// Macros for logging info messages with header and without header
#define LOG_INFO_HEADER(format, ...) LOG_MESSAGE(LOG_INFO, 1, format, ##__VA_ARGS__)
#define LOG_INFO(format, ...) LOG_MESSAGE(LOG_INFO, 0, format, ##__VA_ARGS__)

// Macros for logging success messages with header and without header
#define LOG_SUCCESS_HEADER(format, ...) LOG_MESSAGE(LOG_SUCCESS, 1, format, ##__VA_ARGS__)
#define LOG_SUCCESS(format, ...) LOG_MESSAGE(LOG_SUCCESS, 0, format, ##__VA_ARGS__)


void log_message(LogLevel level, int include_prefix, const char *format, ...);

#endif
