/**
 *
 *  @file Tokenizer.hpp
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

#ifndef SOFTADASTRA_CLI_TOKENIZER_HPP
#define SOFTADASTRA_CLI_TOKENIZER_HPP

#include <string>
#include <string_view>
#include <vector>

namespace softadastra::cli::parser
{
  /**
   * @brief Splits raw command-line input into tokens.
   *
   * Tokenizer is the first parsing stage of the CLI module.
   *
   * It converts raw text into normalized tokens while preserving quoted values.
   *
   * It handles:
   * - whitespace-separated tokens
   * - double-quoted strings
   * - single-quoted strings
   * - basic escaped characters
   *
   * Example:
   * @code
   * store-put name "Softadastra Runtime"
   * @endcode
   *
   * Produces:
   * @code
   * ["store-put", "name", "Softadastra Runtime"]
   * @endcode
   */
  class Tokenizer
  {
  public:
    /**
     * @brief Tokenizes a raw command-line string.
     *
     * @param input Raw command-line input.
     * @return Tokenized values.
     */
    [[nodiscard]] static std::vector<std::string> tokenize(
        std::string_view input);

  private:
    /**
     * @brief Pushes the current token if it is not empty.
     *
     * @param tokens Output token list.
     * @param current Current token buffer.
     */
    static void push_token(
        std::vector<std::string> &tokens,
        std::string &current);
  };

} // namespace softadastra::cli::parser

#endif // SOFTADASTRA_CLI_TOKENIZER_HPP
