/**
 *
 *  @file ArgParser.hpp
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

#ifndef SOFTADASTRA_CLI_ARG_PARSER_HPP
#define SOFTADASTRA_CLI_ARG_PARSER_HPP

#include <string>
#include <string_view>

#include <softadastra/cli/parser/CommandLine.hpp>
#include <softadastra/cli/parser/ParsedCommand.hpp>

namespace softadastra::cli::parser
{
  /**
   * @brief Converts a tokenized command line into a structured command.
   *
   * ArgParser is the second parsing stage of the CLI module.
   *
   * It receives a CommandLine produced by the tokenizer and builds a
   * ParsedCommand containing:
   * - command name
   * - positional arguments
   * - normalized options
   *
   * Supported option forms:
   * - --flag
   * - --key=value
   * - --key value
   * - -f
   * - -k value
   *
   * Option keys are stored without leading '-' or '--'.
   */
  class ArgParser
  {
  public:
    /**
     * @brief Parses a tokenized command line.
     *
     * @param cmdline Tokenized command line.
     * @return Parsed command.
     */
    [[nodiscard]] static ParsedCommand parse(
        const CommandLine &cmdline);

  private:
    /**
     * @brief Returns true if a token is an option.
     *
     * @param token Token to inspect.
     * @return true when token starts with '-' and is not only "-".
     */
    [[nodiscard]] static bool is_option(
        std::string_view token) noexcept;

    /**
     * @brief Returns true if a token uses the --key=value form.
     *
     * @param token Token to inspect.
     * @return true when token contains an inline assignment.
     */
    [[nodiscard]] static bool has_inline_value(
        std::string_view token) noexcept;

    /**
     * @brief Normalizes an option token into its key name.
     *
     * Removes leading '-' or '--' and strips any inline value suffix.
     *
     * Examples:
     * - "--port=8080" becomes "port"
     * - "--verbose" becomes "verbose"
     * - "-p" becomes "p"
     *
     * @param token Option token.
     * @return Normalized option key.
     */
    [[nodiscard]] static std::string normalize_key(
        std::string_view token);

    /**
     * @brief Extracts the inline value from a --key=value token.
     *
     * @param token Option token.
     * @return Extracted value or empty string when none exists.
     */
    [[nodiscard]] static std::string inline_value(
        std::string_view token);
  };

} // namespace softadastra::cli::parser

#endif // SOFTADASTRA_CLI_ARG_PARSER_HPP
