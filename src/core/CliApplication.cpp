/*
 * CliApplication.cpp
 */

#include <softadastra/cli/core/CliApplication.hpp>

namespace softadastra::cli::core
{
  CliApplication::CliApplication(const CliContext &context)
      : context_(context)
  {
  }

  bool CliApplication::start()
  {
    if (!context_.valid())
    {
      return false;
    }

    session_.start();
    return true;
  }

  void CliApplication::stop()
  {
    session_.stop();
  }

  bool CliApplication::running() const noexcept
  {
    return session_.running();
  }

  types::CliErrorCode CliApplication::execute(const parser::ParsedCommand &command)
  {
    if (!running())
    {
      return types::CliErrorCode::InvalidState;
    }

    if (!command.valid())
    {
      return types::CliErrorCode::ParseError;
    }

    auto &registry = context_.registry_ref();

    if (command.has_option("help"))
    {
      auto help_handler = registry.get_handler("help");
      if (help_handler == nullptr)
      {
        return types::CliErrorCode::InternalError;
      }

      parser::ParsedCommand help_command;
      help_command.name = "help";
      help_command.args.push_back(command.name);

      return help_handler->handle(help_command);
    }

    if (!registry.exists(command.name))
    {
      return types::CliErrorCode::CommandNotFound;
    }

    auto handler = registry.get_handler(command.name);
    if (handler == nullptr)
    {
      return types::CliErrorCode::InternalError;
    }

    session_.set_last_command(command.name);
    session_.set_status(types::CliStatus::ExecutingCommand);

    const auto result = handler->handle(command);

    session_.set_status(types::CliStatus::Running);

    return result;
  }

  CliSession &CliApplication::session() noexcept
  {
    return session_;
  }

  const CliContext &CliApplication::context() const noexcept
  {
    return context_;
  }

} // namespace softadastra::cli::core
