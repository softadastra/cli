/*
 * InputReader.cpp
 */

#include <softadastra/cli/io/InputReader.hpp>

#include <iostream>
#include <string>
#include <optional>

namespace softadastra::cli::io
{
  std::optional<std::string> InputReader::read_line()
  {
    std::string line;

    if (!std::getline(std::cin, line))
    {
      return std::nullopt;
    }

    return line;
  }

  std::optional<std::string> InputReader::read_line(const std::string &prompt)
  {
    if (!prompt.empty())
    {
      std::cout << prompt;
      std::cout.flush();
    }

    return read_line();
  }

} // namespace softadastra::cli::io
