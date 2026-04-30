/*
 * InputReader.cpp
 */

#include <softadastra/cli/io/InputReader.hpp>

#include <iostream>
#include <istream>
#include <ostream>
#include <string>

namespace softadastra::cli::io
{
  std::optional<std::string> InputReader::read_line()
  {
    return read_line(std::cin);
  }

  std::optional<std::string> InputReader::read_line(
      std::string_view prompt)
  {
    return read_line(std::cin, std::cout, prompt);
  }

  std::optional<std::string> InputReader::read_line(
      std::istream &input)
  {
    std::string line;

    if (!std::getline(input, line))
    {
      return std::nullopt;
    }

    return line;
  }

  std::optional<std::string> InputReader::read_line(
      std::istream &input,
      std::ostream &output,
      std::string_view prompt)
  {
    if (!prompt.empty())
    {
      output << prompt;
      output.flush();
    }

    return read_line(input);
  }

} // namespace softadastra::cli::io
