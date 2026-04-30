# CLI Guide

The Softadastra CLI module provides the command-line foundation for Softadastra infrastructure.

It is the human and automation entry layer used to interact with Softadastra modules.

The core rule is:

> *CLI owns interaction. Application code owns meaning.*

## Why Softadastra needs CLI

Each module in the stack has one responsibility:

```
WAL        →  durability
Store      →  local state
Sync       →  operation propagation logic
Transport  →  message delivery
Discovery  →  peer discovery
Metadata   →  node identity and runtime information
CLI        →  operator and developer interaction
```

The CLI module does not decide what a store command, sync command, transport command, or node command means.

It only provides:

- input parsing
- command metadata
- command registration
- command dispatch
- session lifecycle
- terminal output helpers
- help and table formatting
- a high-level CLI service

Command handlers own the real behavior.

## What CLI guarantees

- raw input can be tokenized consistently
- quoted strings are preserved
- escaped characters are handled
- command names and arguments can be parsed
- options can be parsed into typed values
- commands can be registered with handlers
- aliases can resolve to canonical commands
- help output can be generated from command metadata
- CLI session state can be observed
- single-command mode can be executed
- interactive mode can be executed
- terminal output can be formatted consistently

> CLI does not guarantee infrastructure correctness by itself.
> Correctness belongs to the underlying module invoked by a command handler.

## What CLI does NOT do

- WAL persistence
- store mutation logic
- sync conflict resolution
- transport delivery
- peer discovery
- metadata ownership
- daemon supervision
- shell execution
- authentication
- permission policy enforcement
- distributed consensus

## Installation

```bash
vix add @softadastra/cli
```

## Main header

```cpp
#include <softadastra/cli/cli.hpp>
```

For direct integration:

```cpp
#include <softadastra/cli/CliService.hpp>
#include <softadastra/cli/core/CliConfig.hpp>
#include <softadastra/cli/command/CliCommand.hpp>
#include <softadastra/cli/command/ICommandHandler.hpp>
```

## Main concepts

- `CliConfig`
- `CliOptions`
- `CliStatus`
- `CliErrorCode`
- `CliCommandType`
- `OptionValue`
- `CliOption`
- `CliCommand`
- `ICommandHandler`
- `CommandRegistry`
- `BuiltinCommand`
- `Tokenizer`
- `CommandLine`
- `ArgParser`
- `ParsedCommand`
- `CliSession`
- `CliContext`
- `CliApplication`
- `CliEngine`
- `CliService`
- `Console`
- `InputReader`
- `OutputWriter`
- `TerminalStyle`
- `HelpFormatter`
- `TableFormatter`
- `StringUtils`
- `Style`
- `Ui`

## CliConfig

Controls CLI runtime behavior.

```cpp
softadastra::cli::core::CliConfig config;

config.app_name    = "softadastra";
config.version     = "0.1.0";
config.interactive = true;
config.show_banner = true;
config.color_output = true;
config.verbose     = false;
config.strict_mode = true;

if (!config.valid())
{
    return 1;
}
```

Default config:

```cpp
auto config = softadastra::cli::core::CliConfig::defaults();
```

## CliOptions

Controls how the CLI starts.

**Interactive mode:**

```cpp
auto options = softadastra::cli::CliOptions::interactive_mode();
```

**Single-command mode:**

```cpp
auto options = softadastra::cli::CliOptions::single_command("help");
```

**Manual setup:**

```cpp
softadastra::cli::CliOptions options;

options.interactive = false;
options.command     = "status";

if (!options.valid())
{
    return 1;
}
```

## CLI lifecycle

The runtime status is represented by `CliStatus`.

**States:**

- `Idle`
- `Starting`
- `Running`
- `WaitingInput`
- `ExecutingCommand`
- `Stopping`
- `Stopped`
- `Failed`

**Helpers:**

```cpp
softadastra::cli::types::to_string(status);
softadastra::cli::types::is_active(status);
softadastra::cli::types::is_terminal(status);
softadastra::cli::types::is_transitioning(status);
```

## Error codes

`CliErrorCode` is the common return type for command execution.

**Common values:**

- `None`
- `InvalidState`
- `NotInitialized`
- `ParseError`
- `UnknownCommand`
- `InvalidArguments`
- `MissingArgument`
- `TooManyArguments`
- `CommandExecutionFailed`
- `CommandNotFound`
- `PermissionDenied`
- `InputError`
- `OutputError`
- `InternalError`
- `NotImplemented`

**Helpers:**

```cpp
softadastra::cli::types::to_string(code);
softadastra::cli::types::is_success(code);
softadastra::cli::types::is_user_error(code);
softadastra::cli::types::is_system_error(code);
```

## Command types

`CliCommandType` classifies commands.

**Values:**

- `Unknown`
- `Builtin`
- `Custom`
- `Info`
- `System`
- `Diagnostic`
- `Admin`

**Helpers:**

```cpp
softadastra::cli::types::to_string(type);
softadastra::cli::types::is_known(type);
softadastra::cli::types::is_mutating(type);
```

**Recommended usage:**

| Type         | Commands                              |
|--------------|---------------------------------------|
| `Info`       | help, version, status, inspect        |
| `Diagnostic` | health, debug, trace, check           |
| `Admin`      | start, stop, reset, configure         |
| `System`     | exit, clear                           |
| `Custom`     | application-defined commands          |

## Parsing model

The parsing flow is intentionally separated from execution.

```
raw input
  → Tokenizer
  → CommandLine
  → ArgParser
  → ParsedCommand
```

### Tokenizer

Splits raw input into tokens.

Handles: spaces, repeated spaces, double quotes, single quotes, escaped spaces, escaped quotes, trailing escape characters.

```cpp
auto tokens =
    softadastra::cli::parser::Tokenizer::tokenize(
        R"(store-put name "Softadastra Runtime")");

// Result: ["store-put", "name", "Softadastra Runtime"]
```

Escaped space:

```cpp
auto tokens =
    softadastra::cli::parser::Tokenizer::tokenize(
        R"(store-put title hello\ world)");

// Result: ["store-put", "title", "hello world"]
```

### CommandLine

Stores tokenized input.

```cpp
softadastra::cli::parser::CommandLine line{
    {"store-put", "name", "hello"}};

line.command();    // "store-put"
line.arguments();  // ["name", "hello"]
line.size();       // 3
line.empty();      // false
```

### ArgParser

Converts `CommandLine` into `ParsedCommand`.

**Supported option forms:**

- `--flag`
- `--key=value`
- `--key value`
- `-f`
- `-k value`

**Example:**

```cpp
softadastra::cli::parser::CommandLine line{
    {"node-start", "--host", "127.0.0.1", "--port", "7000", "--verbose"}};

auto parsed =
    softadastra::cli::parser::ArgParser::parse(line);

parsed.name;                          // "node-start"
parsed.has_option("host");            // true
parsed.has_option("port");            // true
parsed.option_enabled("verbose");
parsed.option_string_or("host", "0.0.0.0");
```

### ParsedCommand

Represents a fully parsed command.

```cpp
softadastra::cli::parser::ParsedCommand command;

command.name = "status";
command.args = {"node-a"};

if (!command.valid())
{
    return 1;
}

if (command.has_option("json"))
{
    // render JSON output
}

const auto *value = command.get_option("port");

if (value != nullptr)
{
    // inspect typed OptionValue
}
```

## OptionValue

Options are typed:

```cpp
using OptionValue = std::variant<
    std::monostate,
    bool,
    std::int64_t,
    double,
    std::string>;
```

**Helpers:**

```cpp
softadastra::cli::types::is_bool(value);
softadastra::cli::types::is_integer(value);
softadastra::cli::types::is_double(value);
softadastra::cli::types::is_string(value);
softadastra::cli::types::option_value_type(value);
```

**Example:**

```cpp
const auto *port = parsed.get_option("port");

if (port != nullptr &&
    std::holds_alternative<std::int64_t>(*port))
{
    auto value = std::get<std::int64_t>(*port);
}
```

## CliOption

Describes one supported option.

```cpp
softadastra::cli::command::CliOption option{
    "port",
    "p",
    "Port to bind",
    "PORT",
    true,
    false};
```

**Fields:**

| Field         | Description                              |
|---------------|------------------------------------------|
| `name`        | Long option name without `--`            |
| `short_name`  | Short option name without `-`            |
| `description` | Help text                                |
| `value_name`  | Placeholder shown in help                |
| `takes_value` | `true` if option expects a value         |
| `required`    | `true` if option is required             |

**Validation:**

```cpp
option.valid();
option.has_short_name();
option.has_description();
option.has_value_name();
```

## CliCommand

Describes one command.

```cpp
softadastra::cli::command::CliCommand command{
    "node-start",
    "Start a Softadastra node",
    "node-start --host HOST --port PORT",
    softadastra::cli::types::CliCommandType::Admin,
    {"start"},
    {
        {"host", "h", "Bind host", "HOST", true, false},
        {"port", "p", "Bind port", "PORT", true, true},
    }};

command.valid();
command.matches("node-start");
command.matches("start");
command.has_aliases();
command.has_options();
command.find_option("port");
```

## ICommandHandler

Command execution is implemented by handlers.

```cpp
class StatusHandler final
    : public softadastra::cli::command::ICommandHandler
{
public:
    [[nodiscard]] softadastra::cli::types::CliErrorCode handle(
        const softadastra::cli::parser::ParsedCommand &command) override
    {
        (void)command;

        std::cout << "Softadastra status: healthy\n";

        return softadastra::cli::types::CliErrorCode::None;
    }
};
```

A handler should:

- validate command-specific arguments
- execute the command
- print output when needed
- return a precise `CliErrorCode`

## CommandRegistry

Stores command definitions and handlers.

```cpp
softadastra::cli::command::CommandRegistry registry;

registry.register_command(
    command,
    std::make_shared<StatusHandler>());

registry.exists("node-start");
registry.exists("start");

auto found   = registry.find_command("start");
auto handler = registry.get_handler("node-start");

auto commands = registry.all_commands();

registry.clear();
```

> `all_commands()` returns canonical commands only. Aliases are not duplicated.

## Built-in commands

`BuiltinCommand` provides default commands.

| Command | Aliases      | Description              |
|---------|--------------|--------------------------|
| `help`  | `h`          | Show help information    |
| `version` | `v`        | Show CLI version         |
| `exit`  | `quit`, `q`  | Exit CLI session         |

Built-ins are registered automatically by `CliService`.

**Manual registration:**

```cpp
auto definitions =
    softadastra::cli::command::BuiltinCommand::definitions();

auto handlers =
    softadastra::cli::command::BuiltinCommand::handlers(context);

for (std::size_t i = 0; i < definitions.size(); ++i)
{
    registry.register_command(definitions[i], handlers[i]);
}
```

## CliSession

Tracks one CLI session.

```cpp
softadastra::cli::core::CliSession session;

session.start();

session.set_last_command("status");
session.increment_command_count();

session.request_stop();
session.stop();

session.running();
session.stop_requested();
session.status();
session.last_command();
session.command_count();

session.reset();
```

## CliContext

References shared runtime objects.

```cpp
softadastra::cli::core::CliContext context;

context.config   = &config;
context.registry = &registry;
context.session  = &session;

if (!context.valid())
{
    return 1;
}

auto &cfg = context.config_ref();
auto &reg = context.registry_ref();
auto &ses = context.session_ref();
```

## CliApplication

Executes parsed commands using the registry.

```cpp
softadastra::cli::core::CliApplication app{context};

if (!app.start())
{
    return 1;
}

auto result = app.execute(parsed);

app.stop();
```

**Application responsibilities:**

- validate context
- start session
- stop session
- resolve handlers
- dispatch parsed commands
- handle `--help` and `-h`
- update session state

## CliEngine

Parses raw input and executes commands.

```cpp
softadastra::cli::engine::CliEngine engine{context};

if (!engine.start())
{
    return 1;
}

auto parsed = engine.parse("status");

if (parsed.has_value())
{
    engine.execute(*parsed);
}

engine.execute("help");
engine.stop();
```

**Engine responsibilities:**

- manage engine status
- tokenize raw input
- parse command arguments
- execute parsed commands
- delegate execution to `CliApplication`

## CliService

The public high-level entry point.

### Single command

```cpp
#include <softadastra/cli/cli.hpp>

int main()
{
    softadastra::cli::core::CliConfig config;

    config.app_name    = "softadastra";
    config.version     = "0.1.0";
    config.interactive = false;
    config.show_banner = false;

    softadastra::cli::CliService service{config};

    return service.run(
        softadastra::cli::CliOptions::single_command("help"));
}
```

### Custom command

```cpp
#include <iostream>
#include <memory>

#include <softadastra/cli/cli.hpp>

class StatusHandler final
    : public softadastra::cli::command::ICommandHandler
{
public:
    [[nodiscard]] softadastra::cli::types::CliErrorCode handle(
        const softadastra::cli::parser::ParsedCommand &) override
    {
        std::cout << "Softadastra status: healthy\n";
        return softadastra::cli::types::CliErrorCode::None;
    }
};

int main()
{
    softadastra::cli::core::CliConfig config;

    config.app_name    = "softadastra";
    config.version     = "0.1.0";
    config.interactive = false;
    config.show_banner = false;

    softadastra::cli::CliService service{config};

    service.register_command(
        softadastra::cli::command::CliCommand{
            "status",
            "Show Softadastra runtime status",
            "status",
            softadastra::cli::types::CliCommandType::Info,
            {"st"},
            {},
        },
        std::make_shared<StatusHandler>());

    return service.run(
        softadastra::cli::CliOptions::single_command("status"));
}
```

### Interactive mode

```cpp
#include <softadastra/cli/cli.hpp>

int main()
{
    softadastra::cli::core::CliConfig config;

    config.app_name    = "softadastra";
    config.version     = "0.1.0";
    config.interactive = true;
    config.show_banner = true;

    softadastra::cli::CliService service{config};

    return service.run(
        softadastra::cli::CliOptions::interactive_mode());
}
```

## I/O helpers

### Console

```cpp
softadastra::cli::io::Console::write("hello");
softadastra::cli::io::Console::writeln("hello");

softadastra::cli::io::Console::error("error");
softadastra::cli::io::Console::errorln("error");

softadastra::cli::io::Console::clear();
softadastra::cli::io::Console::move_cursor_home();

auto &out = softadastra::cli::io::Console::out();
auto &err = softadastra::cli::io::Console::err();
```

### InputReader

```cpp
auto line =
    softadastra::cli::io::InputReader::read_line("> ");

if (!line.has_value())
{
    return 1;
}
```

Custom stream:

```cpp
std::istringstream input{"status\n"};

auto line =
    softadastra::cli::io::InputReader::read_line(input);
```

### OutputWriter

```cpp
softadastra::cli::io::OutputWriter::write("hello");
softadastra::cli::io::OutputWriter::writeln("hello");

softadastra::cli::io::OutputWriter::error("error");
softadastra::cli::io::OutputWriter::errorln("error");
```

Custom stream:

```cpp
std::ostringstream out;

softadastra::cli::io::OutputWriter::writeln(out, "test");
```

### TerminalStyle

```cpp
using softadastra::cli::io::TerminalStyle;

std::cout << TerminalStyle::success("ok")      << "\n";
std::cout << TerminalStyle::error("failed")    << "\n";
std::cout << TerminalStyle::warning("warning") << "\n";
std::cout << TerminalStyle::info("info")       << "\n";
std::cout << TerminalStyle::muted("muted")     << "\n";
std::cout << TerminalStyle::strong("strong")   << "\n";
std::cout << TerminalStyle::link("https://softadastra.com") << "\n";
```

## UI helpers

### Style

```cpp
namespace style = softadastra::cli::utils::style;

std::cout << style::BOLD << style::CYAN
          << "Softadastra"
          << style::RESET
          << "\n";

std::cout << style::bold("strong") << "\n";
std::cout << style::dim("muted")   << "\n";
std::cout << style::link("https://github.com/softadastra/softadastra") << "\n";
```

### Ui

```cpp
namespace ui = softadastra::cli::utils::ui;

ui::section(std::cout, "Softadastra CLI");

ui::ok_line(std::cout,   "Runtime initialized");
ui::info_line(std::cout, "Loading registry");
ui::warn_line(std::cout, "Experimental command enabled");
ui::err_line(std::cout,  "Command failed");

ui::kv(std::cout, "app",     "softadastra");
ui::kv(std::cout, "version", "0.1.0");

ui::tip_line(std::cout, "Run 'help' to list available commands.");
```

## Formatters

### HelpFormatter

Full help:

```cpp
auto help =
    softadastra::cli::utils::HelpFormatter::format(
        registry.all_commands(),
        "softadastra");

std::cout << help;
```

Command help:

```cpp
auto text =
    softadastra::cli::utils::HelpFormatter::format_command(command);
```

### TableFormatter

```cpp
std::vector<std::string> headers{
    "Command",
    "Type",
    "Description",
};

std::vector<std::vector<std::string>> rows{
    {"help",    "info",   "Show help information"},
    {"version", "info",   "Show CLI version"},
    {"exit",    "system", "Exit CLI session"},
};

std::cout << softadastra::cli::utils::TableFormatter::format(
    headers,
    rows);
```

### StringUtils

```cpp
using softadastra::cli::utils::StringUtils;

StringUtils::trim("  hello  ");
StringUtils::to_lower("HELLO");
StringUtils::starts_with("softadastra", "soft");
StringUtils::ends_with("softadastra", "astra");
StringUtils::is_blank("   ");

auto parts  = StringUtils::split("a,b,c", ',');
auto joined = StringUtils::join(parts, "/");
```

## End-to-end command flow

1. CLI service starts
2. Built-in commands are registered
3. Custom commands are registered
4. Engine starts
5. Raw input enters the engine
6. Tokenizer splits raw input into tokens
7. `CommandLine` stores tokens
8. `ArgParser` produces `ParsedCommand`
9. `CliApplication` checks session state
10. `CommandRegistry` resolves command or alias
11. `ICommandHandler` executes command logic
12. Handler returns `CliErrorCode`
13. `CliSession` records last command and command count
14. `CliEngine` restores runtime status
15. `CliService` maps error code to process exit code when needed

## Minimal example

```cpp
#include <softadastra/cli/cli.hpp>

int main()
{
    softadastra::cli::core::CliConfig config;

    config.app_name    = "softadastra";
    config.version     = "0.1.0";
    config.interactive = false;
    config.show_banner = false;

    softadastra::cli::CliService service{config};

    return service.run(
        softadastra::cli::CliOptions::single_command("version"));
}
```

## Custom command example

```cpp
#include <iostream>
#include <memory>

#include <softadastra/cli/cli.hpp>

class NodeInfoHandler final
    : public softadastra::cli::command::ICommandHandler
{
public:
    [[nodiscard]] softadastra::cli::types::CliErrorCode handle(
        const softadastra::cli::parser::ParsedCommand &) override
    {
        std::cout << "node: local\n";
        std::cout << "status: running\n";

        return softadastra::cli::types::CliErrorCode::None;
    }
};

int main()
{
    softadastra::cli::core::CliConfig config;

    config.app_name    = "softadastra";
    config.version     = "0.1.0";
    config.interactive = false;
    config.show_banner = false;

    softadastra::cli::CliService service{config};

    service.register_command(
        softadastra::cli::command::CliCommand{
            "node-info",
            "Show local node information",
            "node-info",
            softadastra::cli::types::CliCommandType::Info,
            {"info"},
            {},
        },
        std::make_shared<NodeInfoHandler>());

    return service.run(
        softadastra::cli::CliOptions::single_command("node-info"));
}
```

## Testing helpers

The CLI module is designed to be testable.

**Input testing with custom streams:**

```cpp
std::istringstream input{"status\n"};

auto line =
    softadastra::cli::io::InputReader::read_line(input);
```

**Output testing with custom streams:**

```cpp
std::ostringstream out;

softadastra::cli::io::OutputWriter::writeln(out, "hello");

if (out.str() != "hello\n")
{
    return 1;
}
```

**Handler testing:**

```cpp
StatusHandler handler;

softadastra::cli::parser::ParsedCommand command;
command.name = "status";

auto result = handler.handle(command);
```

**Registry testing:**

```cpp
softadastra::cli::command::CommandRegistry registry;

registry.register_command(command, handler);

if (!registry.exists("status"))
{
    return 1;
}
```

## Examples

| Example                   | Description                          |
|---------------------------|--------------------------------------|
| `cli_minimal.cpp`         | Minimal CLI setup                    |
| `cli_commands_demo.cpp`   | Command registration demo            |
| `cli_tokenizer.cpp`       | Tokenization example                 |
| `cli_arg_parser.cpp`      | Argument parsing example             |
| `cli_table_formatter.cpp` | Table formatting example             |
| `cli_ui_style.cpp`        | UI and style helpers                 |
| `cli_registry.cpp`        | Command registry and alias lookup    |
| `cli_custom_command.cpp`  | Custom command with handler          |
| `cli_service_single.cpp`  | Single-command service execution     |

**Build examples:**

```bash
vix build
```

Or with CMake:

```bash
cmake -S . -B build -DSOFTADASTRA_CLI_BUILD_EXAMPLES=ON
cmake --build build
```

## Production notes

- use precise `CliErrorCode` values
- keep command handlers small
- keep parsing separate from execution
- do not put infrastructure business logic inside the CLI module
- use `CliCommandType::Admin` for mutating operational commands
- use `CliCommandType::Diagnostic` for inspection commands
- use `CliCommandType::Info` for read-only informational commands
- prefer `TableFormatter` for lists
- prefer `HelpFormatter` for public help text
- prefer `Console` or `OutputWriter` for output abstraction
- keep aliases short and obvious
- keep output deterministic when scripts depend on it
- avoid interactive prompts in automation mode
- add `--json` later for machine-readable output
- add no-color mode for CI and logs
- every public command should have usage text
- every command should return a stable error code

## Design rules

- CLI owns interaction
- application code owns meaning
- parser does not execute
- registry does not execute
- engine does not own business logic
- application dispatches commands
- handlers execute commands
- service owns runtime wiring
- session is the single lifecycle source of truth
- help is generated from command metadata
- aliases must resolve to canonical commands
- error codes must remain stable
- output must remain readable by humans
- future JSON output must remain readable by machines
- command handlers must not depend on parser internals
- built-in commands must remain small and predictable

## Roadmap

- [x] Public `cli.hpp` aggregator
- [x] CLI configuration
- [x] CLI startup options
- [x] Command metadata
- [x] Command options
- [x] Command handlers
- [x] Command registry
- [x] Built-in commands
- [x] Tokenizer
- [x] Argument parser
- [x] Parsed command model
- [x] CLI session
- [x] CLI context
- [x] CLI application
- [x] CLI engine
- [x] CLI service
- [x] Console helpers
- [x] Input reader
- [x] Output writer
- [x] Terminal style helpers
- [x] Help formatter
- [x] Table formatter
- [x] UI helpers
- [ ] Command groups
- [ ] Nested subcommands
- [ ] Shell completion
- [ ] Structured JSON output
- [ ] No-color mode
- [ ] Config file loading
- [ ] Command middleware
- [ ] Permission hooks
- [ ] Audit logging hooks
- [ ] Metrics hooks
- [ ] Better malformed input diagnostics
- [ ] Documentation generation from command metadata

## Summary

`softadastra/cli` provides:

- parsing
- command metadata
- command registration
- command dispatch
- session lifecycle
- built-in commands
- terminal I/O
- styled output
- help formatting
- table formatting
- high-level service execution

Its job is simple: provide a clean, reliable command-line entry point for Softadastra infrastructure without owning infrastructure business logic.
