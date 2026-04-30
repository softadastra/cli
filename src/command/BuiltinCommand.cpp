/*
 * BuiltinCommand.cpp
 */

#include <iostream>
#include <memory>
#include <vector>

#include <softadastra/cli/command/BuiltinCommand.hpp>
#include <softadastra/cli/types/CliErrorCode.hpp>
#include <softadastra/cli/utils/HelpFormatter.hpp>
#include <softadastra/cli/utils/Style.hpp>
#include <softadastra/cli/utils/Ui.hpp>

namespace softadastra::cli::command
{
  namespace types = softadastra::cli::types;
  namespace cli_utils = softadastra::cli::utils;
  namespace cli_core = softadastra::cli::core;
  namespace ui = softadastra::cli::utils::ui;
  namespace style = softadastra::cli::utils::style;

  namespace
  {
    class HelpCommandHandler final : public ICommandHandler
    {
    public:
      explicit HelpCommandHandler(const cli_core::CliContext &context)
          : context_(context)
      {
      }

      [[nodiscard]] types::CliErrorCode handle(
          const parser::ParsedCommand &command) override
      {
        if (!context_.valid())
        {
          ui::err_line(std::cerr, "CLI context is invalid.");
          return types::CliErrorCode::InvalidState;
        }

        const auto &config = context_.config_ref();
        auto &registry = context_.registry_ref();

        if (!command.args.empty())
        {
          const auto found = registry.find_command(command.args.front());

          if (!found.has_value())
          {
            ui::err_line(
                std::cerr,
                "Unknown command: " + command.args.front());

            ui::tip_line(
                std::cerr,
                "Run '" + config.app_name + " help' to list available commands.");

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

    class VersionCommandHandler final : public ICommandHandler
    {
    public:
      explicit VersionCommandHandler(const cli_core::CliContext &context)
          : context_(context)
      {
      }

      [[nodiscard]] types::CliErrorCode handle(
          const parser::ParsedCommand &) override
      {
        if (!context_.valid())
        {
          ui::err_line(std::cerr, "CLI context is invalid.");
          return types::CliErrorCode::InvalidState;
        }

        const auto &config = context_.config_ref();

        std::cout << style::BOLD << style::CYAN
                  << config.app_name
                  << style::RESET
                  << " "
                  << style::GRAY << "v" << style::RESET
                  << style::YELLOW << config.version << style::RESET
                  << "\n";

        return types::CliErrorCode::None;
      }

    private:
      const cli_core::CliContext &context_;
    };

    class ExitCommandHandler final : public ICommandHandler
    {
    public:
      [[nodiscard]] types::CliErrorCode handle(
          const parser::ParsedCommand &) override
      {
        ui::info_line(std::cout, "Exiting...");
        return types::CliErrorCode::None;
      }
    };
  }

  std::vector<CliCommand> BuiltinCommand::definitions()
  {
    return {
        {
            "help",
            "Show help information",
            "help [command]",
            types::CliCommandType::Info,
            {"h"},
            {
                {
                    "command",
                    "c",
                    "Show help for a specific command",
                    "COMMAND",
                    true,
                    false,
                },
            },
        },
        {
            "version",
            "Show CLI version",
            "version",
            types::CliCommandType::Info,
            {"v"},
            {},
        },
        {
            "exit",
            "Exit the CLI session",
            "exit",
            types::CliCommandType::System,
            {"quit", "q"},
            {},
        },
    };
  }

  std::vector<std::shared_ptr<ICommandHandler>> BuiltinCommand::handlers(
      const cli_core::CliContext &context)
  {
    return {
        std::make_shared<HelpCommandHandler>(context),
        std::make_shared<VersionCommandHandler>(context),
        std::make_shared<ExitCommandHandler>(),
    };
  }

} // namespace softadastra::cli::command
