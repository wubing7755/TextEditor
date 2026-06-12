#include <base/log.h>
#include <startup/startup_cmd.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

static int create_file_in_current_dir(const char *filename) {
    FILE *file = NULL;

#if defined(_MSC_VER)
    if (fopen_s(&file, filename, "w") != 0) {
        return 1;
    }
#else
    file = fopen(filename, "w");
    if (file == NULL) {
        return 1;
    }
#endif

    if (file == NULL) {
        return 1;
    }

    return fclose(file) == 0 ? 0 : 1;
}

static bool is_new_file_cmd(StartupCmdType command) {
    return command == CMD_NEW_FILE;
}

static bool is_open_file_cmd(StartupCmdType command) {
    return command == CMD_OPEN_FILE;
}

static bool is_help_cmd(StartupCmdType command) {
    return command == CMD_HELP;
}

static void print_help(void) {
    printf("Usage:\n");
    printf("  td -h | -help\n");
    printf("  td -n | -new <file>\n");
    printf("  td -o | -open <file>\n");
}

/*
Input	            CommandType	    ErrorType	        FileName
td -h	            Help	        None	            None
td -help	        Help	        None	            None
td -n a.txt	        NewFile	        None	            a.txt
td -new a.txt	    NewFile         None	            a.txt
td -o a.txt	        OpenFile	    None	            a.txt
td -open a.txt	    OpenFile	    None	            a.txt
td	                None	        MissingCommand	    None
td --help	        None	        UnknownCommand	    None
td -x	            None	        UnknownCommand	    None
td -n	            None	        MissingFileName	    None
td -o	            None	        MissingFileName	    None
td -n a.txt b.txt	None	        TooManyArguments	None
*/
static int is_help_command(const char *command) {
    return strcmp(command, "-h") == 0 || strcmp(command, "-help") == 0;
}

static int is_new_file_command(const char *command) {
    return strcmp(command, "-n") == 0 || strcmp(command, "-new") == 0;
}

static int is_open_file_command(const char *command) {
    return strcmp(command, "-o") == 0 || strcmp(command, "-open") == 0;
}

static StartupCmdParseResult make_result(StartupErrorType error_type, StartupCmdType cmd_type,
                                         const char *filename) {
    StartupCmdParseResult result = {
        error_type,
        cmd_type,
        filename,
    };
    return result;
}

StartupCmdParseResult parse_startup_command(int argc, char *argv[]) {
    const char *command = NULL;
    StartupCmdType file_command = CMD_NONE;

    /* argv[0] is the executable path/name, for example td.exe on Windows. */
    if (argc < 2 || argv == NULL || argv[1] == NULL) {
        return make_result(ERR_MISSING_COMMAND, CMD_NONE, NULL);
    }

    command = argv[1];

    if (is_help_command(command)) {
        if (argc > 2) {
            return make_result(ERR_TOO_MANY_ARGUMENTS, CMD_NONE, NULL);
        }
        return make_result(ERR_NONE, CMD_HELP, NULL);
    }

    if (is_new_file_command(command)) {
        file_command = CMD_NEW_FILE;
    } else if (is_open_file_command(command)) {
        file_command = CMD_OPEN_FILE;
    } else {
        return make_result(ERR_UNKNOWN_COMMAND, CMD_NONE, NULL);
    }

    if (argc < 3 || argv[2] == NULL) {
        return make_result(ERR_MISSING_FILENAME, CMD_NONE, NULL);
    }

    if (argc > 3) {
        return make_result(ERR_TOO_MANY_ARGUMENTS, CMD_NONE, NULL);
    }

    return make_result(ERR_NONE, file_command, argv[2]);
}

int execute_startup_command(StartupCmdParseResult result) {
    if (is_open_file_cmd(result.cmd_type)) {

    } else if (is_new_file_cmd(result.cmd_type)) {
        return create_file_in_current_dir(result.filename);
    } else if (is_help_cmd(result.cmd_type)) {
        print_help();
    }

    return 0;
}
