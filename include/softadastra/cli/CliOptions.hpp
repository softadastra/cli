/*
 * CliOptions.hpp
 */

#ifndef SOFTADASTRA_CLI_OPTIONS_HPP
#define SOFTADASTRA_CLI_OPTIONS_HPP

#include <string>
#include <vector>

namespace softadastra::cli
{
  /**
   * @brief Entry options for the CLI service
   *
   * Represents how the CLI is started:
   * - interactive mode
   * - single command execution
   */
  struct CliOptions
  {
    /**
     * Raw arguments (argv)
     */
    std::vector<std::string> args;

    /**
     * Run in interactive mode (REPL)
     */
    bool interactive{true};

    /**
     * Optional command to execute directly
     */
    std::string command;

    /**
     * @brief Check whether options are valid
     */
    bool valid() const noexcept
    {
      return interactive || !command.empty();
    }
  };

} // namespace softadastra::cli

#endif
