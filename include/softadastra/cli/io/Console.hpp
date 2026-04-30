/**
 *
 *  @file Console.hpp
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

#ifndef SOFTADASTRA_CLI_CONSOLE_HPP
#define SOFTADASTRA_CLI_CONSOLE_HPP

#include <iosfwd>
#include <string_view>

namespace softadastra::cli::io
{
  /**
   * @brief Provides centralized console output helpers.
   *
   * Console is a small utility used by CLI components to write to stdout and
   * stderr through a consistent interface.
   *
   * It is used for:
   * - normal command output
   * - error output
   * - prompts
   * - terminal control helpers
   *
   * The class is stateless and does not own any output stream.
   */
  class Console
  {
  public:
    /**
     * @brief Writes a message to stdout without appending a newline.
     *
     * @param message Message to write.
     */
    static void write(std::string_view message);

    /**
     * @brief Writes a message to stdout and appends a newline.
     *
     * @param message Message to write.
     */
    static void writeln(std::string_view message);

    /**
     * @brief Writes a message to stderr without appending a newline.
     *
     * @param message Message to write.
     */
    static void error(std::string_view message);

    /**
     * @brief Writes a message to stderr and appends a newline.
     *
     * @param message Message to write.
     */
    static void errorln(std::string_view message);

    /**
     * @brief Writes a prompt-style message to stdout without a newline.
     *
     * @param message Message to write.
     */
    static void print(std::string_view message);

    /**
     * @brief Flushes stdout.
     */
    static void flush();

    /**
     * @brief Flushes stderr.
     */
    static void flush_error();

    /**
     * @brief Clears the terminal screen using ANSI escape sequences.
     *
     * This is intended for ANSI-compatible terminals.
     */
    static void clear();

    /**
     * @brief Moves the terminal cursor to the top-left position.
     */
    static void move_cursor_home();

    /**
     * @brief Returns the stdout stream.
     *
     * @return stdout stream reference.
     */
    [[nodiscard]] static std::ostream &out();

    /**
     * @brief Returns the stderr stream.
     *
     * @return stderr stream reference.
     */
    [[nodiscard]] static std::ostream &err();
  };

} // namespace softadastra::cli::io

#endif // SOFTADASTRA_CLI_CONSOLE_HPP
