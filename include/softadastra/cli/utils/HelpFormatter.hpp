/*
 * HelpFormatter.hpp
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
   * @brief Formats CLI help output
   *
   * Responsible for rendering:
   * - command list
   * - usage
   * - descriptions
   */
  class HelpFormatter
  {
  public:
    /**
     * @brief Format full help output
     */
    static std::string format(const std::vector<command::CliCommand> &commands,
                              const std::string &app_name);

    /**
     * @brief Format a single command help
     */
    static std::string format_command(const command::CliCommand &command);

  private:
    static std::string format_command_line(const command::CliCommand &command);
  };

} // namespace softadastra::cli::utils

#endif
