/**
 *
 *  @file CliEngine.hpp
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

#ifndef SOFTADASTRA_CLI_ENGINE_HPP
#define SOFTADASTRA_CLI_ENGINE_HPP

#include <optional>
#include <string>
#include <string_view>

#include <softadastra/cli/core/CliApplication.hpp>
#include <softadastra/cli/core/CliContext.hpp>
#include <softadastra/cli/parser/ArgParser.hpp>
#include <softadastra/cli/parser/CommandLine.hpp>
#include <softadastra/cli/parser/ParsedCommand.hpp>
#include <softadastra/cli/parser/Tokenizer.hpp>
#include <softadastra/cli/types/CliErrorCode.hpp>
#include <softadastra/cli/types/CliStatus.hpp>

namespace softadastra::cli::engine
{
  namespace cli_core = softadastra::cli::core;
  namespace cli_parser = softadastra::cli::parser;
  namespace cli_types = softadastra::cli::types;

  /**
   * @brief Orchestrates CLI parsing and command execution.
   *
   * CliEngine is the high-level runtime entry point for the CLI module.
   *
   * It is responsible for:
   * - engine lifecycle
   * - raw input tokenization
   * - command-line parsing
   * - parsed command execution
   * - delegation to CliApplication
   *
   * The engine does not implement command logic directly. Commands are resolved
   * through the CommandRegistry owned by the CLI context.
   */
  class CliEngine
  {
  public:
    /**
     * @brief Creates a CLI engine from a shared runtime context.
     *
     * @param context Shared CLI context.
     */
    explicit CliEngine(const cli_core::CliContext &context);

    /**
     * @brief Starts the CLI engine and its application.
     *
     * @return true when startup succeeds.
     */
    [[nodiscard]] bool start();

    /**
     * @brief Stops the CLI engine and its application.
     */
    void stop();

    /**
     * @brief Returns the current engine status.
     *
     * @return Current CLI status.
     */
    [[nodiscard]] cli_types::CliStatus status() const noexcept;

    /**
     * @brief Returns true when the engine is running.
     *
     * @return true if the engine is active.
     */
    [[nodiscard]] bool running() const noexcept;

    /**
     * @brief Parses raw CLI input into a structured command.
     *
     * @param input Raw input line.
     * @return Parsed command or std::nullopt when input is empty.
     */
    [[nodiscard]] std::optional<cli_parser::ParsedCommand> parse(
        std::string_view input) const;

    /**
     * @brief Executes one raw CLI input line.
     *
     * @param input Raw input line.
     * @return CLI error code.
     */
    [[nodiscard]] cli_types::CliErrorCode execute(
        std::string_view input);

    /**
     * @brief Executes one parsed command.
     *
     * @param command Parsed command.
     * @return CLI error code.
     */
    [[nodiscard]] cli_types::CliErrorCode execute(
        const cli_parser::ParsedCommand &command);

    /**
     * @brief Returns the underlying CLI application.
     *
     * @return CLI application.
     */
    [[nodiscard]] cli_core::CliApplication &application() noexcept;

    /**
     * @brief Returns the underlying CLI application.
     *
     * @return CLI application.
     */
    [[nodiscard]] const cli_core::CliApplication &application() const noexcept;

    /**
     * @brief Returns the shared engine context.
     *
     * @return CLI context.
     */
    [[nodiscard]] const cli_core::CliContext &context() const noexcept;

  private:
    const cli_core::CliContext &context_;
    cli_core::CliApplication application_;
    cli_types::CliStatus status_{cli_types::CliStatus::Idle};
  };

} // namespace softadastra::cli::engine

#endif // SOFTADASTRA_CLI_ENGINE_HPP
