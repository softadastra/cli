/**
 *
 *  @file CliStatus.hpp
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

#ifndef SOFTADASTRA_CLI_STATUS_HPP
#define SOFTADASTRA_CLI_STATUS_HPP

#include <cstdint>
#include <string_view>

namespace softadastra::cli::types
{
  /**
   * @brief Represents the lifecycle state of the CLI engine.
   *
   * CliStatus is used to:
   * - track runtime state transitions
   * - drive CLI loops
   * - expose observability hooks
   * - control shutdown and error propagation
   *
   * The state machine is intentionally simple and deterministic.
   */
  enum class CliStatus : std::uint8_t
  {
    /**
     * @brief Initial idle state before startup.
     */
    Idle = 0,

    /**
     * @brief CLI is initializing resources.
     */
    Starting,

    /**
     * @brief CLI is running and ready.
     */
    Running,

    /**
     * @brief CLI is waiting for user input.
     */
    WaitingInput,

    /**
     * @brief CLI is executing a command.
     */
    ExecutingCommand,

    /**
     * @brief CLI is shutting down.
     */
    Stopping,

    /**
     * @brief CLI has stopped cleanly.
     */
    Stopped,

    /**
     * @brief CLI encountered a failure.
     */
    Failed
  };

  /**
   * @brief Converts a status to a stable string representation.
   */
  [[nodiscard]] constexpr std::string_view to_string(
      CliStatus status) noexcept
  {
    switch (status)
    {
    case CliStatus::Idle:
      return "idle";

    case CliStatus::Starting:
      return "starting";

    case CliStatus::Running:
      return "running";

    case CliStatus::WaitingInput:
      return "waiting_input";

    case CliStatus::ExecutingCommand:
      return "executing_command";

    case CliStatus::Stopping:
      return "stopping";

    case CliStatus::Stopped:
      return "stopped";

    case CliStatus::Failed:
      return "failed";

    default:
      return "unknown";
    }
  }

  /**
   * @brief Returns true if the CLI is active.
   */
  [[nodiscard]] constexpr bool is_active(
      CliStatus status) noexcept
  {
    return status == CliStatus::Running ||
           status == CliStatus::WaitingInput ||
           status == CliStatus::ExecutingCommand;
  }

  /**
   * @brief Returns true if the CLI is in a terminal state.
   */
  [[nodiscard]] constexpr bool is_terminal(
      CliStatus status) noexcept
  {
    return status == CliStatus::Stopped ||
           status == CliStatus::Failed;
  }

  /**
   * @brief Returns true if the CLI is transitioning.
   */
  [[nodiscard]] constexpr bool is_transitioning(
      CliStatus status) noexcept
  {
    return status == CliStatus::Starting ||
           status == CliStatus::Stopping;
  }

} // namespace softadastra::cli::types

#endif // SOFTADASTRA_CLI_STATUS_HPP
