/**
 *
 *  @file CliContext.hpp
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

#ifndef SOFTADASTRA_CLI_CONTEXT_HPP
#define SOFTADASTRA_CLI_CONTEXT_HPP

#include <stdexcept>

#include <softadastra/cli/command/CommandRegistry.hpp>
#include <softadastra/cli/core/CliConfig.hpp>
#include <softadastra/cli/core/CliSession.hpp>

namespace softadastra::cli::core
{
  namespace command = softadastra::cli::command;

  /**
   * @brief Shared runtime context for the CLI module.
   *
   * CliContext provides controlled access to shared CLI runtime objects.
   *
   * It is used by:
   * - built-in commands
   * - command handlers
   * - CLI engine
   * - CLI application
   *
   * The context does not own the referenced objects. The owner must guarantee
   * that config, registry, and session outlive the context.
   */
  struct CliContext
  {
    /**
     * @brief CLI runtime configuration.
     */
    const CliConfig *config{nullptr};

    /**
     * @brief Command registry used for lookup and dispatch.
     */
    command::CommandRegistry *registry{nullptr};

    /**
     * @brief Current CLI session state.
     */
    CliSession *session{nullptr};

    /**
     * @brief Returns true when the context is usable.
     *
     * @return true if all required runtime objects are available.
     */
    [[nodiscard]] bool valid() const noexcept
    {
      return config != nullptr &&
             registry != nullptr &&
             session != nullptr &&
             config->valid();
    }

    /**
     * @brief Returns the configuration reference.
     *
     * @return CLI configuration.
     *
     * @throws std::runtime_error if config is null.
     */
    [[nodiscard]] const CliConfig &config_ref() const
    {
      if (config == nullptr)
      {
        throw std::runtime_error("CliContext: config is null");
      }

      return *config;
    }

    /**
     * @brief Returns the command registry reference.
     *
     * @return Command registry.
     *
     * @throws std::runtime_error if registry is null.
     */
    [[nodiscard]] command::CommandRegistry &registry_ref() const
    {
      if (registry == nullptr)
      {
        throw std::runtime_error("CliContext: registry is null");
      }

      return *registry;
    }

    /**
     * @brief Returns the CLI session reference.
     *
     * @return CLI session.
     *
     * @throws std::runtime_error if session is null.
     */
    [[nodiscard]] CliSession &session_ref() const
    {
      if (session == nullptr)
      {
        throw std::runtime_error("CliContext: session is null");
      }

      return *session;
    }
  };

} // namespace softadastra::cli::core

#endif // SOFTADASTRA_CLI_CONTEXT_HPP
