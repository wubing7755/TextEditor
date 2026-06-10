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
option(TEXTEDITOR_BUILD_EXAMPLE "Build the example executable" ${TEXTEDITOR_IS_TOP_LEVEL_DEFAULT})
option(TEXTEDITOR_BUILD_TESTING "Build CTest tests" ${TEXTEDITOR_IS_TOP_LEVEL_DEFAULT})
option(TEXTEDITOR_INSTALL "Generate install rules" ${TEXTEDITOR_IS_TOP_LEVEL_DEFAULT})

set(TEXTEDITOR_GENERATED_INCLUDE_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated/include")
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/texteditor_version.h.in"
    "${TEXTEDITOR_GENERATED_INCLUDE_DIR}/texteditor/version.h"
    @ONLY
)

include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/CompilerOptions.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/Dependencies.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/Sources.cmake")

add_library(texteditor_core ${TEXTEDITOR_CORE_SOURCES})
add_library(TextEditor::texteditor_core ALIAS texteditor_core)

target_compile_features(texteditor_core PUBLIC c_std_11)

target_compile_definitions(texteditor_core
    PRIVATE
        TEXTEDITOR_BUILDING_LIBRARY
)
if(BUILD_SHARED_LIBS)
    target_compile_definitions(texteditor_core PUBLIC TEXTEDITOR_SHARED)
endif()
set_target_properties(texteditor_core PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

target_include_directories(texteditor_core
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${TEXTEDITOR_GENERATED_INCLUDE_DIR}>
        $<INSTALL_INTERFACE:include>
)
texteditor_target_defaults(texteditor_core)

if(TEXTEDITOR_BUILD_EXAMPLE)
    add_executable(texteditor_example ${TEXTEDITOR_EXAMPLE_SOURCES})
    target_link_libraries(texteditor_example PRIVATE texteditor_core)
    texteditor_target_defaults(texteditor_example)
    set_target_properties(texteditor_example PROPERTIES
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
