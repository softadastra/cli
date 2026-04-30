/**
 *
 *  @file CliApplication.hpp
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

#ifndef SOFTADASTRA_CLI_APPLICATION_HPP
#define SOFTADASTRA_CLI_APPLICATION_HPP

#include <softadastra/cli/core/CliContext.hpp>
#include <softadastra/cli/parser/ParsedCommand.hpp>
#include <softadastra/cli/types/CliErrorCode.hpp>

namespace softadastra::cli::core
{
  namespace parser = softadastra::cli::parser;
  namespace types = softadastra::cli::types;

  /**
   * @brief High-level CLI application orchestrator.
   *
   * CliApplication owns the execution flow for parsed commands.
   *
   * It is responsible for:
   * - validating runtime context
   * - starting and stopping the CLI session
   * - resolving command handlers through the registry
   * - executing parsed commands
   * - updating session state
   *
   * The application does not tokenize raw input. Parsing is handled by the
   * parser layer before execution reaches this class.
   */
  class CliApplication
  {
  public:
    /**
     * @brief Creates a CLI application from a runtime context.
     *
     * The context must reference valid config, registry, and session objects.
     *
     * @param context Shared CLI runtime context.
     */
    explicit CliApplication(const CliContext &context);

    /**
     * @brief Starts the CLI application session.
     *
     * @return true when the application started successfully.
     */
    [[nodiscard]] bool start();

    /**
     * @brief Requests the CLI application to stop.
     */
    void stop();

    /**
     * @brief Returns true when the CLI session is running.
     *
     * @return true if running.
     */
    [[nodiscard]] bool running() const noexcept;

    /**
     * @brief Executes one parsed command.
     *
     * @param command Parsed command input.
     * @return CLI error code produced by command execution.
     */
    [[nodiscard]] types::CliErrorCode execute(
        const parser::ParsedCommand &command);

    /**
     * @brief Returns the runtime context.
     *
     * @return CLI context.
     */
    [[nodiscard]] const CliContext &context() const noexcept;

  private:
    const CliContext &context_;
  };

} // namespace softadastra::cli::core

#endif // SOFTADASTRA_CLI_APPLICATION_HPP
