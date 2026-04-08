/*
 * BuiltinCommand.hpp
 */

#ifndef SOFTADASTRA_CLI_BUILTIN_COMMAND_HPP
#define SOFTADASTRA_CLI_BUILTIN_COMMAND_HPP

#include <memory>
#include <vector>

#include <softadastra/cli/command/CliCommand.hpp>
#include <softadastra/cli/command/ICommandHandler.hpp>
#include <softadastra/cli/core/CliContext.hpp>

namespace softadastra::cli::command
{
  namespace cli_core = softadastra::cli::core;

  /**
   * @brief Utility to register built-in CLI commands
   *
   * Provides default commands such as:
   * - help
   * - version
   * - exit
   */
  class BuiltinCommand
  {
  public:
    /**
     * @brief Return all built-in command definitions
     */
    static std::vector<CliCommand> definitions();

    /**
     * @brief Return all built-in handlers aligned with definitions()
     */
    static std::vector<std::shared_ptr<ICommandHandler>> handlers(
        const cli_core::CliContext &context);
  };

} // namespace softadastra::cli::command

#endif
