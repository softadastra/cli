/**
 *
 *  @file BuiltinCommand.hpp
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
   * @brief Factory for built-in CLI command definitions and handlers.
   *
   * BuiltinCommand centralizes the default commands provided by the CLI module.
   *
   * Built-in commands usually include:
   * - help
   * - version
   * - exit
   *
   * The order of definitions() and handlers() must remain aligned when they
   * are registered together by the command registry.
   *
   * This class is stateless and only exposes factory helpers.
   */
  class BuiltinCommand
  {
  public:
    /**
     * @brief Returns built-in command definitions.
     *
     * @return Built-in command metadata.
     */
    [[nodiscard]] static std::vector<CliCommand> definitions();

    /**
     * @brief Returns built-in command handlers.
     *
     * The returned handlers must be in the same logical order as definitions().
     *
     * @param context CLI runtime context used by built-in handlers.
     * @return Built-in command handlers.
     */
    [[nodiscard]] static std::vector<std::shared_ptr<ICommandHandler>> handlers(
        const cli_core::CliContext &context);
  };

} // namespace softadastra::cli::command

#endif // SOFTADASTRA_CLI_BUILTIN_COMMAND_HPP
