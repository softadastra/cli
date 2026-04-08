cmake_minimum_required(VERSION 3.20)

if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    project(softadastra_cli
        VERSION 0.1.0
        DESCRIPTION "Softadastra CLI - Command line interface engine"
        LANGUAGES CXX
    )
endif()

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# ========================
# Standalone fallback options
# ========================
if(NOT DEFINED SOFTADASTRA_WARNINGS_AS_ERRORS)
    option(SOFTADASTRA_WARNINGS_AS_ERRORS "Treat warnings as errors" OFF)
endif()

if(SOFTADASTRA_UMBRELLA_BUILD)
    set(SOFTADASTRA_CLI_BUILD_TESTS ${SOFTADASTRA_BUILD_TESTS})
else()
    option(SOFTADASTRA_CLI_BUILD_TESTS "Build cli tests" OFF)
endif()

option(SOFTADASTRA_CLI_BUILD_EXAMPLES "Build cli examples" OFF)

# ========================
# Dependencies (Vix + local)
# ========================
if(NOT SOFTADASTRA_UMBRELLA_BUILD)
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/.vix/vix_deps.cmake")
        include("${CMAKE_CURRENT_SOURCE_DIR}/.vix/vix_deps.cmake")
    endif()
endif()

# CLI has no hard dependency for now
# (pure module -> registry-safe by design)

# ========================
# Sources
# ========================
file(GLOB_RECURSE SOFTADASTRA_CLI_SOURCES
    CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

# ========================
# Library
# ========================
add_library(softadastra_cli ${SOFTADASTRA_CLI_SOURCES})
add_library(softadastra::cli ALIAS softadastra_cli)

target_compile_features(softadastra_cli PUBLIC cxx_std_20)

# ========================
# Include directories
# ========================
target_include_directories(softadastra_cli
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# ========================
# Compiler options
# ========================
if(MSVC)
    target_compile_options(softadastra_cli PRIVATE /W4 /permissive-)
    if(SOFTADASTRA_WARNINGS_AS_ERRORS)
        target_compile_options(softadastra_cli PRIVATE /WX)
    endif()
else()
    target_compile_options(softadastra_cli PRIVATE -Wall -Wextra -Wpedantic)
    if(SOFTADASTRA_WARNINGS_AS_ERRORS)
        target_compile_options(softadastra_cli PRIVATE -Werror)
    endif()
endif()

# ========================
# Target properties
# ========================
set_target_properties(softadastra_cli PROPERTIES
    OUTPUT_NAME softadastra_cli
    VERSION 0.1.0
    SOVERSION 0
    EXPORT_NAME cli
)

# ========================
# Install
# ========================
install(
    TARGETS softadastra_cli
    EXPORT softadastraCliTargets
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
    DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
    EXPORT softadastraCliTargets
    FILE softadastraCliTargets.cmake
    NAMESPACE softadastra::
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/softadastra_cli"
)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/softadastra_cliConfigVersion.cmake"
    VERSION 0.1.0
    COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/softadastra_cliConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/softadastra_cliConfig.cmake"
    INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/softadastra_cli"
)

install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/softadastra_cliConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/softadastra_cliConfigVersion.cmake"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/softadastra_cli"
)

# ========================
# Examples
# ========================
if(SOFTADASTRA_CLI_BUILD_EXAMPLES AND NOT SOFTADASTRA_UMBRELLA_BUILD)
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/examples/CMakeLists.txt")
        add_subdirectory(examples)
    else()
        message(STATUS "[cli] examples/ missing CMakeLists.txt -> skipping")
    endif()
endif()

# ========================
# Tests
# ========================
if(SOFTADASTRA_CLI_BUILD_TESTS)
    include(CTest)
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tests/CMakeLists.txt")
        add_subdirectory(tests)
    else()
        message(STATUS "[cli] tests/ missing CMakeLists.txt -> skipping")
    endif()
endif()

# ========================
# Summary
# ========================
message(STATUS "------------------------------------------------------")
message(STATUS "softadastra::cli configured (0.1.0)")
message(STATUS "Include dir:      ${CMAKE_CURRENT_SOURCE_DIR}/include")
message(STATUS "Build tests:      ${SOFTADASTRA_CLI_BUILD_TESTS}")
message(STATUS "Build examples:   ${SOFTADASTRA_CLI_BUILD_EXAMPLES}")
message(STATUS "Warnings=error:   ${SOFTADASTRA_WARNINGS_AS_ERRORS}")
message(STATUS "Build type:       ${CMAKE_BUILD_TYPE}")
message(STATUS "Install prefix:   ${CMAKE_INSTALL_PREFIX}")
message(STATUS "------------------------------------------------------")
