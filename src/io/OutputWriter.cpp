/*
 * OutputWriter.cpp
 */

#include <iostream>

#include <softadastra/cli/io/OutputWriter.hpp>

namespace softadastra::cli::io
{
  void OutputWriter::write(const std::string &message)
  {
    std::cout << message;
  }

  void OutputWriter::writeln(const std::string &message)
  {
    std::cout << message << '\n';
  }

  void OutputWriter::error(const std::string &message)
  {
    std::cerr << message;
  }

  void OutputWriter::errorln(const std::string &message)
  {
    std::cerr << message << '\n';
  }

} // namespace softadastra::cli::io
