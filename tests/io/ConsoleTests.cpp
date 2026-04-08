/*
 * ConsoleTests.cpp
 */

#include <iostream>

#include <softadastra/cli/io/Console.hpp>

using softadastra::cli::io::Console;

namespace
{
  void test_write()
  {
    Console::write("Hello");
    Console::writeln(" World");
  }

  void test_error()
  {
    Console::error("Error");
    Console::errorln(" message");
  }

  void test_print()
  {
    Console::print("> ");
    Console::writeln("prompt test");
  }

  void test_clear()
  {
    // Just call it (cannot assert visually)
    Console::clear();
    Console::writeln("Screen cleared (if supported)");
  }
}

int main()
{
  test_write();
  test_error();
  test_print();
  test_clear();

  std::cout << "[OK] ConsoleTests executed (manual verification)\n";
  return 0;
}
