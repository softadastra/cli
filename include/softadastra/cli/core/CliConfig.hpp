/**
 *
 *  @file CliConfig.hpp
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

#ifndef SOFTADASTRA_CLI_CONFIG_HPP
#define SOFTADASTRA_CLI_CONFIG_HPP

#include <string>

namespace softadastra::cli::core
{
  /**
   * @brief Runtime configuration for the CLI module.
   *
   * CliConfig defines the static runtime options used to initialize and run
   * the CLI application.
   *
   * It is used by:
   * - CliApplication
   * - CliEngine
   * - CliContext
   * - tests and embedded CLI integrations
   */
  struct CliConfig
  {
    /**
     * @brief Application name displayed in help, usage and diagnostics.
     *
     * Example: "softadastra".
     */
    std::string app_name{"softadastra"};

    /**
     * @brief Application version displayed by version and help commands.
     */
    std::string version{"0.1.0"};

    /**
     * @brief Enables interactive REPL mode.
     *
     * When true, the CLI may keep reading commands from stdin.
     * When false, the CLI is expected to execute one command and exit.
     */
    bool interactive{true};

    /**
     * @brief Shows the startup banner when the CLI starts.
     */
    bool show_banner{true};

    /**
     * @brief Enables colored terminal output.
     *
     * This can be disabled for logs, CI, scripts, or terminals that do not
     * support ANSI escape sequences.
     */
    bool color_output{true};

    /**
     * @brief Enables verbose diagnostic output.
     */
    bool verbose{false};

    /**
     * @brief Enables strict argument validation.
     *
     * When enabled, unknown options and malformed inputs should be rejected
     * early by parsers and command handlers.
     */
    bool strict_mode{true};

    /**
     * @brief Validates the CLI configuration.
     *
     * @return true when required fields are present.
     */
    [[nodiscard]] bool valid() const noexcept
    {
      return !app_name.empty() &&
             !version.empty();
    }

    /**
     * @brief Creates the default Softadastra CLI configuration.
     *
     * @return Default production-ready configuration.
     */
    [[nodiscard]] static CliConfig defaults()
    {
      return CliConfig{};
    }
  };

} // namespace softadastra::cli::core

#endif // SOFTADASTRA_CLI_CONFIG_HPP
