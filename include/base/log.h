/**
 * @file log.h
 * @brief Lightweight log output macros and implementation.
 *
 * Development logs include level, source file, and line number. User-facing
 * logs keep output concise and omit source paths.
 */
#ifndef TEXTEDITOR_BASE_LOG_H
#define TEXTEDITOR_BASE_LOG_H

#include <stdarg.h>
#include <stdio.h>

typedef enum TextEditorLogLevel {
    TEXTEDITOR_LOG_LEVEL_DEBUG,
    TEXTEDITOR_LOG_LEVEL_INFO,
    TEXTEDITOR_LOG_LEVEL_WARN,
    TEXTEDITOR_LOG_LEVEL_ERROR
} TextEditorLogLevel;

static inline const char *texteditor_log_level_name(TextEditorLogLevel level) {
    switch (level) {
    case TEXTEDITOR_LOG_LEVEL_DEBUG:
        return "DEBUG";
    case TEXTEDITOR_LOG_LEVEL_INFO:
        return "INFO";
    case TEXTEDITOR_LOG_LEVEL_WARN:
        return "WARN";
    case TEXTEDITOR_LOG_LEVEL_ERROR:
        return "ERROR";
    }

    return "UNKNOWN";
}

static inline const char *texteditor_log_user_prefix(TextEditorLogLevel level) {
    switch (level) {
    case TEXTEDITOR_LOG_LEVEL_DEBUG:
        return "td: debug: ";
    case TEXTEDITOR_LOG_LEVEL_INFO:
        return "td: info: ";
    case TEXTEDITOR_LOG_LEVEL_WARN:
        return "td: warning: ";
    case TEXTEDITOR_LOG_LEVEL_ERROR:
        return "td: ";
    }

    return "td: ";
}

/**
 * @brief Internal log implementation function (single line to `stderr`).
 * @param level Log level string.
 * @param file Caller's file name.
 * @param line Caller's line number.
 * @param fmt `printf`-style format string.
 * @param ... Variable arguments matching `fmt`.
 * @return No return value.
 * @note Callers must ensure the format string matches the argument types.
 */
static inline void texteditor_log_write_development(TextEditorLogLevel level, const char *file,
                                                    int line, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    fprintf(stderr, "[%s] [%s:%d] ", texteditor_log_level_name(level), file, line);
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");
    va_end(args);
}

static inline void texteditor_log_write_user(TextEditorLogLevel level, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    fprintf(stderr, "%s", texteditor_log_user_prefix(level));
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");
    va_end(args);
}

#if defined(TEXTEDITOR_DEVELOPMENT_LOGS)
#define TEXTEDITOR_LOG_WRITE(level, fmt, ...)                                                      \
    texteditor_log_write_development(level, __FILE__, __LINE__, fmt, __VA_ARGS__)
#else
#define TEXTEDITOR_LOG_WRITE(level, fmt, ...) texteditor_log_write_user(level, fmt, __VA_ARGS__)
#endif

/** @def LOG_DEBUG
 * @brief Debug log macro (enabled only when `TEXTEDITOR_DEVELOPMENT_LOGS` is set).
 */
#if defined(TEXTEDITOR_DEVELOPMENT_LOGS)
#define LOG_DEBUG(fmt, ...) TEXTEDITOR_LOG_WRITE(TEXTEDITOR_LOG_LEVEL_DEBUG, fmt, __VA_ARGS__)
#else
#define LOG_DEBUG(fmt, ...) ((void)0)
#endif

/** @def LOG_INFO
 * @brief Info log macro.
 */
/** @def LOG_WARN
 * @brief Warning log macro.
 */
/** @def LOG_ERROR
 * @brief Error log macro.
 */
#define LOG_INFO(fmt, ...) TEXTEDITOR_LOG_WRITE(TEXTEDITOR_LOG_LEVEL_INFO, fmt, __VA_ARGS__)
#define LOG_WARN(fmt, ...) TEXTEDITOR_LOG_WRITE(TEXTEDITOR_LOG_LEVEL_WARN, fmt, __VA_ARGS__)
#define LOG_ERROR(fmt, ...) TEXTEDITOR_LOG_WRITE(TEXTEDITOR_LOG_LEVEL_ERROR, fmt, __VA_ARGS__)

#endif /* TEXTEDITOR_BASE_LOG_H */
