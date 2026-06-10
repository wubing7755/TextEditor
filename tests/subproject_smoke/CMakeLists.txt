cmake_minimum_required(VERSION 3.21)

project(TextEditorSubprojectSmoke LANGUAGES C)

if(NOT DEFINED TEXTEDITOR_SOURCE_DIR)
    message(FATAL_ERROR "TEXTEDITOR_SOURCE_DIR must point at the template source tree")
endif()

add_subdirectory("${TEXTEDITOR_SOURCE_DIR}" "${CMAKE_CURRENT_BINARY_DIR}/texteditor-standard")

if(NOT TARGET TextEditor::texteditor_core)
    message(FATAL_ERROR "Expected TextEditor::texteditor_core alias target")
endif()

foreach(option_name IN ITEMS
        TEXTEDITOR_BUILD_EXAMPLE
        TEXTEDITOR_BUILD_TESTING
        TEXTEDITOR_INSTALL)
    if(${option_name})
        message(FATAL_ERROR "${option_name} should default to OFF for subproject builds")
    endif()
endforeach()

foreach(target_name IN ITEMS
        texteditor_example
        texteditor_example_tests
        texteditor_tests)
    if(TARGET ${target_name})
        message(FATAL_ERROR "${target_name} should not be created by default for subproject builds")
    endif()
endforeach()

add_executable(subproject_smoke main.c)
target_link_libraries(subproject_smoke PRIVATE TextEditor::texteditor_core)

enable_testing()
add_test(NAME subproject_smoke COMMAND subproject_smoke)
