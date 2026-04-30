/**
 *
 *  @file Style.hpp
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

#ifndef SOFTADASTRA_CLI_UTILS_STYLE_HPP
#define SOFTADASTRA_CLI_UTILS_STYLE_HPP

#include <iostream>
#include <string>
#include <string_view>

namespace softadastra::cli::utils::style
{
  inline constexpr const char *RESET = "\033[0m";
  inline constexpr const char *BOLD = "\033[1m";
  inline constexpr const char *UNDERLINE = "\033[4m";

  inline constexpr const char *RED = "\033[31m";
  inline constexpr const char *GREEN = "\033[32m";
  inline constexpr const char *YELLOW = "\033[33m";
  inline constexpr const char *CYAN = "\033[36m";
  inline constexpr const char *GRAY = "\033[90m";

  inline constexpr const char *PAD = "  ";

  [[nodiscard]] inline std::string colored(
      std::string_view value,
      const char *color)
  {
    return std::string(color) + std::string(value) + RESET;
  }

  [[nodiscard]] inline std::string bold(std::string_view value)
  {
    return std::string(BOLD) + std::string(value) + RESET;
  }

  [[nodiscard]] inline std::string dim(std::string_view value)
  {
    return std::string(GRAY) + std::string(value) + RESET;
  }

  [[nodiscard]] inline std::string link(std::string_view url)
  {
    return std::string(CYAN) + UNDERLINE + std::string(url) + RESET;
  }

  inline void error(std::string_view msg)
  {
    std::cerr << PAD << RED << "✖ " << msg << RESET << "\n";
  }

  inline void success(std::string_view msg)
  {
    std::cout << PAD << GREEN << "✔ " << msg << RESET << "\n";
  }

  inline void warning(std::string_view msg)
  {
    std::cout << PAD << YELLOW << "! " << msg << RESET << "\n";
  }

  inline void info(std::string_view msg)
  {
    std::cout << PAD << CYAN << "• " << RESET << msg << "\n";
  }

  inline void hint(std::string_view msg)
  {
    std::cout << PAD << GRAY << "➜ " << msg << RESET << "\n";
  }

  inline void section_title(
      std::ostream &out,
      std::string_view label)
  {
    out << PAD << BOLD << CYAN << label << RESET << "\n";
  }

  inline void blank(std::ostream &out = std::cout)
  {
    out << "\n";
  }

} // namespace softadastra::cli::utils::style

#endif // SOFTADASTRA_CLI_UTILS_STYLE_HPP
