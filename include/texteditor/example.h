#ifndef TEXTEDITOR_EXAMPLE_H
#define TEXTEDITOR_EXAMPLE_H

#include <texteditor/compiler.h>
#include <texteditor/export.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct TextEditorVersion {
    int major;
    int minor;
    int patch;
} TextEditorVersion;

/* Returns the library version compiled into this build. */
TEXTEDITOR_API TextEditorVersion texteditor_version(void);

/*
 * Adds two integers and writes the result to out_value.
 * Returns 1 on success and 0 when out_value is NULL or the sum would overflow.
 */
TEXTEDITOR_API int texteditor_add_checked(int left, int right, int *out_value);

/* Returns a human-readable platform name for the current target. */
TEXTEDITOR_API const char *texteditor_platform_name(void);

#ifdef __cplusplus
}
#endif

#endif /* TEXTEDITOR_EXAMPLE_H */
