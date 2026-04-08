/*
 * InputReader.hpp
 */

#ifndef SOFTADASTRA_CLI_INPUT_READER_HPP
#define SOFTADASTRA_CLI_INPUT_READER_HPP

#include <string>

namespace softadastra::cli::io
{
  /**
   * @brief Reads input from the user (stdin)
   */
  class InputReader
  {
  public:
    /**
     * @brief Read one line from stdin
     *
     * Returns empty string on EOF or error.
     */
    static std::string read_line();

    /**
     * @brief Read one line with a prompt
     */
    static std::string read_line(const std::string &prompt);
  };

} // namespace softadastra::cli::io

#endif
