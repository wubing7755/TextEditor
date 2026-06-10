#include <texteditor/example.h>
#include <texteditor/version.h>

#include <limits.h>

TextEditorVersion texteditor_version(void) {
    TextEditorVersion version = {
        TEXTEDITOR_VERSION_MAJOR,
        TEXTEDITOR_VERSION_MINOR,
        TEXTEDITOR_VERSION_PATCH,
    };
    return version;
}

int texteditor_add_checked(int left, int right, int *out_value) {
    if (!out_value) {
        return 0;
    }

    if ((right > 0 && left > INT_MAX - right) || (right < 0 && left < INT_MIN - right)) {
        return 0;
    }

    *out_value = left + right;
    return 1;
}

const char *texteditor_platform_name(void) {
#if TEXTEDITOR_PLATFORM_WINDOWS
    return "windows";
#elif TEXTEDITOR_PLATFORM_MACOS
    return "macos";
#elif TEXTEDITOR_PLATFORM_LINUX
    return "linux";
#else
    return "unknown";
#endif
}
