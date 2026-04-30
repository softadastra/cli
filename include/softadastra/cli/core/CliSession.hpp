/**
 *
 *  @file CliSession.hpp
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

#ifndef SOFTADASTRA_CLI_SESSION_HPP
#define SOFTADASTRA_CLI_SESSION_HPP

#include <cstdint>
#include <string>
#include <utility>

#include <softadastra/cli/types/CliStatus.hpp>

namespace softadastra::cli::core
{
  namespace types = softadastra::cli::types;

  /**
   * @brief Represents the runtime state of one CLI session.
   *
   * CliSession tracks the lifecycle of a CLI execution, whether it is an
   * interactive session or a single-command run.
   *
   * It is responsible for:
   * - current lifecycle status
   * - running flag
   * - shutdown request state
   * - last executed command
   * - command execution count
   *
   * The class does not parse input and does not execute commands directly.
   */
  class CliSession
  {
  public:
    /**
     * @brief Creates an idle CLI session.
     */
    CliSession() = default;

    /**
     * @brief Sets the current session status.
     *
     * @param status New CLI status.
     */
    void set_status(types::CliStatus status) noexcept
    {
      status_ = status;
    }

    /**
     * @brief Returns the current session status.
     *
     * @return Current CLI status.
     */
    [[nodiscard]] types::CliStatus status() const noexcept
    {
      return status_;
    }

    /**
     * @brief Starts the CLI session.
     *
     * The session becomes active and enters the Running state.
     */
    void start() noexcept
    {
      running_ = true;
      stop_requested_ = false;
      status_ = types::CliStatus::Running;
    }

    /**
     * @brief Requests the CLI session to stop.
     *
     * This is useful for graceful shutdown in interactive loops.
     */
    void request_stop() noexcept
    {
      stop_requested_ = true;
      status_ = types::CliStatus::Stopping;
    }

    /**
     * @brief Stops the CLI session immediately.
     *
     * The session becomes inactive and enters the Stopped state.
     */
    void stop() noexcept
    {
      running_ = false;
      stop_requested_ = true;
      status_ = types::CliStatus::Stopped;
    }

    /**
     * @brief Marks the session as failed.
     */
    void fail() noexcept
    {
      running_ = false;
      status_ = types::CliStatus::Failed;
    }

    /**
     * @brief Returns true when the session is running.
     *
     * @return true if the CLI session is active.
     */
    [[nodiscard]] bool running() const noexcept
    {
      return running_;
    }

    /**
     * @brief Returns true when a graceful stop was requested.
     *
     * @return true if the session should stop.
     */
    [[nodiscard]] bool stop_requested() const noexcept
    {
      return stop_requested_;
    }

    /**
     * @brief Stores the last executed command name.
     *
     * @param value Command name.
     */
    void set_last_command(std::string value)
    {
      last_command_ = std::move(value);
    }

    /**
     * @brief Returns the last executed command name.
     *
     * @return Last command name.
     */
    [[nodiscard]] const std::string &last_command() const noexcept
    {
      return last_command_;
    }

    /**
     * @brief Increments the executed command counter.
     */
    void increment_command_count() noexcept
    {
      ++command_count_;
    }

    /**
     * @brief Returns the number of executed commands in this session.
     *
     * @return Executed command count.
     */
    [[nodiscard]] std::uint64_t command_count() const noexcept
    {
      return command_count_;
    }

    /**
     * @brief Resets the session to its initial idle state.
     */
    void reset()
    {
      status_ = types::CliStatus::Idle;
      running_ = false;
      stop_requested_ = false;
      last_command_.clear();
      command_count_ = 0;
    }

  private:
    types::CliStatus status_{types::CliStatus::Idle};
    bool running_{false};
    bool stop_requested_{false};
    std::string last_command_{};
    std::uint64_t command_count_{0};
  };

} // namespace softadastra::cli::core

#endif // SOFTADASTRA_CLI_SESSION_HPP
