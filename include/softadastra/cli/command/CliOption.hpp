/*
 * CliOption.hpp
 */

#ifndef SOFTADASTRA_CLI_OPTION_HPP
#define SOFTADASTRA_CLI_OPTION_HPP

#include <string>
#include <utility>

namespace softadastra::cli::command
{
  /**
   * @brief Declarative description of one CLI option
   */
  struct CliOption
  {
    /**
     * Long option name without leading '--'
     * Example: "help", "port", "host"
     */
    std::string name{};

    /**
     * Short option name without leading '-'
     * Example: "h", "p"
     */
    std::string short_name{};

    /**
     * Human-readable description
     */
    std::string description{};

    /**
     * Value placeholder shown in help
     * Example: "PORT", "HOST"
     */
    std::string value_name{};

    /**
     * Whether the option expects a value
     */
    bool takes_value{false};

    CliOption() = default;

    CliOption(std::string option_name,
              std::string option_short_name,
              std::string option_description,
              std::string option_value_name,
              bool option_takes_value)
        : name(std::move(option_name)),
          short_name(std::move(option_short_name)),
          description(std::move(option_description)),
          value_name(std::move(option_value_name)),
          takes_value(option_takes_value)
    {
    }

    bool valid() const noexcept
    {
      return !name.empty();
    }
  };

} // namespace softadastra::cli::command

#endif
