/*
 * ArgParserTests.cpp
 */

#include <cassert>
#include <cstdint>
#include <iostream>
#include <string>
#include <variant>

#include <softadastra/cli/parser/ArgParser.hpp>
#include <softadastra/cli/parser/CommandLine.hpp>
#include <softadastra/cli/types/OptionValue.hpp>

using softadastra::cli::parser::ArgParser;
using softadastra::cli::parser::CommandLine;

namespace
{
  namespace cli_types = softadastra::cli::types;

  void test_basic_command()
  {
    CommandLine cmd({"vix", "run", "file.cpp"});
    const auto parsed = ArgParser::parse(cmd);

    assert(parsed.valid());
    assert(parsed.name == "vix");
    assert(parsed.args.size() == 2);
    assert(parsed.args[0] == "run");
    assert(parsed.args[1] == "file.cpp");
    assert(parsed.options.empty());
  }

  void test_flags()
  {
    CommandLine cmd({"vix", "run", "--verbose"});
    const auto parsed = ArgParser::parse(cmd);

    assert(parsed.has_option("verbose"));
    assert(parsed.option_enabled("verbose"));

    const auto *opt = parsed.get_option("verbose");
    assert(opt != nullptr);
    assert(std::holds_alternative<bool>(*opt));
    assert(std::get<bool>(*opt));
  }

  void test_key_value_equals()
  {
    CommandLine cmd({"vix", "run", "--name=hello"});
    const auto parsed = ArgParser::parse(cmd);

    const auto *opt = parsed.get_option("name");

    assert(opt != nullptr);
    assert(std::holds_alternative<std::string>(*opt));
    assert(std::get<std::string>(*opt) == "hello");
  }

  void test_key_value_space()
  {
    CommandLine cmd({"vix", "run", "--name", "hello"});
    const auto parsed = ArgParser::parse(cmd);

    const auto *opt = parsed.get_option("name");

    assert(opt != nullptr);
    assert(std::holds_alternative<std::string>(*opt));
    assert(std::get<std::string>(*opt) == "hello");
  }

  void test_integer_value()
  {
    CommandLine cmd({"vix", "run", "--count", "42"});
    const auto parsed = ArgParser::parse(cmd);

    const auto *opt = parsed.get_option("count");

    assert(opt != nullptr);
    assert(std::holds_alternative<std::int64_t>(*opt));
    assert(std::get<std::int64_t>(*opt) == 42);
  }

  void test_negative_integer_value()
  {
    CommandLine cmd({"vix", "run", "--count=-42"});
    const auto parsed = ArgParser::parse(cmd);

    const auto *opt = parsed.get_option("count");

    assert(opt != nullptr);
    assert(std::holds_alternative<std::int64_t>(*opt));
    assert(std::get<std::int64_t>(*opt) == -42);
  }

  void test_double_value()
  {
    CommandLine cmd({"vix", "run", "--ratio", "3.14"});
    const auto parsed = ArgParser::parse(cmd);

    const auto *opt = parsed.get_option("ratio");

    assert(opt != nullptr);
    assert(std::holds_alternative<double>(*opt));
    assert(std::get<double>(*opt) > 3.13);
    assert(std::get<double>(*opt) < 3.15);
  }

  void test_bool_value()
  {
    CommandLine cmd({"vix", "run", "--enabled", "true"});
    const auto parsed = ArgParser::parse(cmd);

    const auto *opt = parsed.get_option("enabled");

    assert(opt != nullptr);
    assert(std::holds_alternative<bool>(*opt));
    assert(std::get<bool>(*opt));
  }

  void test_false_bool_value()
  {
    CommandLine cmd({"vix", "run", "--enabled=false"});
    const auto parsed = ArgParser::parse(cmd);

    const auto *opt = parsed.get_option("enabled");

    assert(opt != nullptr);
    assert(std::holds_alternative<bool>(*opt));
    assert(!std::get<bool>(*opt));
  }

  void test_short_flag()
  {
    CommandLine cmd({"vix", "run", "-v"});
    const auto parsed = ArgParser::parse(cmd);

    assert(parsed.has_option("v"));
    assert(parsed.option_enabled("v"));
  }

  void test_short_key_value_space()
  {
    CommandLine cmd({"vix", "run", "-p", "8080"});
    const auto parsed = ArgParser::parse(cmd);

    const auto *opt = parsed.get_option("p");

    assert(opt != nullptr);
    assert(std::holds_alternative<std::int64_t>(*opt));
    assert(std::get<std::int64_t>(*opt) == 8080);
  }

  void test_option_string_or()
  {
    CommandLine cmd({"vix", "run", "--name", "softadastra"});
    const auto parsed = ArgParser::parse(cmd);

    assert(parsed.option_string_or("name") == "softadastra");
    assert(parsed.option_string_or("missing", "fallback") == "fallback");
  }

  void test_empty_command_line()
  {
    CommandLine cmd;
    const auto parsed = ArgParser::parse(cmd);

    assert(!parsed.valid());
    assert(parsed.empty());
  }
}

int main()
{
  test_basic_command();
  test_flags();
  test_key_value_equals();
  test_key_value_space();
  test_integer_value();
  test_negative_integer_value();
  test_double_value();
  test_bool_value();
  test_false_bool_value();
  test_short_flag();
  test_short_key_value_space();
  test_option_string_or();
  test_empty_command_line();

  std::cout << "[OK] ArgParserTests passed\n";
  return 0;
}
