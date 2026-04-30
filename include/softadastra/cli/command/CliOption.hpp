/**
 *
 *  @file CliOption.hpp
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

#ifndef SOFTADASTRA_CLI_OPTION_HPP
#define SOFTADASTRA_CLI_OPTION_HPP

#include <string>
#include <utility>

namespace softadastra::cli::command
{
  /**
   * @brief Declarative metadata for one CLI option.
   *
   * CliOption describes an option accepted by a command.
   *
   * It is used by:
   * - command definitions
   * - argument parsers
   * - help formatters
   * - validation logic
   *
   * Names are stored without their CLI prefixes:
   * - name: "port" for "--port"
   * - short_name: "p" for "-p"
   */
  struct CliOption
  {
    /**
     * @brief Long option name without the leading "--".
     *
     * Example: "help", "port", "host".
     */
    std::string name{};

    /**
     * @brief Short option name without the leading "-".
     *
     * Example: "h", "p".
     */
    std::string short_name{};

    /**
     * @brief Human-readable option description.
     */
    std::string description{};

    /**
     * @brief Value placeholder displayed in help output.
     *
     * Example: "PORT", "HOST", "PATH".
     */
    std::string value_name{};

    /**
     * @brief Whether the option requires a value.
     */
    bool takes_value{false};

    /**
     * @brief Whether the option is required by the command.
     */
    bool required{false};

    /**
     * @brief Creates an empty option declaration.
     */
    CliOption() = default;

    /**
     * @brief Creates a CLI option declaration.
     *
     * @param option_name Long option name.
     * @param option_short_name Short option name.
     * @param option_description Human-readable description.
     * @param option_value_name Value placeholder.
     * @param option_takes_value Whether the option expects a value.
     * @param option_required Whether the option is required.
     */
    CliOption(
        std::string option_name,
        std::string option_short_name,
        std::string option_description,
        std::string option_value_name,
        bool option_takes_value,
        bool option_required = false)
        : name(std::move(option_name)),
          short_name(std::move(option_short_name)),
          description(std::move(option_description)),
          value_name(std::move(option_value_name)),
          takes_value(option_takes_value),
          required(option_required)
    {
    }

    /**
     * @brief Returns true if the option declaration is valid.
     *
     * A valid option must have a long name. If the option takes a value,
     * the value placeholder should also be present for clean help output.
     *
     * @return true when the option declaration is usable.
     */
    [[nodiscard]] bool valid() const noexcept
    {
      if (name.empty())
      {
        return false;
      }

      if (takes_value && value_name.empty())
      {
        return false;
      }

      return true;
    }

    /**
     * @brief Returns true if this option has a short alias.
     *
     * @return true when short_name is not empty.
     */
    [[nodiscard]] bool has_short_name() const noexcept
    {
      return !short_name.empty();
    }

    /**
     * @brief Returns true if this option has a description.
     *
     * @return true when description is not empty.
     */
    [[nodiscard]] bool has_description() const noexcept
    {
      return !description.empty();
    }

    /**
     * @brief Returns true if this option has a value placeholder.
     *
     * @return true when value_name is not empty.
     */
    [[nodiscard]] bool has_value_name() const noexcept
    {
      return !value_name.empty();
    }
  };

} // namespace softadastra::cli::command

#endif // SOFTADASTRA_CLI_OPTION_HPP
