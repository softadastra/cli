/*
 * OptionValue.hpp
 */

#ifndef SOFTADASTRA_CLI_OPTION_VALUE_HPP
#define SOFTADASTRA_CLI_OPTION_VALUE_HPP

#include <cstdint>
#include <string>
#include <variant>

namespace softadastra::cli::types
{
  /**
   * @brief Value of a CLI option
   *
   * Represents a typed value parsed from command-line arguments.
   */
  using OptionValue = std::variant<
      std::monostate, // no value (flag)
      bool,           // --flag / --no-flag
      std::int64_t,   // integer values
      double,         // floating point values
      std::string     // string values
      >;

} // namespace softadastra::cli::types

#endif
