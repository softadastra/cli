# softadastra/cli

> Command-line interface foundation for Softadastra infrastructure.

`softadastra/cli` is the CLI framework layer of Softadastra.

It provides command parsing, command registration, command execution, terminal output helpers, help formatting, and a high-level CLI service for building production-ready command-line tools.

The core rule is:

> *CLI owns interaction. Application code owns meaning.*

## Purpose

The CLI module provides the entry point for humans, scripts, local tools, servers, operators, and future automation layers to interact with Softadastra.

It helps Softadastra:

- parse raw command input
- tokenize command lines
- extract command names, arguments, and options
- register commands and aliases
- dispatch parsed commands to handlers
- format help output and tables
- style terminal output
- run single commands or interactive sessions
- expose a stable public CLI API

> The module does not decide what Softadastra store, sync, transport, metadata, or discovery commands mean.
> That belongs to the application or higher-level modules.

## What this module does

`softadastra/cli` provides:

- CLI configuration and startup options
- CLI session lifecycle
- command metadata, options, and handlers
- command registry and built-in commands
- raw input tokenizer and argument parser
- parsed command model
- CLI engine and application orchestrator
- CLI service facade
- console I/O helpers
- terminal styling, help formatter, and table formatter
- string utilities

## What this module does NOT do

- store data or write WAL records
- synchronize nodes or discover peers
- send transport messages
- manage metadata directly
- execute shell commands
- provide business logic for application commands
- own daemon lifecycle outside the CLI process
- replace higher-level Softadastra modules

## Design Principles

### CLI-first infrastructure

The CLI is not only a developer tool. It is also the first operator interface for: local node control, diagnostics, status inspection, sync testing, metadata inspection, store operations, and future automation.

### Small public surface

The high-level API is intentionally small:

```cpp
CliService service{config};
service.register_command(command, handler);
service.run(options);
```

The internal flow remains modular:

```
Tokenizer → CommandLine → ArgParser → ParsedCommand
  → CliEngine → CliApplication → CommandRegistry → ICommandHandler
```

### Stateless parsing

Parsing is separated from execution. The parser only transforms input into structure — it does not run commands and does not mutate infrastructure state.

### Observable session lifecycle

`CliSession` tracks: current status, running state, stop requests, last executed command, command count.

### Handlers own execution

The CLI module dispatches commands, but command handlers own execution logic. This keeps the CLI reusable for Softadastra root CLI, module-specific CLIs, embedded tools, tests, and internal automation.

## Module Structure

```
include/softadastra/cli/
├── cli.hpp
├── CliOptions.hpp
├── CliService.hpp
├── command/
│   ├── BuiltinCommand.hpp
│   ├── CliCommand.hpp
│   ├── CliOption.hpp
│   ├── CommandRegistry.hpp
│   └── ICommandHandler.hpp
├── core/
│   ├── CliApplication.hpp
│   ├── CliConfig.hpp
│   ├── CliContext.hpp
│   └── CliSession.hpp
├── engine/
│   └── CliEngine.hpp
├── io/
│   ├── Console.hpp
│   ├── InputReader.hpp
│   ├── OutputWriter.hpp
│   └── TerminalStyle.hpp
├── parser/
│   ├── ArgParser.hpp
│   ├── CommandLine.hpp
│   ├── ParsedCommand.hpp
│   └── Tokenizer.hpp
├── types/
│   ├── CliCommandType.hpp
│   ├── CliErrorCode.hpp
│   ├── CliStatus.hpp
│   └── OptionValue.hpp
└── utils/
    ├── HelpFormatter.hpp
    ├── StringUtils.hpp
    ├── Style.hpp
    ├── TableFormatter.hpp
    └── Ui.hpp
```

## Installation

```bash
vix add @softadastra/cli
```

### Main header

```cpp
#include <softadastra/cli/cli.hpp>
```

For direct component usage:

```cpp
#include <softadastra/cli/parser/Tokenizer.hpp>
#include <softadastra/cli/parser/ArgParser.hpp>
#include <softadastra/cli/command/CommandRegistry.hpp>
#include <softadastra/cli/CliService.hpp>
```

## Core Concepts

### `CliConfig`

Defines runtime configuration for the CLI.

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

// Default configuration
auto config = softadastra::cli::core::CliConfig::defaults();
```

### `CliOptions`

Defines how the CLI service starts.

```cpp
// Interactive mode
auto options = softadastra::cli::CliOptions::interactive_mode();

// Single command mode
auto options = softadastra::cli::CliOptions::single_command("help");

// Manual setup
softadastra::cli::CliOptions options;
options.args        = {"softadastra", "status"};
options.interactive = false;
options.command     = "status";
```

### `CliStatus`

```
Idle → Starting → Running → WaitingInput → ExecutingCommand → Stopping → Stopped → Failed
```

Helpers:

```cpp
softadastra::cli::types::to_string(status);
softadastra::cli::types::is_active(status);
softadastra::cli::types::is_terminal(status);
softadastra::cli::types::is_transitioning(status);
```

### `CliErrorCode`

- `None`, `UnknownError`, `InvalidState`, `NotInitialized`
- `ParseError`, `UnknownCommand`, `InvalidArguments`
- `MissingArgument`, `TooManyArguments`
- `CommandExecutionFailed`, `CommandNotFound`, `PermissionDenied`
- `InputError`, `OutputError`, `InternalError`, `NotImplemented`

Helpers:

```cpp
softadastra::cli::types::to_string(code);
softadastra::cli::types::is_success(code);
softadastra::cli::types::is_user_error(code);
softadastra::cli::types::is_system_error(code);
```

### `CliCommandType`

- `Unknown`, `Builtin`, `Custom`, `Info`, `System`, `Diagnostic`, `Admin`

Helpers:

```cpp
softadastra::cli::types::to_string(type);
softadastra::cli::types::is_known(type);
softadastra::cli::types::is_mutating(type);
```

## Parsing Flow

```
raw input
    ↓
Tokenizer
    ↓
CommandLine
    ↓
ArgParser
    ↓
ParsedCommand
```

Example:

```cpp
using namespace softadastra::cli;

const std::string input = R"(deploy app --host=localhost --port 8080 --verbose)";

const auto tokens = parser::Tokenizer::tokenize(input);
const parser::CommandLine line{tokens};
const auto parsed = parser::ArgParser::parse(line);
```

Result:

```
name:    deploy
args:    ["app"]
options:
  host    →  "localhost"
  port    →  8080
  verbose →  true
```

## `Tokenizer`

Splits raw input into tokens. Supports: whitespace separation, double/single quotes, escaped characters and spaces.

```cpp
// Quoted argument
const auto tokens = softadastra::cli::parser::Tokenizer::tokenize(
    R"(store-put name "Softadastra Runtime")");
// → ["store-put", "name", "Softadastra Runtime"]

// Escaped space
auto tokens = softadastra::cli::parser::Tokenizer::tokenize(
    R"(store-put name hello\ world)");
// → ["store-put", "name", "hello world"]
```

## `CommandLine`

Represents tokenized input.

```cpp
softadastra::cli::parser::CommandLine line{{"store-put", "name", "hello"}};

line.command();    // "store-put"
line.arguments();  // ["name", "hello"]
line.size();       // 3
line.empty();      // false
```

## `ArgParser`

Converts a `CommandLine` into a `ParsedCommand`. Supported option forms: `--flag`, `--key=value`, `--key value`, `-f`, `-k value`.

```cpp
softadastra::cli::parser::CommandLine line{
    {"deploy", "app", "--port", "8080", "--verbose"}};

auto parsed = softadastra::cli::parser::ArgParser::parse(line);

parsed.has_option("port");
parsed.option_enabled("verbose");
parsed.option_string_or("host", "localhost");
```

## `OptionValue`

Typed option value:

```cpp
using OptionValue = std::variant
    std::monostate,
    bool,
    std::int64_t,
    double,
    std::string>;
```

Helpers:

```cpp
softadastra::cli::types::is_empty(value);
softadastra::cli::types::is_bool(value);
softadastra::cli::types::is_integer(value);
softadastra::cli::types::is_double(value);
softadastra::cli::types::is_string(value);
softadastra::cli::types::option_value_type(value);
```

---

## Command Model

### `CliOption`

```cpp
softadastra::cli::command::CliOption option{
    "port", "p", "Port to bind", "PORT", true, false};

option.valid();
option.has_short_name();
option.has_description();
option.has_value_name();
```

### `CliCommand`

```cpp
softadastra::cli::command::CliCommand command{
    "status",
    "Show Softadastra status",
    "status",
    softadastra::cli::types::CliCommandType::Info,
    {"st"},
    {}};

command.valid();
command.matches("status");
command.matches("st");
command.has_aliases();
command.has_options();
command.find_option("port");
```

### Command Handlers

```cpp
class StatusHandler final
    : public softadastra::cli::command::ICommandHandler
{
public:
    [[nodiscard]] softadastra::cli::types::CliErrorCode handle(
        const softadastra::cli::parser::ParsedCommand &command) override
    {
        (void)command;
        std::cout << "Softadastra is running\n";
        return softadastra::cli::types::CliErrorCode::None;
    }
};
```

## `CommandRegistry`

Stores commands and handlers. Supports canonical command registration, alias registration, lookup by name or alias, and handler retrieval.

```cpp
softadastra::cli::command::CommandRegistry registry;

registry.register_command(command, std::make_shared<StatusHandler>());

registry.exists("status");
registry.exists("st");

auto found   = registry.find_command("st");
auto handler = registry.get_handler("status");
auto commands = registry.all_commands();
```

> Aliases are indexed, but `all_commands()` returns only canonical commands.

## Built-in Commands

| Command | Aliases | Description |
|---------|---------|-------------|
| `help` | `h` | Show help information |
| `version` | `v` | Show CLI version |
| `exit` | `quit`, `q` | Exit the CLI session |

```cpp
auto definitions = softadastra::cli::command::BuiltinCommand::definitions();
auto handlers    = softadastra::cli::command::BuiltinCommand::handlers(context);

for (std::size_t i = 0; i < definitions.size(); ++i)
{
    registry.register_command(definitions[i], handlers[i]);
}
```

## Runtime Context

### `CliSession`

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
```

### `CliContext`

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

### `CliApplication`

Executes parsed commands through the registry.

```cpp
softadastra::cli::core::CliApplication app{context};

if (!app.start())
{
    return 1;
}

auto result = app.execute(parsed);

app.stop();
```

Responsibilities: validate context, start/stop session, resolve handlers, dispatch commands, handle `--help` / `-h`, update session state.

### `CliEngine`

High-level parser and executor.

```cpp
softadastra::cli::engine::CliEngine engine{context};

engine.start();

auto parsed = engine.parse("status");

if (parsed.has_value())
{
    engine.execute(*parsed);
}

engine.execute("help");
engine.stop();
```

## `CliService`

The public high-level facade.

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

### Register custom command

```cpp
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

## I/O Helpers

### `Console`

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

### `InputReader`

```cpp
auto line = softadastra::cli::io::InputReader::read_line("> ");

if (!line.has_value())
{
    return 1;
}

// Test-friendly input
std::istringstream input{"status\n"};
auto line = softadastra::cli::io::InputReader::read_line(input);
```

### `OutputWriter`

```cpp
softadastra::cli::io::OutputWriter::writeln("hello");
softadastra::cli::io::OutputWriter::errorln("error");

std::ostringstream out;
softadastra::cli::io::OutputWriter::writeln(out, "test");
```

### `TerminalStyle`

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

## UI Utilities

### `Style.hpp`

```cpp
namespace style = softadastra::cli::utils::style;

std::cout << style::BOLD << style::CYAN
          << "Softadastra"
          << style::RESET << "\n";

std::cout << style::bold("strong") << "\n";
std::cout << style::dim("muted")   << "\n";
std::cout << style::link("https://github.com/softadastra/softadastra") << "\n";
```

### `Ui.hpp`

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

### `HelpFormatter`

```cpp
// Full help
auto help = softadastra::cli::utils::HelpFormatter::format(
    registry.all_commands(), "softadastra");

std::cout << help;

// Single command
auto text = softadastra::cli::utils::HelpFormatter::format_command(command);
```

### `TableFormatter`

```cpp
std::vector<std::string> headers{"Command", "Type", "Description"};

std::vector<std::vector<std::string>> rows{
    {"help",    "info",   "Show help information"},
    {"version", "info",   "Show CLI version"},
    {"exit",    "system", "Exit CLI session"},
};

std::cout << softadastra::cli::utils::TableFormatter::format(headers, rows);
```

### `StringUtils`

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

## Full Execution Flow

```
1.   User enters raw input
2.   CliEngine receives input
3.   Tokenizer splits input into tokens
4.   CommandLine stores tokens
5.   ArgParser creates ParsedCommand
6.   CliApplication validates session state
7.   CommandRegistry resolves command or alias
8.   ICommandHandler executes command logic
9.   CliSession records last command and count
10.  CliEngine returns a CliErrorCode
11.  CliService converts error code to process exit code when needed
```

## Examples

| Example | Description |
|---------|-------------|
| `cli_minimal.cpp` | Minimal CLI setup |
| `cli_commands_demo.cpp` | Command registration demo |
| `cli_tokenizer.cpp` | Tokenization example |
| `cli_arg_parser.cpp` | Argument parsing example |
| `cli_table_formatter.cpp` | Table formatting example |
| `cli_ui_style.cpp` | UI and style helpers |
| `cli_registry.cpp` | Command registry and alias lookup |
| `cli_custom_command.cpp` | Custom command with handler |
| `cli_service_single.cpp` | Single-command service execution |

```bash
vix build

# or with CMake
cmake -S . -B build -DSOFTADASTRA_CLI_BUILD_EXAMPLES=ON
cmake --build build
```

## Tests

The CLI module includes tests for: tokenizer, argument parser, command registry, CLI engine, console I/O, command metadata, session lifecycle, and output helpers.

```bash
vix build
ctest --test-dir build --output-on-failure
```

## Production Notes

Recommended production behavior:

- keep command handlers small
- return precise `CliErrorCode` values
- use `CliCommandType::Admin` for mutating admin commands
- use `CliCommandType::Diagnostic` for inspection commands
- avoid direct `std::cout` in complex commands when `Console` or `OutputWriter` is enough
- keep parsing separate from execution
- keep infrastructure logic outside the CLI module
- ensure every public command has a usage string
- provide aliases only when they are obvious
- use `TableFormatter` for structured lists
- use `HelpFormatter` for public help output
- preserve deterministic output for scripts and CI

## Design Rules

- CLI owns interaction
- Handlers own command meaning
- Parser must not execute commands
- Registry must not execute commands
- Engine must not own business logic
- Service owns runtime wiring
- Session is the single source of lifecycle truth
- Built-in commands must remain small
- Help output must be readable
- Error codes must be precise
- Output must be script-friendly when needed

## Dependencies

**Internal:** `softadastra/core` is not required by the CLI public API. The CLI module is intentionally lightweight and mostly standalone.

**External:**
- C++20 standard library
- ANSI-compatible terminal for styled output

## Roadmap

- [x] Public `cli.hpp` aggregator
- [x] Command registry
- [x] Built-in commands
- [x] Tokenizer and argument parser
- [x] Help formatter and table formatter
- [x] Console helpers and UI styling
- [x] Session tracking
- [x] Single command mode and interactive mode
- [ ] Completion support
- [ ] Command groups and nested subcommands
- [ ] Structured JSON output mode
- [ ] No-color mode enforcement
- [ ] Config file loading
- [ ] Shell completion generation
- [ ] Command middleware
- [ ] Permission policy hooks
- [ ] Audit logging hooks
- [ ] Metrics hooks
- [ ] Better diagnostics for malformed input
- [ ] Command documentation generation

## Summary

`softadastra/cli` provides:

- command parsing and metadata
- command registry and execution dispatch
- built-in commands
- CLI lifecycle management
- terminal I/O helpers and styled output
- help and table formatting
- high-level service entry point

> Its job is simple: provide a clean, reliable, production-ready command-line entry point for Softadastra infrastructure without owning infrastructure business logic.
