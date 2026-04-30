/*
 * CliService.cpp
 */

#include <cstddef>
#include <memory>
#include <utility>

#include <softadastra/cli/CliService.hpp>
#include <softadastra/cli/command/BuiltinCommand.hpp>
#include <softadastra/cli/io/Console.hpp>
#include <softadastra/cli/io/InputReader.hpp>
#include <softadastra/cli/types/CliErrorCode.hpp>
#include <softadastra/cli/utils/Style.hpp>
#include <softadastra/cli/utils/Ui.hpp>

namespace softadastra::cli
{
  namespace cli_command = softadastra::cli::command;
  namespace cli_io = softadastra::cli::io;
  namespace cli_types = softadastra::cli::types;
  namespace ui = softadastra::cli::utils::ui;
  namespace style = softadastra::cli::utils::style;

  CliService::CliService(const cli_core::CliConfig &config)
      : config_(config),
        registry_{},
        session_{},
        context_{},
        engine_([&]() -> cli_core::CliContext &
                {
                  context_.config = &config_;
                  context_.registry = &registry_;
                  context_.session = &session_;
                  return context_; }())
  {
    const auto definitions = cli_command::BuiltinCommand::definitions();
    const auto handlers = cli_command::BuiltinCommand::handlers(context_);

    const std::size_t count =
        definitions.size() < handlers.size()
            ? definitions.size()
            : handlers.size();

    for (std::size_t i = 0; i < count; ++i)
    {
      registry_.register_command(definitions[i], handlers[i]);
    }
  }

  int CliService::run(const CliOptions &options)
  {
    if (!config_.valid() || !options.valid())
    {
      ui::err_line(cli_io::Console::err(), "Invalid CLI configuration.");
      return 1;
    }

    if (!engine_.start())
    {
      ui::err_line(cli_io::Console::err(), "Failed to start CLI engine.");
      return 1;
    }

    if (options.has_command())
    {
      const int exit_code = run_single(options.command);
      engine_.stop();
      return exit_code;
    }

    if (options.interactive)
    {
      return run_interactive();
    }

    engine_.stop();
    return 0;
  }

  void CliService::register_command(
      const cli_command::CliCommand &command,
      std::shared_ptr<cli_command::ICommandHandler> handler)
  {
    registry_.register_command(command, std::move(handler));
  }

  const cli_core::CliConfig &CliService::config() const noexcept
  {
    return config_;
  }

  cli_command::CommandRegistry &CliService::registry() noexcept
  {
    return registry_;
  }

  const cli_command::CommandRegistry &CliService::registry() const noexcept
  {
    return registry_;
  }

  cli_core::CliSession &CliService::session() noexcept
  {
    return session_;
  }

  const cli_core::CliSession &CliService::session() const noexcept
  {
    return session_;
  }

  cli_engine::CliEngine &CliService::engine() noexcept
  {
    return engine_;
  }

  const cli_engine::CliEngine &CliService::engine() const noexcept
  {
    return engine_;
  }

  int CliService::run_interactive()
  {
    if (config_.show_banner)
    {
      cli_io::Console::writeln(
          std::string(style::BOLD) +
          style::CYAN +
          config_.app_name +
          style::RESET +
          " CLI ready.");

      ui::tip_line(
          cli_io::Console::out(),
          "Run 'help' to list available commands.");
    }

    while (engine_.running())
    {
      const auto input =
          cli_io::InputReader::read_line("> ");

      if (!input.has_value())
      {
        cli_io::Console::writeln("");
        break;
      }

      if (input->empty())
      {
        continue;
      }

      const auto result = engine_.execute(*input);

      if (result == cli_types::CliErrorCode::CommandNotFound)
      {
        ui::err_line(cli_io::Console::err(), "Command not found.");
        ui::tip_line(cli_io::Console::err(), "Run 'help' to list available commands.");
      }
      else if (result != cli_types::CliErrorCode::None)
      {
        ui::err_line(
            cli_io::Console::err(),
            std::string("Command failed: ") +
                std::string(cli_types::to_string(result)));
      }

      if (!engine_.running())
      {
        break;
      }
    }

    engine_.stop();
    return 0;
  }

  int CliService::run_single(std::string_view command)
  {
    const auto result = engine_.execute(command);

    if (result != cli_types::CliErrorCode::None)
    {
      ui::err_line(
          cli_io::Console::err(),
          std::string("Command failed: ") +
              std::string(cli_types::to_string(result)));

      return to_exit_code(result);
    }

    return 0;
  }

  int CliService::to_exit_code(
      cli_types::CliErrorCode code) noexcept
  {
    if (code == cli_types::CliErrorCode::None)
    {
      return 0;
    }

    if (cli_types::is_user_error(code))
    {
      return 2;
    }

    if (code == cli_types::CliErrorCode::CommandNotFound ||
        code == cli_types::CliErrorCode::UnknownCommand)
    {
      return 127;
    }

    if (code == cli_types::CliErrorCode::PermissionDenied)
    {
      return 126;
    }

    return 1;
  }

} // namespace softadastra::cli
