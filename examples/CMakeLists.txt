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
function(softadastra_cli_add_example target_name source_file)
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
endfunction()

# ========================
# Examples
# ========================
softadastra_cli_add_example(
    softadastra_cli_example_minimal
    "${CMAKE_CURRENT_SOURCE_DIR}/cli_minimal.cpp"
)

softadastra_cli_add_example(
    softadastra_cli_example_commands_demo
    "${CMAKE_CURRENT_SOURCE_DIR}/cli_commands_demo.cpp"
)

softadastra_cli_add_example(
    softadastra_cli_example_tokenizer
    "${CMAKE_CURRENT_SOURCE_DIR}/cli_tokenizer.cpp"
)

softadastra_cli_add_example(
    softadastra_cli_example_arg_parser
    "${CMAKE_CURRENT_SOURCE_DIR}/cli_arg_parser.cpp"
)

softadastra_cli_add_example(
    softadastra_cli_example_table_formatter
    "${CMAKE_CURRENT_SOURCE_DIR}/cli_table_formatter.cpp"
)

softadastra_cli_add_example(
    softadastra_cli_example_ui_style
    "${CMAKE_CURRENT_SOURCE_DIR}/cli_ui_style.cpp"
)

softadastra_cli_add_example(
    softadastra_cli_example_registry
    "${CMAKE_CURRENT_SOURCE_DIR}/cli_registry.cpp"
)

softadastra_cli_add_example(
    softadastra_cli_example_custom_command
    "${CMAKE_CURRENT_SOURCE_DIR}/cli_custom_command.cpp"
)

softadastra_cli_add_example(
    softadastra_cli_example_service_single
    "${CMAKE_CURRENT_SOURCE_DIR}/cli_service_single.cpp"
)

# ========================
# Summary
# ========================
message(STATUS "[cli/examples] configured")
message(STATUS "[cli/examples] cli target: ${SOFTADASTRA_CLI_TARGET}")
