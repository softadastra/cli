/*
 * Console.cpp
 */

#include <softadastra/cli/io/Console.hpp>

#include <iostream>

namespace softadastra::cli::io
{
  void Console::write(std::string_view message)
  {
    std::cout << message;
  }

  void Console::writeln(std::string_view message)
  {
    std::cout << message << '\n';
  }

  void Console::error(std::string_view message)
  {
    std::cerr << message;
  }

  void Console::errorln(std::string_view message)
  {
    std::cerr << message << '\n';
  }

  void Console::print(std::string_view message)
  {
    std::cout << message;
    std::cout.flush();
  }

  void Console::flush()
  {
    std::cout.flush();
  }

  void Console::flush_error()
  {
    std::cerr.flush();
  }

  void Console::clear()
  {
    std::cout << "\033[2J\033[H";
    std::cout.flush();
  }

  void Console::move_cursor_home()
  {
    std::cout << "\033[H";
    std::cout.flush();
  }

  std::ostream &Console::out()
  {
    return std::cout;
  }

  std::ostream &Console::err()
  {
    return std::cerr;
  }

} // namespace softadastra::cli::io
