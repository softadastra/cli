/**
 *
 *  @file OptionValue.hpp
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

#ifndef SOFTADASTRA_CLI_OPTION_VALUE_HPP
#define SOFTADASTRA_CLI_OPTION_VALUE_HPP

#include <cstdint>
#include <string>
#include <string_view>
#include <variant>

namespace softadastra::cli::types
{
  /**
   * @brief Typed value parsed from a CLI option.
   *
   * OptionValue is used by the parser and command handlers to represent
   * normalized command-line values.
   *
   * Supported values:
   * - std::monostate: option has no explicit value
   * - bool: boolean flag
   * - std::int64_t: integer value
   * - double: floating-point value
   * - std::string: text value
   */
  using OptionValue = std::variant<
      std::monostate,
      bool,
      std::int64_t,
      double,
      std::string>;

  /**
   * @brief Returns true when the option does not carry a value.
   */
  [[nodiscard]] inline bool is_empty(
      const OptionValue &value) noexcept
  {
    return std::holds_alternative<std::monostate>(value);
  }

  /**
   * @brief Returns true when the option contains a boolean value.
   */
  [[nodiscard]] inline bool is_bool(
      const OptionValue &value) noexcept
  {
    return std::holds_alternative<bool>(value);
  }

  /**
   * @brief Returns true when the option contains an integer value.
   */
  [[nodiscard]] inline bool is_integer(
      const OptionValue &value) noexcept
  {
    return std::holds_alternative<std::int64_t>(value);
  }

  /**
   * @brief Returns true when the option contains a floating-point value.
   */
  [[nodiscard]] inline bool is_double(
      const OptionValue &value) noexcept
  {
    return std::holds_alternative<double>(value);
  }

  /**
   * @brief Returns true when the option contains a string value.
   */
  [[nodiscard]] inline bool is_string(
      const OptionValue &value) noexcept
  {
    return std::holds_alternative<std::string>(value);
  }

  /**
   * @brief Returns the semantic type name of an option value.
   */
  [[nodiscard]] inline std::string_view option_value_type(
      const OptionValue &value) noexcept
  {
    if (is_empty(value))
    {
      return "empty";
    }

    if (is_bool(value))
    {
      return "bool";
    }

    if (is_integer(value))
    {
      return "integer";
    }

    if (is_double(value))
    {
      return "double";
    }

    if (is_string(value))
    {
      return "string";
    }

    return "unknown";
  }

} // namespace softadastra::cli::types

#endif // SOFTADASTRA_CLI_OPTION_VALUE_HPP
