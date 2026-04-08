/*
 * ConsoleTests.cpp
 */

#include <cassert>
#include <iostream>
#include <sstream>

#include <softadastra/cli/io/Console.hpp>

using softadastra::cli::io::Console;

namespace
{
  void test_write()
  {
    std::ostringstream out;
    auto *old_buf = std::cout.rdbuf(out.rdbuf());

    Console::write("Hello");
    Console::writeln(" World");

    std::cout.rdbuf(old_buf);

    assert(out.str() == "Hello World\n");
  }

  void test_error()
  {
    std::ostringstream err;
    auto *old_buf = std::cerr.rdbuf(err.rdbuf());

    Console::error("Error");
    Console::errorln(" message");

    std::cerr.rdbuf(old_buf);

    assert(err.str() == "Error message\n");
  }

  void test_print()
  {
    std::ostringstream out;
    auto *old_buf = std::cout.rdbuf(out.rdbuf());

    Console::print("> ");
    Console::writeln("prompt test");

    std::cout.rdbuf(old_buf);

    assert(out.str() == "> prompt test\n");
  }

  void test_clear()
  {
    Console::clear();
  }
}

int main()
{
  test_write();
  test_error();
  test_print();
  test_clear();

  std::cout << "[OK] ConsoleTests passed\n";
  return 0;
}
