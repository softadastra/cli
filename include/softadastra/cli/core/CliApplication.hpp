/*
 * CliApplication.hpp
 */

#ifndef SOFTADASTRA_CLI_APPLICATION_HPP
#define SOFTADASTRA_CLI_APPLICATION_HPP

#include <string>

#include <softadastra/cli/core/CliContext.hpp>
#include <softadastra/cli/core/CliSession.hpp>
#include <softadastra/cli/parser/ParsedCommand.hpp>
#include <softadastra/cli/types/CliErrorCode.hpp>

namespace softadastra::cli::core
{
  namespace parser = softadastra::cli::parser;
  namespace types = softadastra::cli::types;

  /**
   * @brief High-level CLI application orchestrator
   *
   * Responsibilities:
   * - manage session lifecycle
   * - execute parsed commands via registry
   */
  class CliApplication
  {
  public:
    explicit CliApplication(const CliContext &context);

    /**
     * @brief Start CLI application
     */
    bool start();

    /**
     * @brief Stop CLI application
     */
    void stop();

    /**
     * @brief Check if running
     */
    bool running() const noexcept;

    /**
     * @brief Execute one parsed command
     */
    types::CliErrorCode execute(const parser::ParsedCommand &command);

    /**
     * @brief Access session
     */
    CliSession &session() noexcept;

    /**
     * @brief Access context
     */
    const CliContext &context() const noexcept;

  private:
    const CliContext &context_;
    CliSession session_;
  };

} // namespace softadastra::cli::core

#endif
