/*
 * ArgParser.hpp
 */

#ifndef SOFTADASTRA_CLI_ARG_PARSER_HPP
#define SOFTADASTRA_CLI_ARG_PARSER_HPP

#include <string>

#include <softadastra/cli/parser/CommandLine.hpp>
#include <softadastra/cli/parser/ParsedCommand.hpp>

namespace softadastra::cli::parser
{
  /**
   * @brief Converts a tokenized command line into a ParsedCommand
   *
   * Responsibilities:
   * - extract command name
   * - separate positional arguments
   * - parse options (--key, --key=value, --key value)
   */
  class ArgParser
  {
  public:
    /**
     * @brief Parse a command line into a structured command
     */
    static ParsedCommand parse(const CommandLine &cmdline);

  private:
    static bool is_option(const std::string &token);
    static std::string normalize_key(const std::string &token);
  };

} // namespace softadastra::cli::parser

#endif
