/*
 * ICommandHandler.hpp
 */

#ifndef SOFTADASTRA_CLI_I_COMMAND_HANDLER_HPP
#define SOFTADASTRA_CLI_I_COMMAND_HANDLER_HPP

#include <softadastra/cli/parser/ParsedCommand.hpp>
#include <softadastra/cli/types/CliErrorCode.hpp>

namespace softadastra::cli::command
{
  namespace parser = softadastra::cli::parser;
  namespace types = softadastra::cli::types;

  /**
   * @brief Abstract command execution handler
   *
   * A command handler is responsible for executing one parsed command
   * and returning a CLI error code describing the result.
   */
  class ICommandHandler
  {
  public:
    virtual ~ICommandHandler() = default;

    /**
     * @brief Execute one parsed command
     */
    virtual types::CliErrorCode handle(
        const parser::ParsedCommand &command) = 0;
  };

} // namespace softadastra::cli::command

#endif
