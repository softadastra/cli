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

  void test_quotes()
  {
    const auto tokens = Tokenizer::tokenize("vix run \"hello world\"");

    assert(tokens.size() == 3);
    assert(tokens[2] == "hello world");
  }

  void test_single_quotes()
  {
    const auto tokens = Tokenizer::tokenize("vix run 'hello world'");

    assert(tokens.size() == 3);
    assert(tokens[2] == "hello world");
  }

  void test_escape()
  {
    const auto tokens = Tokenizer::tokenize("vix run hello\\ world");

    assert(tokens.size() == 3);
    assert(tokens[2] == "hello world");
  }

  void test_empty_input()
  {
    const auto tokens = Tokenizer::tokenize("");

    assert(tokens.empty());
  }
}

int main()
{
  test_basic_split();
  test_quotes();
  test_single_quotes();
  test_escape();
  test_empty_input();

  std::cout << "[OK] TokenizerTests passed\n";
  return 0;
}
