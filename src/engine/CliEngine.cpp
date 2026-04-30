/*
 * CliEngine.cpp
 */

#include <softadastra/cli/engine/CliEngine.hpp>

namespace softadastra::cli::engine
{
  CliEngine::CliEngine(const cli_core::CliContext &context)
      : context_(context),
        application_(context)
  {
  }

  bool CliEngine::start()
  {
    if (status_ == cli_types::CliStatus::Running)
    {
      return true;
    }

    if (!context_.valid())
    {
      status_ = cli_types::CliStatus::Failed;
      return false;
    }

    status_ = cli_types::CliStatus::Starting;

    if (!application_.start())
    {
      status_ = cli_types::CliStatus::Failed;
      return false;
    }

    status_ = cli_types::CliStatus::Running;
    return true;
  }

  void CliEngine::stop()
  {
    if (status_ == cli_types::CliStatus::Stopped)
    {
      return;
    }

    status_ = cli_types::CliStatus::Stopping;

    if (context_.valid())
    {
      application_.stop();
    }

    status_ = cli_types::CliStatus::Stopped;
  }

  cli_types::CliStatus CliEngine::status() const noexcept
  {
    return status_;
  }

  bool CliEngine::running() const noexcept
  {
    return status_ == cli_types::CliStatus::Running &&
           application_.running();
  }

  std::optional<cli_parser::ParsedCommand> CliEngine::parse(
      std::string_view input) const
  {
    if (!running())
    {
      return std::nullopt;
    }

    const auto tokens = cli_parser::Tokenizer::tokenize(input);

    if (tokens.empty())
    {
      return std::nullopt;
    }

    const cli_parser::CommandLine command_line(tokens);
    const auto parsed = cli_parser::ArgParser::parse(command_line);

    if (!parsed.valid())
    {
      return std::nullopt;
    }

    return parsed;
  }

  cli_types::CliErrorCode CliEngine::execute(
      std::string_view input)
  {
    if (!running())
    {
      return cli_types::CliErrorCode::InvalidState;
    }

    const auto parsed = parse(input);

    if (!parsed.has_value())
    {
      return cli_types::CliErrorCode::ParseError;
    }

    return execute(parsed.value());
  }

  cli_types::CliErrorCode CliEngine::execute(
      const cli_parser::ParsedCommand &command)
  {
    if (!running())
    {
      return cli_types::CliErrorCode::InvalidState;
    }

    if (!command.valid())
    {
      return cli_types::CliErrorCode::ParseError;
    }

    status_ = cli_types::CliStatus::ExecutingCommand;

    const auto result = application_.execute(command);

    if (!application_.running())
    {
      status_ = cli_types::CliStatus::Stopped;
      return result;
    }

    status_ = cli_types::CliStatus::Running;
    return result;
  }

  cli_core::CliApplication &CliEngine::application() noexcept
  {
    return application_;
  }

  const cli_core::CliApplication &CliEngine::application() const noexcept
  {
    return application_;
  }

  const cli_core::CliContext &CliEngine::context() const noexcept
  {
    return context_;
  }

} // namespace softadastra::cli::engine
