/*
 * CliEngineTests.cpp
 */

#include <cassert>
#include <iostream>
#include <memory>

#include <softadastra/cli/engine/CliEngine.hpp>
#include <softadastra/cli/command/CommandRegistry.hpp>
#include <softadastra/cli/command/CliCommand.hpp>
#include <softadastra/cli/command/ICommandHandler.hpp>
#include <softadastra/cli/core/CliConfig.hpp>
#include <softadastra/cli/core/CliContext.hpp>

using namespace softadastra::cli;

namespace
{
  class DummyHandler : public command::ICommandHandler
  {
  public:
    types::CliErrorCode handle(const parser::ParsedCommand &) override
    {
      return types::CliErrorCode::None;
    }
  };

  engine::CliEngine make_engine()
  {
    static core::CliConfig config{"test-cli", "1.0.0"};
    static command::CommandRegistry registry;

    // register one command
    command::CliCommand cmd{
        "test",
        "test command",
        "test",
        types::CliCommandType::Custom};

    registry.register_command(cmd, std::make_shared<DummyHandler>());

    static core::CliContext context;
    context.config = &config;
    context.registry = &registry;

    return engine::CliEngine(context);
  }

  void test_start()
  {
    auto engine = make_engine();

    const bool started = engine.start();
    assert(started);
    assert(engine.running());
  }

  void test_parse()
  {
    auto engine = make_engine();
    engine.start();

    const auto parsed = engine.parse("test arg1 arg2");

    assert(parsed.has_value());
    assert(parsed->name == "test");
    assert(parsed->args.size() == 2);
  }

  void test_execute_success()
  {
    auto engine = make_engine();
    engine.start();

    const auto result = engine.execute("test");

    assert(result == types::CliErrorCode::None);
  }

  void test_execute_unknown_command()
  {
    auto engine = make_engine();
    engine.start();

    const auto result = engine.execute("unknown");

    assert(result == types::CliErrorCode::CommandNotFound);
  }
}

int main()
{
  test_start();
  test_parse();
  test_execute_success();
  test_execute_unknown_command();

  std::cout << "[OK] CliEngineTests passed\n";
  return 0;
}
