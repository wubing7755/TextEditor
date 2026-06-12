#ifndef TEXTEDITOR_STARTUP_CMD_H
#define TEXTEDITOR_STARTUP_CMD_H

#include <base/export.h>

/* Startup command type. */
typedef enum { CMD_NONE, CMD_HELP, CMD_NEW_FILE, CMD_OPEN_FILE } StartupCmdType;

/* Startup command parse error type. */
typedef enum {
    ERR_NONE,
    ERR_MISSING_COMMAND,
    ERR_UNKNOWN_COMMAND,
    ERR_MISSING_FILENAME,
    ERR_TOO_MANY_ARGUMENTS
} StartupErrorType;

/* Parsed startup command. */
typedef struct StartupCmdParseResult {
    StartupErrorType error_type;
    StartupCmdType cmd_type;
    const char *filename;
} StartupCmdParseResult;

/* Parses argv[1..]; argv[0] is the program path/name supplied by the runtime. */
TEXTEDITOR_API StartupCmdParseResult parse_startup_command(int argc, char *argv[]);

TEXTEDITOR_API int execute_startup_command(StartupCmdParseResult result);

#endif /* TEXTEDITOR_STARTUP_CMD_H */
