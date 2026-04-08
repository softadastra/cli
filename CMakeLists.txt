cmake_minimum_required(VERSION 3.20)

project(softadastra_cli
    VERSION 0.1.0
    DESCRIPTION "Softadastra CLI - Command line interface engine"
    LANGUAGES CXX
)

include(GNUInstallDirs)

# ========================
# Options
# ========================
option(SOFTADASTRA_CLI_BUILD_TESTS "Build cli tests" OFF)
option(SOFTADASTRA_CLI_BUILD_EXAMPLES "Build cli examples" OFF)

# ========================
# Global settings
# ========================
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# ========================
# Dependencies (Vix + local)
# ========================
if(NOT SOFTADASTRA_UMBRELLA_BUILD)
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/.vix/vix_deps.cmake")
        include("${CMAKE_CURRENT_SOURCE_DIR}/.vix/vix_deps.cmake")
    endif()
endif()

# CLI has no hard dependency for now
# (pure module → registry-safe by design)

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
else()
    target_compile_options(softadastra_cli PRIVATE -Wall -Wextra -Wpedantic)
endif()

# ========================
# Target properties
# ========================
set_target_properties(softadastra_cli PROPERTIES
    OUTPUT_NAME softadastra_cli
    VERSION ${PROJECT_VERSION}
    SOVERSION 0
    EXPORT_NAME cli
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
message(STATUS "softadastra::cli configured (${PROJECT_VERSION})")
message(STATUS "Include dir:      ${CMAKE_CURRENT_SOURCE_DIR}/include")
message(STATUS "Build tests:      ${SOFTADASTRA_CLI_BUILD_TESTS}")
message(STATUS "Build examples:   ${SOFTADASTRA_CLI_BUILD_EXAMPLES}")
message(STATUS "Build type:       ${CMAKE_BUILD_TYPE}")
message(STATUS "------------------------------------------------------")
