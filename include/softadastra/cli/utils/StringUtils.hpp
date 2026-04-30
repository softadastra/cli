/**
 *
 *  @file StringUtils.hpp
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

#ifndef SOFTADASTRA_CLI_STRING_UTILS_HPP
#define SOFTADASTRA_CLI_STRING_UTILS_HPP

#include <algorithm>
#include <cctype>
#include <string>
#include <string_view>
#include <vector>

namespace softadastra::cli::utils
{
  /**
   * @brief Provides small string helpers used by the CLI module.
   *
   * StringUtils centralizes common string operations needed by parsers,
   * formatters, command handlers, and user-facing CLI output.
   *
   * All helpers are stateless and allocation-conscious where possible.
   */
  class StringUtils
  {
  public:
    /**
     * @brief Removes whitespace from both ends of a string.
     *
     * @param value Input string.
     * @return Trimmed string.
     */
    [[nodiscard]] static std::string trim(std::string_view value)
    {
      std::size_t begin = 0;
      std::size_t end = value.size();

      while (begin < end &&
             std::isspace(static_cast<unsigned char>(value[begin])))
      {
        ++begin;
      }

      while (end > begin &&
             std::isspace(static_cast<unsigned char>(value[end - 1])))
      {
        --end;
      }

      return std::string(value.substr(begin, end - begin));
    }

    /**
     * @brief Converts a string to lowercase.
     *
     * @param value Input string.
     * @return Lowercase string.
     */
    [[nodiscard]] static std::string to_lower(std::string_view value)
    {
      std::string result{value};

      std::transform(
          result.begin(),
          result.end(),
          result.begin(),
          [](unsigned char c)
          {
            return static_cast<char>(std::tolower(c));
          });

      return result;
    }

    /**
     * @brief Returns true if a string starts with a prefix.
     *
     * @param value Input string.
     * @param prefix Prefix to match.
     * @return true when value starts with prefix.
     */
    [[nodiscard]] static bool starts_with(
        std::string_view value,
        std::string_view prefix) noexcept
    {
      return value.size() >= prefix.size() &&
             value.substr(0, prefix.size()) == prefix;
    }

    /**
     * @brief Returns true if a string ends with a suffix.
     *
     * @param value Input string.
     * @param suffix Suffix to match.
     * @return true when value ends with suffix.
     */
    [[nodiscard]] static bool ends_with(
        std::string_view value,
        std::string_view suffix) noexcept
    {
      return value.size() >= suffix.size() &&
             value.substr(value.size() - suffix.size()) == suffix;
    }

    /**
     * @brief Returns true if the string is empty after trimming.
     *
     * @param value Input string.
     * @return true when trimmed value is empty.
     */
    [[nodiscard]] static bool is_blank(std::string_view value)
    {
      return trim(value).empty();
    }

    /**
     * @brief Splits a string by a single-character delimiter.
     *
     * Empty parts are preserved.
     *
     * @param value Input string.
     * @param delimiter Delimiter character.
     * @return Split parts.
     */
    [[nodiscard]] static std::vector<std::string> split(
        std::string_view value,
        char delimiter)
    {
      std::vector<std::string> parts;
      std::size_t start = 0;

      while (start <= value.size())
      {
        const std::size_t pos = value.find(delimiter, start);

        if (pos == std::string_view::npos)
        {
          parts.emplace_back(value.substr(start));
          break;
        }

        parts.emplace_back(value.substr(start, pos - start));
        start = pos + 1;
      }

      return parts;
    }

    /**
     * @brief Joins string parts with a separator.
     *
     * @param parts Values to join.
     * @param separator Separator inserted between values.
     * @return Joined string.
     */
    [[nodiscard]] static std::string join(
        const std::vector<std::string> &parts,
        std::string_view separator)
    {
      std::string result;

      for (std::size_t i = 0; i < parts.size(); ++i)
      {
        result += parts[i];

        if (i + 1 < parts.size())
        {
          result += separator;
        }
      }

      return result;
    }
  };

} // namespace softadastra::cli::utils

#endif // SOFTADASTRA_CLI_STRING_UTILS_HPP
