/*
 * CliService.cpp
 */

#include <iostream>

#include <softadastra/cli/CliService.hpp>
#include <softadastra/cli/command/BuiltinCommand.hpp>
#include <softadastra/cli/io/InputReader.hpp>
#include <softadastra/cli/io/Console.hpp>

namespace softadastra::cli
{
  namespace cli_command = softadastra::cli::command;
  namespace cli_io = softadastra::cli::io;

  CliService::CliService(const cli_core::CliConfig &config)
      : config_(config),
        registry_{},
        context_{},
        engine_([&]() -> cli_core::CliContext &
                {
                  context_.config = &config_;
                  context_.registry = &registry_;
                  return context_; }())
  {
    // Register built-in commands
    const auto defs = cli_command::BuiltinCommand::definitions();
    const auto handlers = cli_command::BuiltinCommand::handlers();

    for (std::size_t i = 0; i < defs.size(); ++i)
    {
      registry_.register_command(defs[i], handlers[i]);
    }
  }

  int CliService::run(const CliOptions &options)
  {
    if (!config_.valid() || !options.valid())
    {
      return 1;
    }

    if (!engine_.start())
    {
      return 1;
    }

    if (!options.command.empty())
    {
      return run_single(options.command);
    }

    if (options.interactive)
    {
      return run_interactive();
    }

    return 0;
  }

  int CliService::run_interactive()
  {
    cli_io::Console::writeln("Softadastra CLI ready.");

    while (engine_.running())
    {
      const auto input = cli_io::InputReader::read_line("> ");

      if (input.empty())
      {
        continue;
      }

      const auto result = engine_.execute(input);

      if (result == types::CliErrorCode::CommandNotFound)
      {
        cli_io::Console::errorln("Command not found.");
      }

      // Exit handling (simple for now)
      if (input == "exit" || input == "quit")
      {
        break;
      }
    }

    engine_.stop();
    return 0;
  }

  int CliService::run_single(const std::string &command)
  {
    const auto result = engine_.execute(command);

    if (result != types::CliErrorCode::None)
    {
      cli_io::Console::errorln("Command failed.");
      return 1;
    }

    return 0;
  }

} // namespace softadastra::cli
