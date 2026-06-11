#ifndef TEXTEDITOR_COMMAND_PARSER_H
#define TEXTEDITOR_COMMAND_PARSER_H

#include <base/export.h>
#include <base/types.h>

/* Command Type */
typedef enum {
    CMD_NONE,
    CMD_HELP,
    CMD_NEW_FILE,
    CMD_OPEN_FILE
} CmdType;

/* Error Type */
typedef enum {
    ERR_NONE,
    ERR_MISSING_COMMAND,
    ERR_UNKNOWN_COMMAND,
    ERR_MISSING_FILENAME,
    ERR_TOO_MANY_ARGUMENTS
} ErrorType;

/* Command Parser */
typedef struct ParseResult {
    ErrorType error_type;
    CmdType cmd_type;
    string filename;
} ParseResult;

/* Parses argv[1..]; argv[0] is the program path/name supplied by the runtime. */
TEXTEDITOR_API ParseResult parse_command(int argc, char *argv[]);

#endif /* TEXTEDITOR_COMMAND_PARSER_H */
