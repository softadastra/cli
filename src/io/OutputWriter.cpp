/*
 * OutputWriter.cpp
 */

#include <softadastra/cli/io/OutputWriter.hpp>

#include <iostream>
#include <ostream>

namespace softadastra::cli::io
{
  void OutputWriter::write(std::string_view message)
  {
    write(std::cout, message);
  }

  void OutputWriter::writeln(std::string_view message)
  {
    writeln(std::cout, message);
  }

  void OutputWriter::error(std::string_view message)
  {
    write(std::cerr, message);
  }

  void OutputWriter::errorln(std::string_view message)
  {
    writeln(std::cerr, message);
  }

  void OutputWriter::write(
      std::ostream &output,
      std::string_view message)
  {
    output << message;
  }

  void OutputWriter::writeln(
      std::ostream &output,
      std::string_view message)
  {
    output << message << '\n';
  }

  void OutputWriter::flush()
  {
    std::cout.flush();
  }

  void OutputWriter::flush_error()
  {
    std::cerr.flush();
  }

  void OutputWriter::flush(std::ostream &output)
  {
    output.flush();
  }

} // namespace softadastra::cli::io
