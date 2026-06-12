function(texteditor_add_test target)
    cmake_parse_arguments(TEXTEDITOR_TEST
        ""
        ""
        "SOURCES;LIBS"
        ${ARGN}
    )

    if(NOT TEXTEDITOR_TEST_SOURCES)
        message(FATAL_ERROR "texteditor_add_test(${target}) requires SOURCES")
    endif()

    add_executable(${target}
        ${TEXTEDITOR_TEST_SOURCES}
    )

    target_include_directories(${target}
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/include
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/support
    )

    if(TEXTEDITOR_TEST_LIBS)
        target_link_libraries(${target} PRIVATE ${TEXTEDITOR_TEST_LIBS})
    endif()

    texteditor_target_defaults(${target})

    set_target_properties(${target} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    )

    add_test(NAME ${target} COMMAND $<TARGET_FILE:${target}>)
    list(APPEND TEXTEDITOR_TEST_TARGETS ${target})
    set(TEXTEDITOR_TEST_TARGETS "${TEXTEDITOR_TEST_TARGETS}" PARENT_SCOPE)
endfunction()

set(TEXTEDITOR_TEST_TARGETS "")

texteditor_add_test(texteditor_exe_tests
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_example.c
    LIBS
        texteditor_lib
)

add_custom_target(texteditor_tests
    DEPENDS
        ${TEXTEDITOR_TEST_TARGETS}
)
