#include <example/example.h>

int main(void) {
    TextEditorVersion version = texteditor_version();
    int value = 0;

    if (version.major < 0 || version.minor < 0 || version.patch < 0) {
        return 1;
    }

    if (!texteditor_add_checked(20, 22, &value) || value != 42) {
        return 1;
    }

    return 0;
}
