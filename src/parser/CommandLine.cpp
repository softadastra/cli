/*
 * CommandLine.cpp
 */

#include <iterator>
#include <utility>

#include <softadastra/cli/parser/CommandLine.hpp>

namespace softadastra::cli::parser
{
  CommandLine::CommandLine(std::vector<std::string> tokens)
      : tokens_(std::move(tokens))
  {
  }

  const std::vector<std::string> &CommandLine::tokens() const noexcept
  {
    return tokens_;
  }

  bool CommandLine::empty() const noexcept
  {
    return tokens_.empty();
  }

  std::size_t CommandLine::size() const noexcept
  {
    return tokens_.size();
  }

  const std::string &CommandLine::at(std::size_t index) const
  {
    return tokens_.at(index);
  }

  std::string CommandLine::command() const
  {
    if (tokens_.empty())
    {
      return {};
    }

    return tokens_.front();
  }

  std::vector<std::string> CommandLine::arguments() const
  {
    if (tokens_.size() <= 1)
    {
      return {};
    }

    return std::vector<std::string>(
        std::next(tokens_.begin()),
        tokens_.end());
  }

} // namespace softadastra::cli::parser
