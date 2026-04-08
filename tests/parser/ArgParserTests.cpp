/*
 * ArgParserTests.cpp
 */

#include <cassert>
#include <iostream>

#include <softadastra/cli/parser/ArgParser.hpp>
#include <softadastra/cli/parser/CommandLine.hpp>

using softadastra::cli::parser::ArgParser;
using softadastra::cli::parser::CommandLine;

namespace
{
  void test_basic_command()
  {
    CommandLine cmd({"vix", "run", "file.cpp"});
    const auto parsed = ArgParser::parse(cmd);

    assert(parsed.name == "vix");
    assert(parsed.args.size() == 2);
    assert(parsed.args[0] == "run");
    assert(parsed.args[1] == "file.cpp");
  }

  void test_flags()
  {
    CommandLine cmd({"vix", "run", "--verbose"});
    const auto parsed = ArgParser::parse(cmd);

    assert(parsed.has_option("verbose"));
  }

  void test_key_value_equals()
  {
    CommandLine cmd({"vix", "run", "--name=hello"});
    const auto parsed = ArgParser::parse(cmd);

    const auto *opt = parsed.get_option("name");
    assert(opt != nullptr);
  }

  void test_key_value_space()
  {
    CommandLine cmd({"vix", "run", "--name", "hello"});
    const auto parsed = ArgParser::parse(cmd);

    const auto *opt = parsed.get_option("name");
    assert(opt != nullptr);
  }

  void test_integer_value()
  {
    CommandLine cmd({"vix", "run", "--count", "42"});
    const auto parsed = ArgParser::parse(cmd);

    const auto *opt = parsed.get_option("count");
    assert(opt != nullptr);
  }

  void test_double_value()
  {
    CommandLine cmd({"vix", "run", "--ratio", "3.14"});
    const auto parsed = ArgParser::parse(cmd);

    const auto *opt = parsed.get_option("ratio");
    assert(opt != nullptr);
  }

  void test_bool_value()
  {
    CommandLine cmd({"vix", "run", "--enabled", "true"});
    const auto parsed = ArgParser::parse(cmd);

    const auto *opt = parsed.get_option("enabled");
    assert(opt != nullptr);
  }
}

int main()
{
  test_basic_command();
  test_flags();
  test_key_value_equals();
  test_key_value_space();
  test_integer_value();
  test_double_value();
  test_bool_value();

  std::cout << "[OK] ArgParserTests passed\n";
  return 0;
}
