/*
 * CommandRegistryTests.cpp
 */

#include <cassert>
#include <iostream>
#include <memory>

#include <softadastra/cli/command/CommandRegistry.hpp>
#include <softadastra/cli/command/CliCommand.hpp>
#include <softadastra/cli/command/ICommandHandler.hpp>

using namespace softadastra::cli::command;

namespace
{
  class DummyHandler : public ICommandHandler
  {
  public:
    types::CliErrorCode handle(const parser::ParsedCommand &) override
    {
      return types::CliErrorCode::None;
    }
  };

  void test_register_and_exists()
  {
    CommandRegistry registry;

    CliCommand cmd(
        "test",
        "test command",
        "test",
        types::CliCommandType::Custom);

    registry.register_command(cmd, std::make_shared<DummyHandler>());

    assert(registry.exists("test"));
  }

  void test_find_command()
  {
    CommandRegistry registry;

    CliCommand cmd(
        "build",
        "build project",
        "build",
        types::CliCommandType::Custom);

    registry.register_command(cmd, std::make_shared<DummyHandler>());

    auto found = registry.find_command("build");
    assert(found.has_value());
    assert(found->name == "build");
  }

  void test_get_handler()
  {
    CommandRegistry registry;

    CliCommand cmd(
        "run",
        "run project",
        "run",
        types::CliCommandType::Custom);

    auto handler = std::make_shared<DummyHandler>();
    registry.register_command(cmd, handler);

    auto result = registry.get_handler("run");
    assert(result != nullptr);
  }

  void test_alias()
  {
    CommandRegistry registry;

    CliCommand cmd(
        "help",
        "show help",
        "help",
        types::CliCommandType::Info,
        {"h"});

    registry.register_command(cmd, std::make_shared<DummyHandler>());

    assert(registry.exists("help"));
    assert(registry.exists("h"));

    auto found = registry.find_command("h");
    assert(found.has_value());
    assert(found->name == "help");
  }

  void test_all_commands_returns_unique_commands()
  {
    CommandRegistry registry;

    CliCommand cmd(
        "help",
        "show help",
        "help",
        types::CliCommandType::Info,
        {"h", "?"});

    registry.register_command(cmd, std::make_shared<DummyHandler>());

    const auto commands = registry.all_commands();
    assert(commands.size() == 1);
    assert(commands.front().name == "help");
  }
}

int main()
{
  test_register_and_exists();
  test_find_command();
  test_get_handler();
  test_alias();
  test_all_commands_returns_unique_commands();

  std::cout << "[OK] CommandRegistryTests passed\n";
  return 0;
}
