/*
 * Tokenizer.hpp
 */

#ifndef SOFTADASTRA_CLI_TOKENIZER_HPP
#define SOFTADASTRA_CLI_TOKENIZER_HPP

#include <string>
#include <vector>

namespace softadastra::cli::parser
{
  /**
   * @brief Splits a raw command line into tokens
   *
   * Handles:
   * - spaces
   * - quoted strings ("hello world")
   * - basic escaping
   */
  class Tokenizer
  {
  public:
    /**
     * @brief Tokenize a command line string
     */
    static std::vector<std::string> tokenize(const std::string &input);

  private:
    static void push_token(std::vector<std::string> &tokens,
                           std::string &current);
  };

} // namespace softadastra::cli::parser

#endif
