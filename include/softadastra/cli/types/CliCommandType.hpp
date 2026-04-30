/**
 *
 *  @file CliCommandType.hpp
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

#ifndef SOFTADASTRA_CLI_COMMAND_TYPE_HPP
#define SOFTADASTRA_CLI_COMMAND_TYPE_HPP

#include <cstdint>
#include <string_view>

namespace softadastra::cli::types
{
  /**
   * @brief Classifies the semantic type of a CLI command.
   *
   * CliCommandType identifies how a command should be grouped, displayed,
   * routed, documented, or handled by higher-level CLI components.
   */
  enum class CliCommandType : std::uint8_t
  {
    /**
     * @brief Unknown or unclassified command.
     */
    Unknown = 0,

    /**
     * @brief Built-in command provided by the CLI module.
     */
    Builtin,

    /**
     * @brief Application-specific command registered by a consumer.
     */
    Custom,

    /**
     * @brief Informational command that reads or displays state.
     */
    Info,

    /**
     * @brief System-level command that controls the CLI session.
     */
    System,

    /**
     * @brief Diagnostic command used for debugging or inspection.
     */
    Diagnostic,

    /**
     * @brief Administrative command that mutates configuration or state.
     */
    Admin
  };

  /**
   * @brief Converts a command type to a stable string representation.
   *
   * @param type Command type.
   * @return String representation.
   */
  [[nodiscard]] constexpr std::string_view to_string(
      CliCommandType type) noexcept
  {
    switch (type)
    {
    case CliCommandType::Builtin:
      return "builtin";

    case CliCommandType::Custom:
      return "custom";

    case CliCommandType::Info:
      return "info";

    case CliCommandType::System:
      return "system";

    case CliCommandType::Diagnostic:
      return "diagnostic";

    case CliCommandType::Admin:
      return "admin";

    case CliCommandType::Unknown:
    default:
      return "unknown";
    }
  }

  /**
   * @brief Returns true when the command type is known.
   *
   * @param type Command type.
   * @return true if the type is not Unknown.
   */
  [[nodiscard]] constexpr bool is_known(
      CliCommandType type) noexcept
  {
    return type != CliCommandType::Unknown;
  }

  /**
   * @brief Returns true when the command type may change application state.
   *
   * @param type Command type.
   * @return true for mutating command categories.
   */
  [[nodiscard]] constexpr bool is_mutating(
      CliCommandType type) noexcept
  {
    return type == CliCommandType::Custom ||
           type == CliCommandType::System ||
           type == CliCommandType::Admin;
  }

} // namespace softadastra::cli::types

#endif // SOFTADASTRA_CLI_COMMAND_TYPE_HPP
