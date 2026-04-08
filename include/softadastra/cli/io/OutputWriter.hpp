/*
 * OutputWriter.hpp
 */

#ifndef SOFTADASTRA_CLI_OUTPUT_WRITER_HPP
#define SOFTADASTRA_CLI_OUTPUT_WRITER_HPP

#include <string>

namespace softadastra::cli::io
{
  /**
   * @brief Output abstraction layer
   */
  class OutputWriter
  {
  public:
    static void write(const std::string &message);
    static void writeln(const std::string &message);

    static void error(const std::string &message);
    static void errorln(const std::string &message);
  };

} // namespace softadastra::cli::io

#endif
