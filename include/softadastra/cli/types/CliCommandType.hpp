/*
 * CliCommandType.hpp
 */

#ifndef SOFTADASTRA_CLI_COMMAND_TYPE_HPP
#define SOFTADASTRA_CLI_COMMAND_TYPE_HPP

#include <cstdint>

namespace softadastra::cli::types
{
  /**
   * @brief Type/category of a CLI command
   *
   * Used to classify commands for routing, help display,
   * or execution strategy.
   */
  enum class CliCommandType : std::uint8_t
  {
    Unknown = 0,

    // Built-in CLI commands
    Builtin,

    // User-defined or application commands
    Custom,

    // Informational commands (help, version, status)
    Info,

    // System-level commands (exit, clear, etc.)
    System
  };

} // namespace softadastra::cli::types

#endif
