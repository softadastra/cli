/*
 * Tokenizer.cpp
 */

#include <softadastra/cli/parser/Tokenizer.hpp>

namespace softadastra::cli::parser
{
  std::vector<std::string> Tokenizer::tokenize(const std::string &input)
  {
    std::vector<std::string> tokens;
    std::string current;

    bool in_quotes = false;
    char quote_char = '\0';

    for (std::size_t i = 0; i < input.size(); ++i)
    {
      const char c = input[i];

      // Handle quotes
      if ((c == '"' || c == '\''))
      {
        if (!in_quotes)
        {
          in_quotes = true;
          quote_char = c;
        }
        else if (quote_char == c)
        {
          in_quotes = false;
          quote_char = '\0';
        }
        else
        {
          current += c;
        }
        continue;
      }

      // Handle escape character
      if (c == '\\')
      {
        if (i + 1 < input.size())
        {
          current += input[i + 1];
          ++i;
        }
        continue;
      }

      // Split on space (only if not in quotes)
      if (std::isspace(static_cast<unsigned char>(c)) && !in_quotes)
      {
        push_token(tokens, current);
        continue;
      }

      current += c;
    }

    // Push last token
    push_token(tokens, current);

    return tokens;
  }

  void Tokenizer::push_token(std::vector<std::string> &tokens,
                             std::string &current)
  {
    if (!current.empty())
    {
      tokens.push_back(std::move(current));
      current.clear();
    }
  }

} // namespace softadastra::cli::parser
