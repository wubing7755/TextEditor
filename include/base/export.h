#ifndef TEXTEDITOR_EXPORT_H
#define TEXTEDITOR_EXPORT_H

#if defined(_WIN32) && defined(TEXTEDITOR_SHARED)
#if defined(TEXTEDITOR_BUILDING_LIBRARY)
#define TEXTEDITOR_API __declspec(dllexport)
#else
#define TEXTEDITOR_API __declspec(dllimport)
#endif
#else
#define TEXTEDITOR_API
#endif

#endif /* TEXTEDITOR_EXPORT_H */
