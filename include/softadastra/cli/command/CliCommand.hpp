/*
 * CliCommand.hpp
 */

#ifndef SOFTADASTRA_CLI_COMMAND_HPP
#define SOFTADASTRA_CLI_COMMAND_HPP

#include <string>
#include <utility>
#include <vector>

#include <softadastra/cli/types/CliCommandType.hpp>

namespace softadastra::cli::command
{
  namespace types = softadastra::cli::types;

  /**
   * @brief Declarative description of one CLI command
   */
  struct CliCommand
  {
    /**
     * Command name used on the command line
     */
    std::string name{};

    /**
     * Short human-readable description
     */
    std::string description{};

    /**
     * Usage string shown in help output
     */
    std::string usage{};

    /**
     * Command category
     */
    types::CliCommandType type{types::CliCommandType::Unknown};

    /**
     * Optional aliases
     */
    std::vector<std::string> aliases{};

    CliCommand() = default;

    CliCommand(std::string command_name,
               std::string command_description,
               std::string command_usage,
               types::CliCommandType command_type,
               std::vector<std::string> command_aliases = {})
        : name(std::move(command_name)),
          description(std::move(command_description)),
          usage(std::move(command_usage)),
          type(command_type),
          aliases(std::move(command_aliases))
    {
    }

    /**
     * @brief Check whether this command definition is usable
     */
    bool valid() const noexcept
    {
      return !name.empty();
    }

    /**
     * @brief Return true if the given value matches this command
     */
    bool matches(const std::string &value) const
    {
      if (name == value)
      {
        return true;
      }

      for (const auto &alias : aliases)
      {
        if (alias == value)
        {
          return true;
        }
      }

      return false;
    }
  };

} // namespace softadastra::cli::command

#endif
