/*
 * Tokenizer.cpp
 */

#include <cctype>
#include <cstddef>
#include <utility>

#include <softadastra/cli/parser/Tokenizer.hpp>

namespace softadastra::cli::parser
{
  std::vector<std::string> Tokenizer::tokenize(
      std::string_view input)
  {
    std::vector<std::string> tokens;
    std::string current;

    bool in_quotes = false;
    bool escaping = false;
    char quote_char = '\0';

    for (const char c : input)
    {
      if (escaping)
      {
        current += c;
        escaping = false;
        continue;
      }

      if (c == '\\')
      {
        escaping = true;
        continue;
      }

      if (c == '"' || c == '\'')
      {
        if (!in_quotes)
        {
          in_quotes = true;
          quote_char = c;
          continue;
        }

        if (quote_char == c)
        {
          in_quotes = false;
          quote_char = '\0';
          continue;
        }
      }

      if (std::isspace(static_cast<unsigned char>(c)) && !in_quotes)
      {
        push_token(tokens, current);
        continue;
      }

      current += c;
    }

    if (escaping)
    {
      current += '\\';
    }

    push_token(tokens, current);

    return tokens;
  }

  void Tokenizer::push_token(
      std::vector<std::string> &tokens,
      std::string &current)
  {
    if (current.empty())
    {
      return;
    }

    tokens.push_back(std::move(current));
    current.clear();
  }

} // namespace softadastra::cli::parser
