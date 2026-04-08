/*
 * CliService.hpp
 */

#ifndef SOFTADASTRA_CLI_SERVICE_HPP
#define SOFTADASTRA_CLI_SERVICE_HPP

#include <string>

#include <softadastra/cli/CliOptions.hpp>
#include <softadastra/cli/core/CliConfig.hpp>
#include <softadastra/cli/core/CliContext.hpp>
#include <softadastra/cli/engine/CliEngine.hpp>

namespace softadastra::cli
{
  namespace cli_core = softadastra::cli::core;
  namespace cli_engine = softadastra::cli::engine;

  /**
   * @brief High-level CLI service
   *
   * Entry point for:
   * - starting CLI
   * - running commands
   * - interactive loop (REPL)
   */
  class CliService
  {
  public:
    explicit CliService(const cli_core::CliConfig &config);

    /**
     * @brief Run CLI with given options
     */
    int run(const CliOptions &options);

    void register_command(const softadastra::cli::command::CliCommand &command,
                          std::shared_ptr<softadastra::cli::command::ICommandHandler> handler);

  private:
    int run_interactive();
    int run_single(const std::string &command);

  private:
    cli_core::CliConfig config_;
    softadastra::cli::command::CommandRegistry registry_;
    cli_core::CliContext context_;
    cli_engine::CliEngine engine_;
  };

} // namespace softadastra::cli

#endif
