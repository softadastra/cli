/**
 *
 *  @file InputReader.hpp
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

#ifndef SOFTADASTRA_CLI_INPUT_READER_HPP
#define SOFTADASTRA_CLI_INPUT_READER_HPP

#include <iosfwd>
#include <optional>
#include <string>
#include <string_view>

namespace softadastra::cli::io
{
  /**
   * @brief Provides stdin input helpers for CLI applications.
   *
   * InputReader centralizes line-based input reading for interactive CLI
   * sessions.
   *
   * It supports:
   * - reading one line from stdin
   * - reading one line with a prompt
   * - reading from a custom input stream for tests
   *
   * EOF and input errors are represented as std::nullopt.
   */
  class InputReader
  {
  public:
    /**
     * @brief Reads one line from stdin.
     *
     * @return Input line, or std::nullopt on EOF or input error.
     */
    [[nodiscard]] static std::optional<std::string> read_line();

    /**
     * @brief Reads one line from stdin after printing a prompt.
     *
     * @param prompt Prompt text displayed before reading.
     * @return Input line, or std::nullopt on EOF or input error.
     */
    [[nodiscard]] static std::optional<std::string> read_line(
        std::string_view prompt);

    /**
     * @brief Reads one line from a custom input stream.
     *
     * This is useful for unit tests and embedded CLI integrations.
     *
     * @param input Input stream.
     * @return Input line, or std::nullopt on EOF or input error.
     */
    [[nodiscard]] static std::optional<std::string> read_line(
        std::istream &input);

    /**
     * @brief Reads one line from a custom input stream after printing a prompt.
     *
     * @param input Input stream.
     * @param output Output stream used to display the prompt.
     * @param prompt Prompt text.
     * @return Input line, or std::nullopt on EOF or input error.
     */
    [[nodiscard]] static std::optional<std::string> read_line(
        std::istream &input,
        std::ostream &output,
        std::string_view prompt);
  };

} // namespace softadastra::cli::io

#endif // SOFTADASTRA_CLI_INPUT_READER_HPP
