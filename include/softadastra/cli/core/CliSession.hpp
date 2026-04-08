/*
 * CliSession.hpp
 */

#ifndef SOFTADASTRA_CLI_SESSION_HPP
#define SOFTADASTRA_CLI_SESSION_HPP

#include <string>

#include <softadastra/cli/types/CliStatus.hpp>

namespace softadastra::cli::core
{
  namespace types = softadastra::cli::types;

  /**
   * @brief Represents one CLI session (interactive or single-run)
   */
  class CliSession
  {
  public:
    /**
     * @brief Set current status
     */
    void set_status(types::CliStatus status) noexcept
    {
      status_ = status;
    }

    /**
     * @brief Get current status
     */
    types::CliStatus status() const noexcept
    {
      return status_;
    }

    /**
     * @brief Mark session as running
     */
    void start() noexcept
    {
      running_ = true;
      status_ = types::CliStatus::Running;
    }

    /**
     * @brief Stop session
     */
    void stop() noexcept
    {
      running_ = false;
      status_ = types::CliStatus::Stopped;
    }

    /**
     * @brief Check if session is active
     */
    bool running() const noexcept
    {
      return running_;
    }

    /**
     * @brief Store last executed command name
     */
    void set_last_command(std::string value)
    {
      last_command_ = std::move(value);
    }

    /**
     * @brief Get last executed command name
     */
    const std::string &last_command() const noexcept
    {
      return last_command_;
    }

  private:
    types::CliStatus status_{types::CliStatus::Idle};
    bool running_{false};
    std::string last_command_;
  };

} // namespace softadastra::cli::core

#endif
