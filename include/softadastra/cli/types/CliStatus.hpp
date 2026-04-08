/*
 * CliStatus.hpp
 */

#ifndef SOFTADASTRA_CLI_STATUS_HPP
#define SOFTADASTRA_CLI_STATUS_HPP

#include <cstdint>

namespace softadastra::cli::types
{
  /**
   * @brief Runtime status of the CLI engine
   */
  enum class CliStatus : std::uint8_t
  {
    Idle = 0,
    Starting,
    Running,
    WaitingInput,
    ExecutingCommand,
    Stopping,
    Stopped,
    Failed
  };

} // namespace softadastra::cli::types

#endif
