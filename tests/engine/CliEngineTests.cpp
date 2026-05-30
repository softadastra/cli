/*
 * CliEngineTests.cpp
 */

#include <cassert>
#include <iostream>
#include <memory>

#include <softadastra/cli/command/CliCommand.hpp>
#include <softadastra/cli/command/CommandRegistry.hpp>
#include <softadastra/cli/command/ICommandHandler.hpp>
#include <softadastra/cli/core/CliConfig.hpp>
#include <softadastra/cli/core/CliContext.hpp>
#include <softadastra/cli/core/CliSession.hpp>
#include <softadastra/cli/engine/CliEngine.hpp>
#include <softadastra/cli/parser/ParsedCommand.hpp>
#include <softadastra/cli/types/CliCommandType.hpp>
#include <softadastra/cli/types/CliErrorCode.hpp>

using namespace softadastra::cli;

namespace
{
  class DummyHandler final : public command::ICommandHandler
  {
  public:
    [[nodiscard]] types::CliErrorCode handle(
        const parser::ParsedCommand &) override
    {
      return types::CliErrorCode::None;
    }
  };

  struct EngineFixture
  {
    core::CliConfig config{};
    command::CommandRegistry registry{};
    core::CliSession session{};
    core::CliContext context{};
    engine::CliEngine engine;

    EngineFixture()
        : config{},
          registry{},
          session{},
          context{},
          engine([&]() -> core::CliContext &
                 {
                   config.app_name = "test-cli";
                   config.version = "1.0.0";
                   config.interactive = false;
                   config.show_banner = false;

                   context.config = &config;
                   context.registry = &registry;
                   context.session = &session;

                   return context; }())
    {
      command::CliCommand cmd{
          "test",
          "test command",
          "test",
          types::CliCommandType::Custom,
      };

      registry.register_command(
          cmd,
          std::make_shared<DummyHandler>());
    }
  };

  void test_start()
  {
    EngineFixture fixture;

    const bool started = fixture.engine.start();

    assert(started);
    assert(fixture.engine.running());
    assert(fixture.session.running());
    assert(fixture.engine.status() == types::CliStatus::Running);
  }

  void test_parse()
  {
    EngineFixture fixture;
    assert(fixture.engine.start());

    const auto parsed = fixture.engine.parse("test arg1 arg2");

    assert(parsed.has_value());
    assert(parsed->name == "test");
    assert(parsed->args.size() == 2);
    assert(parsed->args[0] == "arg1");
    assert(parsed->args[1] == "arg2");
  }

  void test_execute_success()
  {
    EngineFixture fixture;
    assert(fixture.engine.start());

    const auto result = fixture.engine.execute("test");

    assert(result == types::CliErrorCode::None);
    assert(fixture.session.last_command() == "test");
    assert(fixture.session.command_count() == 1);
    assert(fixture.engine.running());
  }

  void test_execute_unknown_command()
  {
    EngineFixture fixture;
    assert(fixture.engine.start());

    const auto result = fixture.engine.execute("unknown");

    assert(result == types::CliErrorCode::CommandNotFound);
    assert(fixture.engine.running());
  }

  void test_execute_empty_input()
  {
    EngineFixture fixture;
    assert(fixture.engine.start());

    const auto result = fixture.engine.execute("");

    assert(result == types::CliErrorCode::ParseError);
  }

  void test_stop()
  {
    EngineFixture fixture;
    assert(fixture.engine.start());

    fixture.engine.stop();

    assert(!fixture.engine.running());
    assert(!fixture.session.running());
    assert(fixture.engine.status() == types::CliStatus::Stopped);
  }
}

int main()
{
  test_start();
  test_parse();
  test_execute_success();
  test_execute_unknown_command();
  test_execute_empty_input();
  test_stop();

  std::cout << "[OK] CliEngineTests passed\n";
  return 0;
}
