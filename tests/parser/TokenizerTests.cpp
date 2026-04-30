/*
 * TokenizerTests.cpp
 */

#include <cassert>
#include <iostream>
#include <vector>

#include <softadastra/cli/parser/Tokenizer.hpp>

using softadastra::cli::parser::Tokenizer;

namespace
{
  void test_basic_split()
  {
    const auto tokens = Tokenizer::tokenize("vix run file.cpp");

    assert(tokens.size() == 3);
    assert(tokens[0] == "vix");
    assert(tokens[1] == "run");
    assert(tokens[2] == "file.cpp");
  }

  void test_multiple_spaces()
  {
    const auto tokens = Tokenizer::tokenize("  vix   run    file.cpp  ");

    assert(tokens.size() == 3);
    assert(tokens[0] == "vix");
    assert(tokens[1] == "run");
    assert(tokens[2] == "file.cpp");
  }

  void test_quotes()
  {
    const auto tokens = Tokenizer::tokenize("vix run \"hello world\"");

    assert(tokens.size() == 3);
    assert(tokens[0] == "vix");
    assert(tokens[1] == "run");
    assert(tokens[2] == "hello world");
  }

  void test_single_quotes()
  {
    const auto tokens = Tokenizer::tokenize("vix run 'hello world'");

    assert(tokens.size() == 3);
    assert(tokens[0] == "vix");
    assert(tokens[1] == "run");
    assert(tokens[2] == "hello world");
  }

  void test_escape()
  {
    const auto tokens = Tokenizer::tokenize("vix run hello\\ world");

    assert(tokens.size() == 3);
    assert(tokens[0] == "vix");
    assert(tokens[1] == "run");
    assert(tokens[2] == "hello world");
  }

  void test_escaped_quote_inside_double_quotes()
  {
    const auto tokens = Tokenizer::tokenize("vix say \"hello \\\"world\\\"\"");

    assert(tokens.size() == 3);
    assert(tokens[0] == "vix");
    assert(tokens[1] == "say");
    assert(tokens[2] == "hello \"world\"");
  }

  void test_escaped_single_quote_inside_single_quotes()
  {
    const auto tokens = Tokenizer::tokenize("vix say 'hello \\'world\\''");

    assert(tokens.size() == 3);
    assert(tokens[0] == "vix");
    assert(tokens[1] == "say");
    assert(tokens[2] == "hello 'world'");
  }

  void test_mixed_quotes_are_preserved_inside_other_quotes()
  {
    const auto tokens = Tokenizer::tokenize("vix say \"hello 'world'\"");

    assert(tokens.size() == 3);
    assert(tokens[0] == "vix");
    assert(tokens[1] == "say");
    assert(tokens[2] == "hello 'world'");
  }

  void test_trailing_escape_is_preserved()
  {
    const auto tokens = Tokenizer::tokenize("vix run path\\");

    assert(tokens.size() == 3);
    assert(tokens[0] == "vix");
    assert(tokens[1] == "run");
    assert(tokens[2] == "path\\");
  }

  void test_empty_input()
  {
    const auto tokens = Tokenizer::tokenize("");

    assert(tokens.empty());
  }

  void test_blank_input()
  {
    const auto tokens = Tokenizer::tokenize("     ");

    assert(tokens.empty());
  }
}

int main()
{
  test_basic_split();
  test_multiple_spaces();
  test_quotes();
  test_single_quotes();
  test_escape();
  test_escaped_quote_inside_double_quotes();
  test_escaped_single_quote_inside_single_quotes();
  test_mixed_quotes_are_preserved_inside_other_quotes();
  test_trailing_escape_is_preserved();
  test_empty_input();
  test_blank_input();

  std::cout << "[OK] TokenizerTests passed\n";
  return 0;
}
