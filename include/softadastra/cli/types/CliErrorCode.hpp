/*
 * CliErrorCode.hpp
 */

#ifndef SOFTADASTRA_CLI_ERROR_CODE_HPP
#define SOFTADASTRA_CLI_ERROR_CODE_HPP

#include <cstdint>

namespace softadastra::cli::types
{
  /**
   * @brief Error codes for CLI operations
   */
  enum class CliErrorCode : std::uint16_t
  {
    None = 0,

    // Generic errors
    UnknownError,
    InvalidState,
    NotInitialized,

    // Parsing errors
    ParseError,
    UnknownCommand,
    InvalidArguments,
    MissingArgument,
    TooManyArguments,

    // Execution errors
    CommandExecutionFailed,
    CommandNotFound,
    PermissionDenied,

    // I/O errors
    InputError,
    OutputError,

    // System errors
    InternalError,
    NotImplemented
  };

} // namespace softadastra::cli::types

#endif
