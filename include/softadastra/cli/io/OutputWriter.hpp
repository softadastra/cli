/**
 *
 *  @file OutputWriter.hpp
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

#ifndef SOFTADASTRA_CLI_OUTPUT_WRITER_HPP
#define SOFTADASTRA_CLI_OUTPUT_WRITER_HPP

#include <iosfwd>
#include <string_view>

namespace softadastra::cli::io
{
  /**
   * @brief Provides output helpers for CLI applications.
   *
   * OutputWriter centralizes stdout and stderr writes behind a small API.
   *
   * It is used by:
   * - command handlers
   * - CLI engine
   * - CLI application
   * - tests and embedded integrations
   *
   * Unlike Console, this class also exposes stream-based overloads to make
   * command output easier to test.
   */
  class OutputWriter
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
     * @brief Writes a message to a custom output stream.
     *
     * @param output Output stream.
     * @param message Message to write.
     */
    static void write(
        std::ostream &output,
        std::string_view message);

    /**
     * @brief Writes a message to a custom output stream and appends a newline.
     *
     * @param output Output stream.
     * @param message Message to write.
     */
    static void writeln(
        std::ostream &output,
        std::string_view message);

    /**
     * @brief Flushes stdout.
     */
    static void flush();

    /**
     * @brief Flushes stderr.
     */
    static void flush_error();

    /**
     * @brief Flushes a custom output stream.
     *
     * @param output Output stream.
     */
    static void flush(std::ostream &output);
  };

} // namespace softadastra::cli::io

#endif // SOFTADASTRA_CLI_OUTPUT_WRITER_HPP
