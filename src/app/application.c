#include <app/application.h>
#include <base/log.h>
#include <startup/startup_cmd.h>

static const char *error_type_name(StartupErrorType error_type) {
    switch (error_type) {
    case ERR_NONE:
        return "none";
    case ERR_MISSING_COMMAND:
        return "missing command";
    case ERR_UNKNOWN_COMMAND:
        return "unknown command";
    case ERR_MISSING_FILENAME:
        return "missing filename";
    case ERR_TOO_MANY_ARGUMENTS:
        return "too many arguments";
    }

    return "unknown parser error";
}

int app_run(int argc, char *argv[]) {
    StartupCmdParseResult result = parse_startup_command(argc, argv);

    if (result.error_type != ERR_NONE) {
        LOG_ERROR("%s", error_type_name(result.error_type));
        return 1;
    }

    return execute_startup_command(result);
}
