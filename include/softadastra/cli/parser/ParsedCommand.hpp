/**
 *
 *  @file ParsedCommand.hpp
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

#ifndef SOFTADASTRA_CLI_PARSED_COMMAND_HPP
#define SOFTADASTRA_CLI_PARSED_COMMAND_HPP

#include <cstddef>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

#include <softadastra/cli/types/OptionValue.hpp>

namespace softadastra::cli::parser
{
  namespace types = softadastra::cli::types;

  /**
   * @brief Represents the result of parsing a CLI command line.
   *
   * ParsedCommand stores the normalized representation of a command after
   * tokenization and argument parsing.
   *
   * It contains:
   * - command name
   * - positional arguments
   * - parsed options
   *
   * Options are stored without their leading prefixes.
   *
   * Examples:
   * - "--verbose" becomes "verbose" => bool(true)
   * - "--port=8080" becomes "port" => parsed value
   * - "--host localhost" becomes "host" => parsed value
   */
  struct ParsedCommand
  {
    /**
     * @brief Command name.
     *
     * Example: "run", "build", "node", "store-put".
     */
    std::string name{};

    /**
     * @brief Positional command arguments.
     */
    std::vector<std::string> args{};

    /**
     * @brief Parsed options indexed by normalized option name.
     */
    std::unordered_map<std::string, types::OptionValue> options{};

    /**
     * @brief Returns true when a command name is present.
     *
     * @return true if the parsed command is usable.
     */
    [[nodiscard]] bool valid() const noexcept
    {
      return !name.empty();
    }

    /**
     * @brief Returns true when no command name is present.
     *
     * @return true if the parsed command is empty.
     */
    [[nodiscard]] bool empty() const noexcept
    {
      return name.empty() &&
             args.empty() &&
             options.empty();
    }

    /**
     * @brief Returns the number of positional arguments.
     *
     * @return Argument count.
     */
    [[nodiscard]] std::size_t arg_count() const noexcept
    {
      return args.size();
    }

    /**
     * @brief Returns true when the command has positional arguments.
     *
     * @return true if at least one positional argument exists.
     */
    [[nodiscard]] bool has_args() const noexcept
    {
      return !args.empty();
    }

    /**
     * @brief Returns true when an option exists.
     *
     * @param key Normalized option name.
     * @return true if the option is present.
     */
    [[nodiscard]] bool has_option(std::string_view key) const
    {
      return options.find(std::string(key)) != options.end();
    }

    /**
     * @brief Returns a pointer to an option value.
     *
     * @param key Normalized option name.
     * @return Pointer to the option value, or nullptr if missing.
     */
    [[nodiscard]] const types::OptionValue *get_option(
        std::string_view key) const
    {
      const auto it = options.find(std::string(key));

      if (it == options.end())
      {
        return nullptr;
      }

      return &it->second;
    }

    /**
     * @brief Returns true when an option exists and is a boolean true flag.
     *
     * @param key Normalized option name.
     * @return true if the option is present and equals bool(true).
     */
    [[nodiscard]] bool option_enabled(std::string_view key) const
    {
      const auto *value = get_option(key);

      if (value == nullptr)
      {
        return false;
      }

      if (!std::holds_alternative<bool>(*value))
      {
        return false;
      }

      return std::get<bool>(*value);
    }

    /**
     * @brief Returns an option string value or a fallback.
     *
     * @param key Normalized option name.
     * @param fallback Value returned when option is missing or not a string.
     * @return Option string value or fallback.
     */
    [[nodiscard]] std::string option_string_or(
        std::string_view key,
        std::string fallback = {}) const
    {
      const auto *value = get_option(key);

      if (value == nullptr)
      {
        return fallback;
      }

      if (!std::holds_alternative<std::string>(*value))
      {
        return fallback;
      }

      return std::get<std::string>(*value);
    }

    /**
     * @brief Clears the parsed command.
     */
    void clear()
    {
      name.clear();
      args.clear();
      options.clear();
    }
  };

} // namespace softadastra::cli::parser

#endif // SOFTADASTRA_CLI_PARSED_COMMAND_HPP
