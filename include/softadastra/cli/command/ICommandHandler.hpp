/**
 *
 *  @file ICommandHandler.hpp
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

#ifndef SOFTADASTRA_CLI_I_COMMAND_HANDLER_HPP
#define SOFTADASTRA_CLI_I_COMMAND_HANDLER_HPP

#include <softadastra/cli/parser/ParsedCommand.hpp>
#include <softadastra/cli/types/CliErrorCode.hpp>

namespace softadastra::cli::command
{
  namespace parser = softadastra::cli::parser;
  namespace types = softadastra::cli::types;

  /**
   * @brief Abstract interface for executable CLI command handlers.
   *
   * ICommandHandler defines the execution contract used by the CLI engine and
   * command registry.
   *
   * A command handler receives a ParsedCommand and returns a CliErrorCode that
   * describes the execution result.
   *
   * Implementations are responsible for:
   * - validating command-specific arguments
   * - executing command logic
   * - writing user-facing output when needed
   * - returning a precise error code
   *
   * The interface is intentionally small so application commands can be plugged
   * into the CLI module without depending on the engine internals.
   */
  class ICommandHandler
  {
  public:
    /**
     * @brief Destroys the command handler.
     */
    virtual ~ICommandHandler() = default;

    /**
     * @brief Executes one parsed CLI command.
     *
     * @param command Parsed command input.
     * @return CLI error code describing the execution result.
     */
    [[nodiscard]] virtual types::CliErrorCode handle(
        const parser::ParsedCommand &command) = 0;
  };

} // namespace softadastra::cli::command

#endif // SOFTADASTRA_CLI_I_COMMAND_HANDLER_HPP
