cmake_minimum_required(VERSION 3.21)

project(TextEditor
    VERSION 0.1.0
    DESCRIPTION "A compact C11 project template and engineering standard"
    LANGUAGES C
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
    set(TEXTEDITOR_IS_TOP_LEVEL_DEFAULT ON)
else()
    set(TEXTEDITOR_IS_TOP_LEVEL_DEFAULT OFF)
endif()

if(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build type" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
        "Debug" "Release" "RelWithDebInfo" "MinSizeRel")
endif()

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

option(TEXTEDITOR_ENABLE_ASAN "Enable AddressSanitizer where supported" OFF)
option(TEXTEDITOR_ENABLE_UBSAN "Enable UndefinedBehaviorSanitizer where supported" OFF)
option(TEXTEDITOR_ENABLE_COVERAGE "Enable coverage flags where supported" OFF)
if(NOT CMAKE_CONFIGURATION_TYPES AND CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(TEXTEDITOR_DEVELOPMENT_LOGS_DEFAULT ON)
else()
    set(TEXTEDITOR_DEVELOPMENT_LOGS_DEFAULT OFF)
endif()
option(TEXTEDITOR_DEVELOPMENT_LOGS
    "Enable source file and line information in runtime logs"
    ${TEXTEDITOR_DEVELOPMENT_LOGS_DEFAULT}
)
option(TEXTEDITOR_BUILD_EXE "Build the TextEditor executable" ${TEXTEDITOR_IS_TOP_LEVEL_DEFAULT})
option(TEXTEDITOR_BUILD_TESTING "Build CTest tests" ${TEXTEDITOR_IS_TOP_LEVEL_DEFAULT})
option(TEXTEDITOR_INSTALL "Generate install rules" ${TEXTEDITOR_IS_TOP_LEVEL_DEFAULT})

set(TEXTEDITOR_GENERATED_INCLUDE_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated/include")
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/texteditor_version.h.in"
    "${TEXTEDITOR_GENERATED_INCLUDE_DIR}/utils/version.h"
    @ONLY
)

include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/CompilerOptions.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/Dependencies.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/Sources.cmake")

add_library(texteditor_lib ${TEXTEDITOR_LIB_SOURCES})
add_library(TextEditor::texteditor_lib ALIAS texteditor_lib)

target_compile_features(texteditor_lib PUBLIC c_std_11)

target_compile_definitions(texteditor_lib
    PRIVATE
        TEXTEDITOR_BUILDING_LIBRARY
)
if(BUILD_SHARED_LIBS)
    target_compile_definitions(texteditor_lib PUBLIC TEXTEDITOR_SHARED)
endif()
if(TEXTEDITOR_DEVELOPMENT_LOGS)
    target_compile_definitions(texteditor_lib PUBLIC TEXTEDITOR_DEVELOPMENT_LOGS)
endif()
set_target_properties(texteditor_lib PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

target_include_directories(texteditor_lib
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${TEXTEDITOR_GENERATED_INCLUDE_DIR}>
        $<INSTALL_INTERFACE:include>
)
texteditor_target_defaults(texteditor_lib)

if(TEXTEDITOR_BUILD_EXE)
    add_executable(texteditor_exe ${TEXTEDITOR_EXE_SOURCES})
    target_link_libraries(texteditor_exe PRIVATE texteditor_lib)
    texteditor_target_defaults(texteditor_exe)
    set_target_properties(texteditor_exe PROPERTIES
        OUTPUT_NAME "td"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    )
endif()

if(TEXTEDITOR_BUILD_TESTING)
    enable_testing()
    include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/Tests.cmake")
endif()

if(TEXTEDITOR_INSTALL)
    include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/Packaging.cmake")
endif()
