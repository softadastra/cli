/*
 * CliEngine.hpp
 */

#ifndef SOFTADASTRA_CLI_ENGINE_HPP
#define SOFTADASTRA_CLI_ENGINE_HPP

#include <optional>
#include <string>

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
   * @brief Orchestrates CLI parsing and command execution
   *
   * Responsibilities:
   * - manage engine lifecycle
   * - tokenize raw input
   * - build command line representation
   * - parse command arguments
   * - execute parsed commands through CliApplication
   */
  class CliEngine
  {
  public:
    explicit CliEngine(const cli_core::CliContext &context);

    /**
     * @brief Start the CLI engine
     */
    bool start();

    /**
     * @brief Stop the CLI engine
     */
    void stop();

    /**
     * @brief Return current engine status
     */
    cli_types::CliStatus status() const noexcept;

    /**
     * @brief Return true if engine is running
     */
    bool running() const noexcept;

    /**
     * @brief Parse raw input into a structured command
     */
    std::optional<cli_parser::ParsedCommand> parse(
        const std::string &input) const;

    /**
     * @brief Execute one raw CLI input line
     */
    cli_types::CliErrorCode execute(const std::string &input);

    /**
     * @brief Execute one parsed command
     */
    cli_types::CliErrorCode execute(
        const cli_parser::ParsedCommand &command);

    /**
     * @brief Return underlying application
     */
    cli_core::CliApplication &application() noexcept;

    /**
     * @brief Return engine context
     */
    const cli_core::CliContext &context() const noexcept;

  private:
    const cli_core::CliContext &context_;
    cli_core::CliApplication application_;
    cli_types::CliStatus status_{cli_types::CliStatus::Idle};
  };

} // namespace softadastra::cli::engine

#endif
