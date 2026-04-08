/*
 * StringUtils.hpp
 */

#ifndef SOFTADASTRA_CLI_STRING_UTILS_HPP
#define SOFTADASTRA_CLI_STRING_UTILS_HPP

#include <algorithm>
#include <cctype>
#include <string>

namespace softadastra::cli::utils
{
  /**
   * @brief String utility helpers
   */
  class StringUtils
  {
  public:
    /**
     * @brief Trim whitespace from both ends
     */
    static std::string trim(const std::string &value)
    {
      auto begin = value.begin();
      auto end = value.end();

      while (begin != end && std::isspace(static_cast<unsigned char>(*begin)))
      {
        ++begin;
      }

      while (begin != end && std::isspace(static_cast<unsigned char>(*(end - 1))))
      {
        --end;
      }

      return std::string(begin, end);
    }

    /**
     * @brief Convert string to lowercase
     */
    static std::string to_lower(std::string value)
    {
      std::transform(value.begin(), value.end(), value.begin(),
                     [](unsigned char c)
                     { return static_cast<char>(std::tolower(c)); });
      return value;
    }

    /**
     * @brief Check if string starts with prefix
     */
    static bool starts_with(const std::string &value, const std::string &prefix)
    {
      return value.size() >= prefix.size() &&
             value.compare(0, prefix.size(), prefix) == 0;
    }

    /**
     * @brief Check if string ends with suffix
     */
    static bool ends_with(const std::string &value, const std::string &suffix)
    {
      return value.size() >= suffix.size() &&
             value.compare(value.size() - suffix.size(), suffix.size(), suffix) == 0;
    }
  };

} // namespace softadastra::cli::utils

#endif
