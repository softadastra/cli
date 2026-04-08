/*
 * CliContext.hpp
 */

#ifndef SOFTADASTRA_CLI_CONTEXT_HPP
#define SOFTADASTRA_CLI_CONTEXT_HPP

#include <stdexcept>

#include <softadastra/cli/command/CommandRegistry.hpp>
#include <softadastra/cli/core/CliConfig.hpp>

namespace softadastra::cli::core
{
  namespace command = softadastra::cli::command;

  /**
   * @brief Shared runtime context for the CLI module
   *
   * Provides access to:
   * - CLI configuration
   * - Command registry
   */
  struct CliContext
  {
    /**
     * CLI configuration
     */
    const CliConfig *config{nullptr};

    /**
     * Command registry
     */
    command::CommandRegistry *registry{nullptr};

    /**
     * @brief Check whether context is usable
     */
    bool valid() const noexcept
    {
      return config != nullptr &&
             registry != nullptr &&
             config->valid();
    }

    /**
     * @brief Return configuration reference
     */
    const CliConfig &config_ref() const
    {
      if (config == nullptr)
      {
        throw std::runtime_error("CliContext: config is null");
      }

      return *config;
    }

    /**
     * @brief Return command registry reference
     */
    command::CommandRegistry &registry_ref() const
    {
      if (registry == nullptr)
      {
        throw std::runtime_error("CliContext: registry is null");
      }

      return *registry;
    }
  };

} // namespace softadastra::cli::core

#endif
