/*
 * CommandRegistryTests.cpp
 */

#include <cassert>
#include <iostream>
#include <memory>

#include <softadastra/cli/command/CliCommand.hpp>
#include <softadastra/cli/command/CommandRegistry.hpp>
#include <softadastra/cli/command/ICommandHandler.hpp>
#include <softadastra/cli/parser/ParsedCommand.hpp>
#include <softadastra/cli/types/CliCommandType.hpp>
#include <softadastra/cli/types/CliErrorCode.hpp>

using namespace softadastra::cli::command;

namespace
{
  namespace cli_parser = softadastra::cli::parser;
  namespace cli_types = softadastra::cli::types;

  class DummyHandler final : public ICommandHandler
  {
  public:
    [[nodiscard]] cli_types::CliErrorCode handle(
        const cli_parser::ParsedCommand &) override
    {
      return cli_types::CliErrorCode::None;
    }
  };

  void test_register_and_exists()
  {
    CommandRegistry registry;

    CliCommand cmd{
        "test",
        "test command",
        "test",
        cli_types::CliCommandType::Custom,
    };

    registry.register_command(
        cmd,
        std::make_shared<DummyHandler>());

    assert(registry.exists("test"));
    assert(registry.size() == 1);
    assert(!registry.empty());
  }

  void test_find_command()
  {
    CommandRegistry registry;

    CliCommand cmd{
        "build",
        "build project",
        "build",
        cli_types::CliCommandType::Custom,
    };

    registry.register_command(
        cmd,
        std::make_shared<DummyHandler>());

    const auto found = registry.find_command("build");

    assert(found.has_value());
    assert(found->name == "build");
    assert(found->description == "build project");
  }

  void test_get_handler()
  {
    CommandRegistry registry;

    CliCommand cmd{
        "run",
        "run project",
        "run",
        cli_types::CliCommandType::Custom,
    };

    const auto handler = std::make_shared<DummyHandler>();

    registry.register_command(cmd, handler);

    const auto result = registry.get_handler("run");

    assert(result != nullptr);
    assert(result == handler);
  }

  void test_alias()
  {
    CommandRegistry registry;

    CliCommand cmd{
        "help",
        "show help",
        "help",
        cli_types::CliCommandType::Info,
        {"h"},
    };

    registry.register_command(
        cmd,
        std::make_shared<DummyHandler>());

    assert(registry.exists("help"));
    assert(registry.exists("h"));

    const auto found = registry.find_command("h");

    assert(found.has_value());
    assert(found->name == "help");

    const auto handler = registry.get_handler("h");
    assert(handler != nullptr);
  }

  void test_all_commands_returns_unique_commands()
  {
    CommandRegistry registry;

    CliCommand cmd{
        "help",
        "show help",
        "help",
        cli_types::CliCommandType::Info,
        {"h", "?"},
    };

    registry.register_command(
        cmd,
        std::make_shared<DummyHandler>());

    const auto commands = registry.all_commands();

    assert(commands.size() == 1);
    assert(commands.front().name == "help");
  }

  void test_clear()
  {
    CommandRegistry registry;

    CliCommand cmd{
        "status",
        "show status",
        "status",
        cli_types::CliCommandType::Info,
        {"st"},
    };

    registry.register_command(
        cmd,
        std::make_shared<DummyHandler>());

    assert(!registry.empty());
    assert(registry.exists("status"));
    assert(registry.exists("st"));

    registry.clear();

    assert(registry.empty());
    assert(registry.size() == 0);
    assert(!registry.exists("status"));
    assert(!registry.exists("st"));
    assert(registry.all_commands().empty());
  }

  void test_invalid_command_is_ignored()
  {
    CommandRegistry registry;

    CliCommand cmd{
        "",
        "invalid command",
        "",
        cli_types::CliCommandType::Custom,
    };

    registry.register_command(
        cmd,
        std::make_shared<DummyHandler>());

    assert(registry.empty());
    assert(registry.size() == 0);
  }

  void test_null_handler_is_ignored()
  {
    CommandRegistry registry;

    CliCommand cmd{
        "broken",
        "broken command",
        "broken",
        cli_types::CliCommandType::Custom,
    };

    registry.register_command(cmd, nullptr);

    assert(registry.empty());
    assert(registry.size() == 0);
    assert(!registry.exists("broken"));
  }
}

int main()
{
  test_register_and_exists();
  test_find_command();
  test_get_handler();
  test_alias();
  test_all_commands_returns_unique_commands();
  test_clear();
  test_invalid_command_is_ignored();
  test_null_handler_is_ignored();

  std::cout << "[OK] CommandRegistryTests passed\n";
  return 0;
}
