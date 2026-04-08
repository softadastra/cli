/*
 * CliConfig.hpp
 */

#ifndef SOFTADASTRA_CLI_CONFIG_HPP
#define SOFTADASTRA_CLI_CONFIG_HPP

#include <string>

namespace softadastra::cli::core
{
  /**
   * @brief Runtime configuration for the CLI module
   */
  struct CliConfig
  {
    /**
     * Application name (e.g. "vix")
     */
    std::string app_name;

    /**
     * Application version (e.g. "2.1.0")
     */
    std::string version{"0.1.0"};

    /**
     * Enable interactive mode (REPL)
     */
    bool interactive{true};

    /**
     * Show banner on startup
     */
    bool show_banner{true};

    /**
     * @brief Check whether config is valid
     */
    bool valid() const noexcept
    {
      return !app_name.empty() &&
             !version.empty();
    }
  };

} // namespace softadastra::cli::core

#endif
