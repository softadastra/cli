/*
 * Console.hpp
 */

#ifndef SOFTADASTRA_CLI_CONSOLE_HPP
#define SOFTADASTRA_CLI_CONSOLE_HPP

#include <string>

namespace softadastra::cli::io
{
  /**
   * @brief Console output utility
   *
   * Provides a unified interface for writing to stdout/stderr.
   */
  class Console
  {
  public:
    /**
     * @brief Print message to stdout
     */
    static void write(const std::string &message);

    /**
     * @brief Print line to stdout
     */
    static void writeln(const std::string &message);

    /**
     * @brief Print message to stderr
     */
    static void error(const std::string &message);

    /**
     * @brief Print line to stderr
     */
    static void errorln(const std::string &message);

    /**
     * @brief Print without newline (prompt, etc.)
     */
    static void print(const std::string &message);

    /**
     * @brief Clear terminal screen
     */
    static void clear();
  };

} // namespace softadastra::cli::io

#endif
