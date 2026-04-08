/*
 * Console.cpp
 */

#include <softadastra/cli/io/Console.hpp>

#include <cstdlib>
#include <iostream>

namespace softadastra::cli::io
{
  void Console::write(const std::string &message)
  {
    std::cout << message;
  }

  void Console::writeln(const std::string &message)
  {
    std::cout << message << '\n';
  }

  void Console::error(const std::string &message)
  {
    std::cerr << message;
  }

  void Console::errorln(const std::string &message)
  {
    std::cerr << message << '\n';
  }

  void Console::print(const std::string &message)
  {
    std::cout << message;
  }

  void Console::clear()
  {
#if defined(_WIN32)
    static_cast<void>(std::system("cls"));
#else
    static_cast<void>(std::system("clear"));
#endif
  }

} // namespace softadastra::cli::io
