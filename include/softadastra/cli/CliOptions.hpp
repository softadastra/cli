/**
 *
 *  @file CliOptions.hpp
 *  @author Gaspard Kirira
 *
 *  Copyright 2026, Softadastra.
 *  All rights reserved.
 *  https://github.com/softadastra/softadastra
 *
 *  Licensed under the Apache License, Version 2.0.
 *
 *  Softadastra CLI
 *
 */

#ifndef SOFTADASTRA_CLI_OPTIONS_HPP
#define SOFTADASTRA_CLI_OPTIONS_HPP

#include <cstddef>
#include <string>
#include <utility>
#include <vector>

namespace softadastra::cli
{
  /**
   * @brief Startup options for the CLI service.
   *
   * CliOptions describes how the CLI service should be started.
   *
   * It supports:
   * - interactive REPL mode
   * - single command execution
   * - raw argv preservation
   * - optional startup command
   *
   * This structure is intentionally simple because it is part of the public
   * entry surface of the CLI module.
   */
  struct CliOptions
  {
    /**
     * @brief Raw command-line arguments.
     *
     * Usually built from argv.
     */
    std::vector<std::string> args{};

    /**
     * @brief Enables interactive mode.
     *
     * When true, the CLI service may enter a REPL loop.
     */
    bool interactive{true};

    /**
     * @brief Optional command to execute directly.
     *
     * When this value is present, the service can execute it once before
     * returning or before entering interactive mode depending on the caller.
     */
    std::string command{};

    /**
     * @brief Creates default CLI options.
     */
    CliOptions() = default;

    /**
     * @brief Creates CLI options from raw args.
     *
     * @param startup_args Raw startup arguments.
     * @param run_interactive Whether interactive mode is enabled.
     * @param startup_command Optional command to execute.
     */
    CliOptions(
        std::vector<std::string> startup_args,
        bool run_interactive = true,
        std::string startup_command = {})
        : args(std::move(startup_args)),
          interactive(run_interactive),
          command(std::move(startup_command))
    {
    }

    /**
     * @brief Returns true when the options are usable.
     *
     * @return true when interactive mode is enabled or a command is provided.
     */
    [[nodiscard]] bool valid() const noexcept
    {
      return interactive || !command.empty();
    }

    /**
     * @brief Returns true when a startup command is provided.
     *
     * @return true if command is not empty.
     */
    [[nodiscard]] bool has_command() const noexcept
    {
      return !command.empty();
    }

    /**
     * @brief Returns true when raw arguments are available.
     *
     * @return true if args is not empty.
     */
    [[nodiscard]] bool has_args() const noexcept
    {
      return !args.empty();
    }

    /**
     * @brief Returns the number of raw arguments.
     *
     * @return Raw argument count.
     */
    [[nodiscard]] std::size_t arg_count() const noexcept
    {
      return args.size();
    }

    /**
     * @brief Creates options for interactive mode.
     *
     * @return Interactive CLI options.
     */
    [[nodiscard]] static CliOptions interactive_mode()
    {
      CliOptions options;
      options.interactive = true;
      return options;
    }

    /**
     * @brief Creates options for single-command execution.
     *
     * @param value Command to execute.
     * @return Single-command CLI options.
     */
    [[nodiscard]] static CliOptions single_command(std::string value)
    {
      CliOptions options;
      options.interactive = false;
      options.command = std::move(value);
      return options;
    }
  };

} // namespace softadastra::cli

#endif // SOFTADASTRA_CLI_OPTIONS_HPP
