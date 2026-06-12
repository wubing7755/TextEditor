#include <example/example.h>
#include <startup/startup_cmd.h>
#include <utils/version.h>

#include "test_assert.h"

#include <limits.h>
#include <stdio.h>
#include <string.h>

static int test_version(void) {
    TextEditorVersion version = texteditor_version();
    if (!TEXTEDITOR_EXPECT_INT_EQ(version.major, TEXTEDITOR_VERSION_MAJOR)) {
        return 1;
    }
    if (!TEXTEDITOR_EXPECT_INT_EQ(version.minor, TEXTEDITOR_VERSION_MINOR)) {
        return 1;
    }
    if (!TEXTEDITOR_EXPECT_INT_EQ(version.patch, TEXTEDITOR_VERSION_PATCH)) {
        return 1;
    }
    return 0;
}

static int test_checked_add(void) {
    int value = 0;

    if (!TEXTEDITOR_EXPECT_TRUE(texteditor_add_checked(2, 3, &value))) {
        return 1;
    }
    if (!TEXTEDITOR_EXPECT_INT_EQ(value, 5)) {
        return 1;
    }
    if (!TEXTEDITOR_EXPECT_TRUE(!texteditor_add_checked(INT_MAX, 1, &value))) {
        return 1;
    }
    if (!TEXTEDITOR_EXPECT_TRUE(!texteditor_add_checked(INT_MIN, -1, &value))) {
        return 1;
    }
    if (!TEXTEDITOR_EXPECT_TRUE(!texteditor_add_checked(1, 1, NULL))) {
        return 1;
    }
    return 0;
}

static int expect_parse_result(int argc, char *argv[], StartupCmdType cmd_type,
                               StartupErrorType error_type, const char *filename) {
    StartupCmdParseResult result = parse_startup_command(argc, argv);

    if (!TEXTEDITOR_EXPECT_INT_EQ((int)result.cmd_type, (int)cmd_type)) {
        return 0;
    }
    if (!TEXTEDITOR_EXPECT_INT_EQ((int)result.error_type, (int)error_type)) {
        return 0;
    }

    if (filename == NULL) {
        return TEXTEDITOR_EXPECT_TRUE(result.filename == NULL);
    }

    if (!TEXTEDITOR_EXPECT_TRUE(result.filename != NULL)) {
        return 0;
    }

    return TEXTEDITOR_EXPECT_TRUE(strcmp(result.filename, filename) == 0);
}

static int test_parse_command(void) {
    char program_path[] = "td.exe";
    char *help_short[] = {program_path, "-h"};
    char *help_long[] = {program_path, "-help"};
    char *new_short[] = {program_path, "-n", "a.txt"};
    char *new_long[] = {program_path, "-new", "a.txt"};
    char *open_short[] = {program_path, "-o", "a.txt"};
    char *open_long[] = {program_path, "-open", "a.txt"};
    char *missing_command[] = {program_path};
    char *unknown_help[] = {program_path, "--help"};
    char *unknown_short[] = {program_path, "-x"};
    char *new_missing_filename[] = {program_path, "-n"};
    char *open_missing_filename[] = {program_path, "-o"};
    char *new_too_many_arguments[] = {program_path, "-n", "a.txt", "b.txt"};

    if (!expect_parse_result(2, help_short, CMD_HELP, ERR_NONE, NULL)) {
        return 1;
    }
    if (!expect_parse_result(2, help_long, CMD_HELP, ERR_NONE, NULL)) {
        return 1;
    }
    if (!expect_parse_result(3, new_short, CMD_NEW_FILE, ERR_NONE, "a.txt")) {
        return 1;
    }
    if (!expect_parse_result(3, new_long, CMD_NEW_FILE, ERR_NONE, "a.txt")) {
        return 1;
    }
    if (!expect_parse_result(3, open_short, CMD_OPEN_FILE, ERR_NONE, "a.txt")) {
        return 1;
    }
    if (!expect_parse_result(3, open_long, CMD_OPEN_FILE, ERR_NONE, "a.txt")) {
        return 1;
    }
    if (!expect_parse_result(1, missing_command, CMD_NONE, ERR_MISSING_COMMAND, NULL)) {
        return 1;
    }
    if (!expect_parse_result(2, unknown_help, CMD_NONE, ERR_UNKNOWN_COMMAND, NULL)) {
        return 1;
    }
    if (!expect_parse_result(2, unknown_short, CMD_NONE, ERR_UNKNOWN_COMMAND, NULL)) {
        return 1;
    }
    if (!expect_parse_result(2, new_missing_filename, CMD_NONE, ERR_MISSING_FILENAME, NULL)) {
        return 1;
    }
    if (!expect_parse_result(2, open_missing_filename, CMD_NONE, ERR_MISSING_FILENAME, NULL)) {
        return 1;
    }
    if (!expect_parse_result(4, new_too_many_arguments, CMD_NONE, ERR_TOO_MANY_ARGUMENTS, NULL)) {
        return 1;
    }

    return 0;
}

int main(void) {
    if (test_version()) {
        return 1;
    }
    if (test_checked_add()) {
        return 1;
    }
    if (test_parse_command()) {
        return 1;
    }

    printf("[PASS] example tests\n");
    return 0;
}
