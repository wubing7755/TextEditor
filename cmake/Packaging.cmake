include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

set(TEXTEDITOR_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/TextEditor")

install(TARGETS texteditor_core
    EXPORT TextEditorTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(DIRECTORY ${TEXTEDITOR_GENERATED_INCLUDE_DIR}/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/TextEditorConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/TextEditorConfig.cmake"
    INSTALL_DESTINATION "${TEXTEDITOR_INSTALL_CMAKEDIR}"
)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/TextEditorConfigVersion.cmake"
    VERSION "${PROJECT_VERSION}"
    COMPATIBILITY SameMajorVersion
)

install(EXPORT TextEditorTargets
    NAMESPACE TextEditor::
    DESTINATION ${TEXTEDITOR_INSTALL_CMAKEDIR}
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/TextEditorConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/TextEditorConfigVersion.cmake"
    DESTINATION ${TEXTEDITOR_INSTALL_CMAKEDIR}
)
