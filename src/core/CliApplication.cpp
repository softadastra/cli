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

    context_.session_ref().start();
    return true;
  }

  void CliApplication::stop()
  {
    if (!context_.valid())
    {
      return;
    }

    context_.session_ref().stop();
  }

  bool CliApplication::running() const noexcept
  {
    if (!context_.valid())
    {
      return false;
    }

    return context_.session->running();
  }

  types::CliErrorCode CliApplication::execute(
      const parser::ParsedCommand &command)
  {
    if (!context_.valid())
    {
      return types::CliErrorCode::InvalidState;
    }

    auto &session = context_.session_ref();

    if (!session.running())
    {
      return types::CliErrorCode::InvalidState;
    }

    if (!command.valid())
    {
      return types::CliErrorCode::ParseError;
    }

    auto &registry = context_.registry_ref();

    if (command.has_option("help") ||
        command.has_option("h"))
    {
      const auto help_handler = registry.get_handler("help");

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

    const auto handler = registry.get_handler(command.name);

    if (handler == nullptr)
    {
      return types::CliErrorCode::InternalError;
    }

    session.set_last_command(command.name);
    session.increment_command_count();
    session.set_status(types::CliStatus::ExecutingCommand);

    const auto result = handler->handle(command);

    if (result == types::CliErrorCode::None)
    {
      if (session.stop_requested())
      {
        session.stop();
      }
      else if (session.running())
      {
        session.set_status(types::CliStatus::Running);
      }
    }
    else
    {
      session.set_status(types::CliStatus::Running);
    }

    return result;
  }

  const CliContext &CliApplication::context() const noexcept
  {
    return context_;
  }

} // namespace softadastra::cli::core
