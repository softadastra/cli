/**
 *
 *  @file HelpFormatter.hpp
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

#ifndef SOFTADASTRA_CLI_HELP_FORMATTER_HPP
#define SOFTADASTRA_CLI_HELP_FORMATTER_HPP

#include <string>
#include <vector>

#include <softadastra/cli/command/CliCommand.hpp>

namespace softadastra::cli::utils
{
  namespace command = softadastra::cli::command;

  /**
   * @brief Formats human-readable CLI help output.
   *
   * HelpFormatter centralizes help rendering for the CLI module.
   *
   * It is responsible for:
   * - full application help
   * - single command help
   * - usage lines
   * - command descriptions
   *
   * The formatter is stateless and safe to use from any CLI component.
   */
  class HelpFormatter
  {
  public:
    /**
     * @brief Formats full application help.
     *
     * @param commands Commands to display.
     * @param app_name Application name used in usage text.
     * @return Formatted help text.
     */
    [[nodiscard]] static std::string format(
        const std::vector<command::CliCommand> &commands,
        const std::string &app_name);

    /**
     * @brief Formats help for a single command.
     *
     * @param command Command metadata.
     * @return Formatted command help text.
     */
    [[nodiscard]] static std::string format_command(
        const command::CliCommand &command);

  private:
    /**
     * @brief Formats one command summary line.
     *
     * @param command Command metadata.
     * @return Formatted command line.
     */
    [[nodiscard]] static std::string format_command_line(
        const command::CliCommand &command);
  };

} // namespace softadastra::cli::utils

#endif // SOFTADASTRA_CLI_HELP_FORMATTER_HPP
