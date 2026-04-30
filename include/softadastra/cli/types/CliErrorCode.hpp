/**
 *
 *  @file CliErrorCode.hpp
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

#ifndef SOFTADASTRA_CLI_ERROR_CODE_HPP
#define SOFTADASTRA_CLI_ERROR_CODE_HPP

#include <cstdint>
#include <string_view>

namespace softadastra::cli::types
{
  /**
   * @brief Error codes returned by CLI operations.
   *
   * CliErrorCode provides a stable and explicit contract for:
   * - command handlers
   * - CLI engine
   * - exit codes
   * - logs and diagnostics
   *
   * Values are intentionally grouped by category.
   */
  enum class CliErrorCode : std::uint16_t
  {
    /**
     * @brief No error occurred.
     */
    None = 0,

    // ---------------------------
    // Generic errors
    // ---------------------------

    /**
     * @brief Unknown or unexpected error.
     */
    UnknownError,

    /**
     * @brief Invalid internal state.
     */
    InvalidState,

    /**
     * @brief Component not initialized.
     */
    NotInitialized,

    // ---------------------------
    // Parsing errors
    // ---------------------------

    /**
     * @brief Failed to parse input.
     */
    ParseError,

    /**
     * @brief Command is not recognized.
     */
    UnknownCommand,

    /**
     * @brief Invalid argument values.
     */
    InvalidArguments,

    /**
     * @brief Required argument missing.
     */
    MissingArgument,

    /**
     * @brief Too many arguments provided.
     */
    TooManyArguments,

    // ---------------------------
    // Execution errors
    // ---------------------------

    /**
     * @brief Command execution failed.
     */
    CommandExecutionFailed,

    /**
     * @brief Command not found in registry.
     */
    CommandNotFound,

    /**
     * @brief Operation not allowed.
     */
    PermissionDenied,

    // ---------------------------
    // I/O errors
    // ---------------------------

    /**
     * @brief Input read failure.
     */
    InputError,

    /**
     * @brief Output write failure.
     */
    OutputError,

    // ---------------------------
    // System errors
    // ---------------------------

    /**
     * @brief Internal unrecoverable error.
     */
    InternalError,

    /**
     * @brief Feature not implemented.
     */
    NotImplemented
  };

  /**
   * @brief Converts an error code to a stable string.
   */
  [[nodiscard]] constexpr std::string_view to_string(
      CliErrorCode code) noexcept
  {
    switch (code)
    {
    case CliErrorCode::None:
      return "none";

    case CliErrorCode::UnknownError:
      return "unknown_error";

    case CliErrorCode::InvalidState:
      return "invalid_state";

    case CliErrorCode::NotInitialized:
      return "not_initialized";

    case CliErrorCode::ParseError:
      return "parse_error";

    case CliErrorCode::UnknownCommand:
      return "unknown_command";

    case CliErrorCode::InvalidArguments:
      return "invalid_arguments";

    case CliErrorCode::MissingArgument:
      return "missing_argument";

    case CliErrorCode::TooManyArguments:
      return "too_many_arguments";

    case CliErrorCode::CommandExecutionFailed:
      return "command_execution_failed";

    case CliErrorCode::CommandNotFound:
      return "command_not_found";

    case CliErrorCode::PermissionDenied:
      return "permission_denied";

    case CliErrorCode::InputError:
      return "input_error";

    case CliErrorCode::OutputError:
      return "output_error";

    case CliErrorCode::InternalError:
      return "internal_error";

    case CliErrorCode::NotImplemented:
      return "not_implemented";

    default:
      return "unknown";
    }
  }

  /**
   * @brief Returns true if the error represents success.
   */
  [[nodiscard]] constexpr bool is_success(
      CliErrorCode code) noexcept
  {
    return code == CliErrorCode::None;
  }

  /**
   * @brief Returns true if the error is user-related (input).
   */
  [[nodiscard]] constexpr bool is_user_error(
      CliErrorCode code) noexcept
  {
    return code == CliErrorCode::ParseError ||
           code == CliErrorCode::UnknownCommand ||
           code == CliErrorCode::InvalidArguments ||
           code == CliErrorCode::MissingArgument ||
           code == CliErrorCode::TooManyArguments;
  }

  /**
   * @brief Returns true if the error is system-related.
   */
  [[nodiscard]] constexpr bool is_system_error(
      CliErrorCode code) noexcept
  {
    return code == CliErrorCode::InternalError ||
           code == CliErrorCode::NotImplemented ||
           code == CliErrorCode::InvalidState ||
           code == CliErrorCode::NotInitialized;
  }

} // namespace softadastra::cli::types

#endif // SOFTADASTRA_CLI_ERROR_CODE_HPP
