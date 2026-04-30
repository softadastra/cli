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

  void test_flush()
  {
    std::ostringstream out;
    auto *old_buf = std::cout.rdbuf(out.rdbuf());

    Console::write("flush");
    Console::flush();

    std::cout.rdbuf(old_buf);

    assert(out.str() == "flush");
  }

  void test_flush_error()
  {
    std::ostringstream err;
    auto *old_buf = std::cerr.rdbuf(err.rdbuf());

    Console::error("flush-error");
    Console::flush_error();

    std::cerr.rdbuf(old_buf);

    assert(err.str() == "flush-error");
  }

  void test_clear()
  {
    std::ostringstream out;
    auto *old_buf = std::cout.rdbuf(out.rdbuf());

    Console::clear();

    std::cout.rdbuf(old_buf);

    assert(out.str() == "\033[2J\033[H");
  }

  void test_move_cursor_home()
  {
    std::ostringstream out;
    auto *old_buf = std::cout.rdbuf(out.rdbuf());

    Console::move_cursor_home();

    std::cout.rdbuf(old_buf);

    assert(out.str() == "\033[H");
  }

  void test_stream_accessors()
  {
    assert(&Console::out() == &std::cout);
    assert(&Console::err() == &std::cerr);
  }
}

int main()
{
  test_write();
  test_error();
  test_print();
  test_flush();
  test_flush_error();
  test_clear();
  test_move_cursor_home();
  test_stream_accessors();

  std::cout << "[OK] ConsoleTests passed\n";
  return 0;
}
