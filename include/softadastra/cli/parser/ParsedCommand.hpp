/*
 * ParsedCommand.hpp
 */

#ifndef SOFTADASTRA_CLI_PARSED_COMMAND_HPP
#define SOFTADASTRA_CLI_PARSED_COMMAND_HPP

#include <string>
#include <unordered_map>
#include <vector>

#include <softadastra/cli/types/OptionValue.hpp>

namespace softadastra::cli::parser
{
  namespace types = softadastra::cli::types;

  /**
   * @brief Result of CLI parsing
   *
   * Represents a fully parsed command line:
   * - command name
   * - positional arguments
   * - options (flags + key/value)
   */
  struct ParsedCommand
  {
    /**
     * Command name (e.g. "run", "build")
     */
    std::string name;

    /**
     * Positional arguments
     */
    std::vector<std::string> args;

    /**
     * Options map:
     *   --flag           -> bool(true)
     *   --key=value      -> value
     *   --key value      -> value
     */
    std::unordered_map<std::string, types::OptionValue> options;

    /**
     * @brief Check if a command is present
     */
    bool valid() const noexcept
    {
      return !name.empty();
    }

    /**
     * @brief Check if an option exists
     */
    bool has_option(const std::string &key) const
    {
      return options.find(key) != options.end();
    }

    /**
     * @brief Get option value (nullptr if not found)
     */
    const types::OptionValue *get_option(const std::string &key) const
    {
      auto it = options.find(key);
      if (it == options.end())
      {
        return nullptr;
      }
      return &it->second;
    }
  };

} // namespace softadastra::cli::parser

#endif
