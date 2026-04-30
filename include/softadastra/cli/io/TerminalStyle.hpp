/**
 *
 *  @file TerminalStyle.hpp
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

#ifndef SOFTADASTRA_CLI_TERMINAL_STYLE_HPP
#define SOFTADASTRA_CLI_TERMINAL_STYLE_HPP

#include <string>
#include <string_view>

namespace softadastra::cli::io
{
  /**
   * @brief Provides ANSI terminal styling helpers.
   *
   * TerminalStyle contains low-level ANSI escape sequences and small helpers
   * for producing styled terminal strings.
   *
   * It is used by:
   * - Console
   * - OutputWriter
   * - HelpFormatter
   * - command handlers
   *
   * This class only formats strings. It does not write to stdout or stderr.
   */
  class TerminalStyle
  {
  public:
    /**
     * @brief ANSI reset sequence.
     */
    [[nodiscard]] static constexpr const char *reset() noexcept
    {
      return "\033[0m";
    }

    /**
     * @brief ANSI bold sequence.
     */
    [[nodiscard]] static constexpr const char *bold() noexcept
    {
      return "\033[1m";
    }

    /**
     * @brief ANSI dim sequence.
     */
    [[nodiscard]] static constexpr const char *dim() noexcept
    {
      return "\033[2m";
    }

    /**
     * @brief ANSI underline sequence.
     */
    [[nodiscard]] static constexpr const char *underline() noexcept
    {
      return "\033[4m";
    }

    /**
     * @brief ANSI red foreground color.
     */
    [[nodiscard]] static constexpr const char *red() noexcept
    {
      return "\033[31m";
    }

    /**
     * @brief ANSI green foreground color.
     */
    [[nodiscard]] static constexpr const char *green() noexcept
    {
      return "\033[32m";
    }

    /**
     * @brief ANSI yellow foreground color.
     */
    [[nodiscard]] static constexpr const char *yellow() noexcept
    {
      return "\033[33m";
    }

    /**
     * @brief ANSI blue foreground color.
     */
    [[nodiscard]] static constexpr const char *blue() noexcept
    {
      return "\033[34m";
    }

    /**
     * @brief ANSI magenta foreground color.
     */
    [[nodiscard]] static constexpr const char *magenta() noexcept
    {
      return "\033[35m";
    }

    /**
     * @brief ANSI cyan foreground color.
     */
    [[nodiscard]] static constexpr const char *cyan() noexcept
    {
      return "\033[36m";
    }

    /**
     * @brief ANSI gray foreground color.
     */
    [[nodiscard]] static constexpr const char *gray() noexcept
    {
      return "\033[90m";
    }

    /**
     * @brief Wraps text with one ANSI style sequence.
     *
     * @param text Text to style.
     * @param style ANSI style sequence.
     * @return Styled string.
     */
    [[nodiscard]] static std::string wrap(
        std::string_view text,
        const char *style)
    {
      return std::string(style) + std::string(text) + reset();
    }

    /**
     * @brief Wraps text with two ANSI style sequences.
     *
     * @param text Text to style.
     * @param first First ANSI style sequence.
     * @param second Second ANSI style sequence.
     * @return Styled string.
     */
    [[nodiscard]] static std::string wrap(
        std::string_view text,
        const char *first,
        const char *second)
    {
      return std::string(first) +
             std::string(second) +
             std::string(text) +
             reset();
    }

    /**
     * @brief Styles text as success output.
     *
     * @param text Text to style.
     * @return Styled string.
     */
    [[nodiscard]] static std::string success(std::string_view text)
    {
      return wrap(text, green());
    }

    /**
     * @brief Styles text as error output.
     *
     * @param text Text to style.
     * @return Styled string.
     */
    [[nodiscard]] static std::string error(std::string_view text)
    {
      return wrap(text, red());
    }

    /**
     * @brief Styles text as warning output.
     *
     * @param text Text to style.
     * @return Styled string.
     */
    [[nodiscard]] static std::string warning(std::string_view text)
    {
      return wrap(text, yellow());
    }

    /**
     * @brief Styles text as informational output.
     *
     * @param text Text to style.
     * @return Styled string.
     */
    [[nodiscard]] static std::string info(std::string_view text)
    {
      return wrap(text, cyan());
    }

    /**
     * @brief Styles text as muted output.
     *
     * @param text Text to style.
     * @return Styled string.
     */
    [[nodiscard]] static std::string muted(std::string_view text)
    {
      return wrap(text, gray());
    }

    /**
     * @brief Styles text as strong output.
     *
     * @param text Text to style.
     * @return Styled string.
     */
    [[nodiscard]] static std::string strong(std::string_view text)
    {
      return wrap(text, bold());
    }

    /**
     * @brief Styles text as a terminal link-like value.
     *
     * @param text Text to style.
     * @return Styled string.
     */
    [[nodiscard]] static std::string link(std::string_view text)
    {
      return wrap(text, cyan(), underline());
    }
  };

} // namespace softadastra::cli::io

#endif // SOFTADASTRA_CLI_TERMINAL_STYLE_HPP
