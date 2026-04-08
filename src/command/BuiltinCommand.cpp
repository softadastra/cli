/*
 * BuiltinCommand.cpp
 */

#include <iostream>
#include <memory>
#include <vector>

#include <softadastra/cli/command/BuiltinCommand.hpp>
#include <softadastra/cli/types/CliErrorCode.hpp>

namespace softadastra::cli::command
{
  namespace types = softadastra::cli::types;

  namespace
  {
    class HelpCommandHandler : public ICommandHandler
    {
    public:
      types::CliErrorCode handle(const parser::ParsedCommand &) override
      {
        std::cout << "Available commands:\n";
        std::cout << "  help     Show this help message\n";
        std::cout << "  version  Show CLI version\n";
        std::cout << "  exit     Exit the CLI\n";
        return types::CliErrorCode::None;
      }
    };

    class VersionCommandHandler : public ICommandHandler
    {
    public:
      types::CliErrorCode handle(const parser::ParsedCommand &) override
      {
        std::cout << "Softadastra CLI v0.1.0\n";
        return types::CliErrorCode::None;
      }
    };

    class ExitCommandHandler : public ICommandHandler
    {
    public:
      types::CliErrorCode handle(const parser::ParsedCommand &) override
      {
        std::cout << "Exiting...\n";
        return types::CliErrorCode::None;
      }
    };
  }

  std::vector<CliCommand> BuiltinCommand::definitions()
  {
    return {
        {"help",
         "Show help information",
         "help",
         types::CliCommandType::Info,
         {"h"}},
        {"version",
         "Show CLI version",
         "version",
         types::CliCommandType::Info,
         {"v"}},
        {"exit",
         "Exit the CLI",
         "exit",
         types::CliCommandType::System,
         {"quit", "q"}}};
  }

  std::vector<std::shared_ptr<ICommandHandler>> BuiltinCommand::handlers()
  {
    return {
        std::make_shared<HelpCommandHandler>(),
        std::make_shared<VersionCommandHandler>(),
        std::make_shared<ExitCommandHandler>()};
  }

} // namespace softadastra::cli::command
