/*
 * TerminalStyle.hpp
 */

#ifndef SOFTADASTRA_CLI_TERMINAL_STYLE_HPP
#define SOFTADASTRA_CLI_TERMINAL_STYLE_HPP

#include <string>

namespace softadastra::cli::io
{
  /**
   * @brief ANSI terminal styling utilities
   *
   * Provides simple helpers for colored and formatted output.
   */
  class TerminalStyle
  {
  public:
    // Reset
    static constexpr const char *reset() noexcept { return "\033[0m"; }

    // Styles
    static constexpr const char *bold() noexcept { return "\033[1m"; }
    static constexpr const char *dim() noexcept { return "\033[2m"; }

    // Colors
    static constexpr const char *red() noexcept { return "\033[31m"; }
    static constexpr const char *green() noexcept { return "\033[32m"; }
    static constexpr const char *yellow() noexcept { return "\033[33m"; }
    static constexpr const char *blue() noexcept { return "\033[34m"; }
    static constexpr const char *magenta() noexcept { return "\033[35m"; }
    static constexpr const char *cyan() noexcept { return "\033[36m"; }

    /**
     * @brief Wrap text with a style
     */
    static std::string wrap(const std::string &text, const char *style)
    {
      return std::string(style) + text + reset();
    }

    /**
     * @brief Convenience helpers
     */
    static std::string success(const std::string &text)
    {
      return wrap(text, green());
    }

    static std::string error(const std::string &text)
    {
      return wrap(text, red());
    }

    static std::string warning(const std::string &text)
    {
      return wrap(text, yellow());
    }

    static std::string info(const std::string &text)
    {
      return wrap(text, cyan());
    }
  };

} // namespace softadastra::cli::io

#endif
