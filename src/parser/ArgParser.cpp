/*
 * ArgParser.cpp
 */

#include <cctype>
#include <cstdlib>
#include <string>
#include <string_view>

#include <softadastra/cli/parser/ArgParser.hpp>

namespace softadastra::cli::parser
{
  namespace
  {
    bool parse_bool(
        std::string_view value,
        bool &out)
    {
      if (value == "true" ||
          value == "1" ||
          value == "yes" ||
          value == "on")
      {
        out = true;
        return true;
      }

      if (value == "false" ||
          value == "0" ||
          value == "no" ||
          value == "off")
      {
        out = false;
        return true;
      }

      return false;
    }

    bool looks_like_integer(std::string_view value)
    {
      if (value.empty())
      {
        return false;
      }

      std::size_t index = 0;

      if (value[0] == '-' || value[0] == '+')
      {
        if (value.size() == 1)
        {
          return false;
        }

        index = 1;
      }

      for (; index < value.size(); ++index)
      {
        if (!std::isdigit(static_cast<unsigned char>(value[index])))
        {
          return false;
        }
      }

      return true;
    }

    bool looks_like_double(std::string_view value)
    {
      if (value.empty())
      {
        return false;
      }

      bool has_digit = false;
      bool has_dot = false;

      std::size_t index = 0;

      if (value[0] == '-' || value[0] == '+')
      {
        if (value.size() == 1)
        {
          return false;
        }

        index = 1;
      }

      for (; index < value.size(); ++index)
      {
        const unsigned char c =
            static_cast<unsigned char>(value[index]);

        if (std::isdigit(c))
        {
          has_digit = true;
          continue;
        }

        if (c == '.' && !has_dot)
        {
          has_dot = true;
          continue;
        }

        return false;
      }

      return has_digit && has_dot;
    }

    types::OptionValue parse_option_value(std::string_view value)
    {
      bool bool_value = false;

      if (parse_bool(value, bool_value))
      {
        return bool_value;
      }

      const std::string raw_value{value};

      if (looks_like_integer(value))
      {
        return static_cast<std::int64_t>(
            std::strtoll(raw_value.c_str(), nullptr, 10));
      }

      if (looks_like_double(value))
      {
        return std::strtod(raw_value.c_str(), nullptr);
      }

      return raw_value;
    }
  }

  ParsedCommand ArgParser::parse(
      const CommandLine &cmdline)
  {
    ParsedCommand result;

    if (cmdline.empty())
    {
      return result;
    }

    result.name = cmdline.command();

    const auto tokens = cmdline.arguments();

    for (std::size_t i = 0; i < tokens.size(); ++i)
    {
      const std::string &token = tokens[i];

      if (!is_option(token))
      {
        result.args.push_back(token);
        continue;
      }

      const std::string key = normalize_key(token);

      if (key.empty())
      {
        continue;
      }

      if (has_inline_value(token))
      {
        result.options[key] =
            parse_option_value(inline_value(token));
        continue;
      }

      if ((i + 1) < tokens.size() && !is_option(tokens[i + 1]))
      {
        result.options[key] =
            parse_option_value(tokens[i + 1]);
        ++i;
        continue;
      }

      result.options[key] = true;
    }

    return result;
  }

  bool ArgParser::is_option(
      std::string_view token) noexcept
  {
    return token.size() > 1 &&
           token[0] == '-' &&
           token != "-";
  }

  bool ArgParser::has_inline_value(
      std::string_view token) noexcept
  {
    return token.find('=') != std::string_view::npos;
  }

  std::string ArgParser::normalize_key(
      std::string_view token)
  {
    if (token.rfind("--", 0) == 0)
    {
      token.remove_prefix(2);
    }
    else if (token.rfind("-", 0) == 0)
    {
      token.remove_prefix(1);
    }

    const std::size_t equal_pos = token.find('=');

    if (equal_pos != std::string_view::npos)
    {
      token = token.substr(0, equal_pos);
    }

    return std::string{token};
  }

  std::string ArgParser::inline_value(
      std::string_view token)
  {
    const std::size_t equal_pos = token.find('=');

    if (equal_pos == std::string_view::npos)
    {
      return {};
    }

    return std::string{token.substr(equal_pos + 1)};
  }

} // namespace softadastra::cli::parser
