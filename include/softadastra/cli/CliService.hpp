/**
 *
 *  @file CliService.hpp
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

#ifndef SOFTADASTRA_CLI_SERVICE_HPP
#define SOFTADASTRA_CLI_SERVICE_HPP

#include <memory>
#include <string>
#include <string_view>

#include <softadastra/cli/CliOptions.hpp>
#include <softadastra/cli/command/CliCommand.hpp>
#include <softadastra/cli/command/CommandRegistry.hpp>
#include <softadastra/cli/command/ICommandHandler.hpp>
#include <softadastra/cli/core/CliConfig.hpp>
#include <softadastra/cli/core/CliContext.hpp>
#include <softadastra/cli/core/CliSession.hpp>
#include <softadastra/cli/engine/CliEngine.hpp>

namespace softadastra::cli
{
  namespace cli_core = softadastra::cli::core;
  namespace cli_engine = softadastra::cli::engine;
  namespace cli_command = softadastra::cli::command;

  /**
   * @brief High-level entry point for the CLI module.
   *
   * CliService owns the main CLI runtime objects and exposes a simple public
   * API for applications that want to embed or run the Softadastra CLI.
   *
   * It is responsible for:
   * - holding CLI configuration
   * - owning the command registry
   * - owning the session state
   * - wiring the runtime context
   * - starting the CLI engine
   * - running one-shot commands
   * - running interactive sessions
   */
  class CliService
  {
  public:
    /**
     * @brief Creates a CLI service from configuration.
     *
     * @param config CLI configuration.
     */
    explicit CliService(const cli_core::CliConfig &config);

    /**
     * @brief Runs the CLI using startup options.
     *
     * @param options CLI startup options.
     * @return Process-style exit code.
     */
    [[nodiscard]] int run(const CliOptions &options);

    /**
     * @brief Registers a command and its handler.
     *
     * Invalid commands or null handlers are ignored by the registry.
     *
     * @param command Command metadata.
     * @param handler Command handler.
     */
    void register_command(
        const cli_command::CliCommand &command,
        std::shared_ptr<cli_command::ICommandHandler> handler);

    /**
     * @brief Returns the current CLI configuration.
     *
     * @return CLI configuration.
     */
    [[nodiscard]] const cli_core::CliConfig &config() const noexcept;

    /**
     * @brief Returns the command registry.
     *
     * @return Command registry.
     */
    [[nodiscard]] cli_command::CommandRegistry &registry() noexcept;

    /**
     * @brief Returns the command registry.
     *
     * @return Command registry.
     */
    [[nodiscard]] const cli_command::CommandRegistry &registry() const noexcept;

    /**
     * @brief Returns the CLI session.
     *
     * @return CLI session.
     */
    [[nodiscard]] cli_core::CliSession &session() noexcept;

    /**
     * @brief Returns the CLI session.
     *
     * @return CLI session.
     */
    [[nodiscard]] const cli_core::CliSession &session() const noexcept;

    /**
     * @brief Returns the CLI engine.
     *
     * @return CLI engine.
     */
    [[nodiscard]] cli_engine::CliEngine &engine() noexcept;

    /**
     * @brief Returns the CLI engine.
     *
     * @return CLI engine.
     */
    [[nodiscard]] const cli_engine::CliEngine &engine() const noexcept;

  private:
    /**
     * @brief Runs the interactive REPL loop.
     *
     * @return Process-style exit code.
     */
    [[nodiscard]] int run_interactive();

    /**
     * @brief Runs a single command line.
     *
     * @param command Command line to execute.
     * @return Process-style exit code.
     */
    [[nodiscard]] int run_single(std::string_view command);

    /**
     * @brief Converts a CLI error code to a process exit code.
     *
     * @param code CLI error code.
     * @return Process-style exit code.
     */
    [[nodiscard]] static int to_exit_code(
        softadastra::cli::types::CliErrorCode code) noexcept;

  private:
    cli_core::CliConfig config_{};
    cli_command::CommandRegistry registry_{};
    cli_core::CliSession session_{};
    cli_core::CliContext context_{};
    cli_engine::CliEngine engine_;
  };

} // namespace softadastra::cli

#endif // SOFTADASTRA_CLI_SERVICE_HPP
