/**
 *
 *  @file Ui.hpp
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

#ifndef SOFTADASTRA_CLI_UTILS_UI_HPP
#define SOFTADASTRA_CLI_UTILS_UI_HPP

#include <softadastra/cli/utils/Style.hpp>

#include <iostream>
#include <sstream>
#include <string>
#include <string_view>

namespace softadastra::cli::utils::ui
{
  using namespace softadastra::cli::utils::style;

  [[nodiscard]] inline std::string quote(std::string_view value)
  {
    return std::string("\"") + std::string(value) + "\"";
  }

  inline void section(
      std::ostream &out,
      std::string_view title)
  {
    section_title(out, title);
  }

  inline void kv(
      std::ostream &out,
      std::string_view key,
      std::string_view value,
      int pad = 14)
  {
    std::string padded_key{key};

    if (static_cast<int>(padded_key.size()) < pad)
    {
      padded_key.append(
          static_cast<std::size_t>(pad - static_cast<int>(padded_key.size())),
          ' ');
    }

    out << "    "
        << GRAY << "• " << RESET
        << GRAY << padded_key << RESET
        << GRAY << ": " << RESET
        << YELLOW << BOLD << value << RESET
        << "\n";
  }

  inline void ok_line(
      std::ostream &out,
      std::string_view msg)
  {
    out << "  " << GREEN << "✔" << RESET << " " << msg << "\n";
  }

  inline void err_line(
      std::ostream &out,
      std::string_view msg)
  {
    out << "  " << RED << "✖" << RESET << " " << msg << "\n";
  }

  inline void warn_line(
      std::ostream &out,
      std::string_view msg)
  {
    out << "  " << YELLOW << "!" << RESET << " " << msg << "\n";
  }

  inline void info_line(
      std::ostream &out,
      std::string_view msg)
  {
    out << "  " << CYAN << "•" << RESET << " " << msg << "\n";
  }

  inline void tip_line(
      std::ostream &out,
      std::string_view msg)
  {
    out << "\n"
        << BOLD << CYAN << "TIP:" << RESET
        << " " << msg << "\n\n";
  }

  [[nodiscard]] inline std::string faint_sep()
  {
    return std::string(GRAY) +
           "────────────────────────────────────────" +
           RESET;
  }

  inline void spacer(std::ostream &out)
  {
    out << "\n";
  }

  inline void pkg_line(
      std::ostream &out,
      std::string_view id,
      std::string_view latest,
      std::string_view description,
      std::string_view repo)
  {
    out << "  " << CYAN << BOLD << id << RESET;

    if (!latest.empty())
    {
      out << "  "
          << GRAY << "(" << RESET
          << YELLOW << "latest" << RESET
          << GRAY << ": " << RESET
          << YELLOW << BOLD << latest << RESET
          << GRAY << ")" << RESET;
    }

    out << "\n";

    if (!description.empty())
    {
      out << "    " << GRAY << description << RESET << "\n";
    }

    if (!repo.empty())
    {
      out << "    "
          << GRAY << "repo: " << RESET
          << CYAN << UNDERLINE << repo << RESET
          << "\n";
    }
  }

  inline void dep_line(
      std::ostream &out,
      std::string_view id,
      std::string_view version,
      std::string_view commit,
      std::string_view repo)
  {
    out << "  " << CYAN << BOLD << id << RESET;

    if (!version.empty())
    {
      out << "  "
          << GRAY << "(" << RESET
          << YELLOW << "version" << RESET
          << GRAY << ": " << RESET
          << YELLOW << BOLD << version << RESET
          << GRAY << ")" << RESET;
    }

    out << "\n";

    if (!commit.empty())
    {
      out << "    "
          << GRAY << "commit: " << RESET
          << YELLOW << commit << RESET
          << "\n";
    }

    if (!repo.empty())
    {
      out << "    "
          << GRAY << "repo: " << RESET
          << CYAN << UNDERLINE << repo << RESET
          << "\n";
    }
  }

} // namespace softadastra::cli::utils::ui

#endif // SOFTADASTRA_CLI_UTILS_UI_HPP
