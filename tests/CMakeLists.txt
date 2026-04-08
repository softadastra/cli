cmake_minimum_required(VERSION 3.20)

# ========================
# Guards
# ========================
if(NOT TARGET softadastra::cli AND NOT TARGET softadastra_cli)
    message(FATAL_ERROR
        "softadastra cli target not found.\n"
        "Build the cli module first or include it from the umbrella build."
    )
endif()

set(SOFTADASTRA_CLI_TARGET "")
if(TARGET softadastra::cli)
    set(SOFTADASTRA_CLI_TARGET softadastra::cli)
elseif(TARGET softadastra_cli)
    set(SOFTADASTRA_CLI_TARGET softadastra_cli)
endif()

# ========================
# Helpers
# ========================
function(softadastra_cli_add_test target_name source_file)
    add_executable(${target_name} ${source_file})

    target_link_libraries(${target_name}
        PRIVATE
            ${SOFTADASTRA_CLI_TARGET}
    )

    target_compile_features(${target_name} PRIVATE cxx_std_20)

    if(MSVC)
        target_compile_options(${target_name} PRIVATE /W4 /permissive-)
    else()
        target_compile_options(${target_name} PRIVATE -Wall -Wextra -Wpedantic)
    endif()

    add_test(NAME ${target_name} COMMAND ${target_name})
endfunction()

# ========================
# Parser tests
# ========================
softadastra_cli_add_test(
    softadastra_cli_test_tokenizer
    "${CMAKE_CURRENT_SOURCE_DIR}/parser/TokenizerTests.cpp"
)

softadastra_cli_add_test(
    softadastra_cli_test_arg_parser
    "${CMAKE_CURRENT_SOURCE_DIR}/parser/ArgParserTests.cpp"
)

# ========================
# Command tests
# ========================
softadastra_cli_add_test(
    softadastra_cli_test_command_registry
    "${CMAKE_CURRENT_SOURCE_DIR}/command/CommandRegistryTests.cpp"
)

# ========================
# Engine tests
# ========================
softadastra_cli_add_test(
    softadastra_cli_test_engine
    "${CMAKE_CURRENT_SOURCE_DIR}/engine/CliEngineTests.cpp"
)

# ========================
# IO tests
# ========================
softadastra_cli_add_test(
    softadastra_cli_test_console
    "${CMAKE_CURRENT_SOURCE_DIR}/io/ConsoleTests.cpp"
)

# ========================
# Summary
# ========================
message(STATUS "[cli/tests] configured")
message(STATUS "[cli/tests] cli target: ${SOFTADASTRA_CLI_TARGET}")
