#include <stdio.h>

#include <texteditor/application.h>
#include <texteditor/example.h>

int app_run(int argc, char *argv[]) {
    char *temp = "";

    for (int i = 1; i < argc; i++) {
        temp = argv[i];

        printf("%s\n", temp);
    }

    TextEditorVersion version = texteditor_version();
    printf("TextEditor example %d.%d.%d\n", version.major, version.minor, version.patch);
    return 0;
}
