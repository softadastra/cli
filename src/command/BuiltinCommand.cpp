/*
 * BuiltinCommand.cpp
 */

#include <iostream>
#include <memory>
#include <vector>

#include <softadastra/cli/command/BuiltinCommand.hpp>
#include <softadastra/cli/types/CliErrorCode.hpp>
#include <softadastra/cli/utils/HelpFormatter.hpp>

namespace softadastra::cli::command
{
  namespace types = softadastra::cli::types;
  namespace cli_utils = softadastra::cli::utils;
  namespace cli_core = softadastra::cli::core;

  namespace
  {
    class HelpCommandHandler : public ICommandHandler
    {
    public:
      explicit HelpCommandHandler(const cli_core::CliContext &context)
          : context_(context)
      {
      }

      types::CliErrorCode handle(const parser::ParsedCommand &command) override
      {
        if (!context_.valid())
        {
          return types::CliErrorCode::InvalidState;
        }

        const auto &config = context_.config_ref();
        auto &registry = context_.registry_ref();

        if (!command.args.empty())
        {
          const auto found = registry.find_command(command.args.front());

          if (!found.has_value())
          {
            std::cerr << "Unknown command: " << command.args.front() << "\n";
            return types::CliErrorCode::CommandNotFound;
          }

          std::cout << cli_utils::HelpFormatter::format_command(*found)
                    << std::flush;
          return types::CliErrorCode::None;
        }

        std::cout << cli_utils::HelpFormatter::format(
                         registry.all_commands(),
                         config.app_name)
                  << std::flush;

        return types::CliErrorCode::None;
      }

    private:
      const cli_core::CliContext &context_;
    };

    class VersionCommandHandler : public ICommandHandler
    {
    public:
      explicit VersionCommandHandler(const cli_core::CliContext &context)
          : context_(context)
      {
      }

      types::CliErrorCode handle(const parser::ParsedCommand &) override
      {
        if (!context_.valid())
        {
          return types::CliErrorCode::InvalidState;
        }

        const auto &config = context_.config_ref();
        std::cout << config.app_name << " v" << config.version << "\n";
        return types::CliErrorCode::None;
      }

    private:
      const cli_core::CliContext &context_;
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
         "help [command]",
         types::CliCommandType::Info,
         {"h"},
         {
             {"help", "h", "Show help for a command", "COMMAND", false},
         }},
        {"version",
         "Show CLI version",
         "version",
         types::CliCommandType::Info,
         {"v"},
         {}},
        {"exit",
         "Exit the CLI",
         "exit",
         types::CliCommandType::System,
         {"quit", "q"},
         {}}};
  }

  std::vector<std::shared_ptr<ICommandHandler>> BuiltinCommand::handlers(
      const cli_core::CliContext &context)
  {
    return {
        std::make_shared<HelpCommandHandler>(context),
        std::make_shared<VersionCommandHandler>(context),
        std::make_shared<ExitCommandHandler>()};
  }

} // namespace softadastra::cli::command
