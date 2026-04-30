/**
 *
 *  @file CommandLine.hpp
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

#ifndef SOFTADASTRA_CLI_COMMAND_LINE_HPP
#define SOFTADASTRA_CLI_COMMAND_LINE_HPP

#include <cstddef>
#include <string>
#include <vector>

namespace softadastra::cli::parser
{
  /**
   * @brief Represents a tokenized CLI command line.
   *
   * CommandLine is an intermediate immutable-style structure between raw user
   * input and a fully parsed command.
   *
   * It stores the normalized token list produced by the tokenizer and exposes
   * safe helpers for accessing:
   * - the command name
   * - positional arguments
   * - raw tokens
   *
   * The first token is treated as the command name. Remaining tokens are
   * treated as arguments or options by higher-level parsers.
   */
  class CommandLine
  {
  public:
    /**
     * @brief Creates an empty command line.
     */
    CommandLine() = default;

    /**
     * @brief Creates a command line from an existing token list.
     *
     * @param tokens Tokenized command-line values.
     */
    explicit CommandLine(std::vector<std::string> tokens);

    /**
     * @brief Returns all tokens.
     *
     * @return Read-only token list.
     */
    [[nodiscard]] const std::vector<std::string> &tokens() const noexcept;

    /**
     * @brief Returns true when no tokens are present.
     *
     * @return true if the command line is empty.
     */
    [[nodiscard]] bool empty() const noexcept;

    /**
     * @brief Returns the number of tokens.
     *
     * @return Token count.
     */
    [[nodiscard]] std::size_t size() const noexcept;

    /**
     * @brief Returns a token by index.
     *
     * Throws std::out_of_range when the index is invalid.
     *
     * @param index Token index.
     * @return Token at the requested index.
     */
    [[nodiscard]] const std::string &at(std::size_t index) const;

    /**
     * @brief Returns the command name.
     *
     * The command name is the first token. If the command line is empty,
     * an empty string is returned.
     *
     * @return Command name.
     */
    [[nodiscard]] std::string command() const;

    /**
     * @brief Returns all arguments after the command name.
     *
     * If the command line has no command, an empty vector is returned.
     *
     * @return Positional and option tokens after the command name.
     */
    [[nodiscard]] std::vector<std::string> arguments() const;

    /**
     * @brief Returns true when the command line contains at least one command.
     *
     * @return true if a command token exists.
     */
    [[nodiscard]] bool has_command() const noexcept
    {
      return !tokens_.empty();
    }

    /**
     * @brief Clears all tokens.
     */
    void clear() noexcept
    {
      tokens_.clear();
    }

  private:
    std::vector<std::string> tokens_{};
  };

} // namespace softadastra::cli::parser

#endif // SOFTADASTRA_CLI_COMMAND_LINE_HPP
