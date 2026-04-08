# Softadastra CLI

> **A modular and extensible command-line interface engine for real-world systems.**

Softadastra CLI provides a clean and structured way to build command-line tools with:

- robust parsing
- command registry and handlers
- interactive REPL support
- extensible architecture

Designed to integrate seamlessly with the Softadastra ecosystem.

---

## ✨ Features

- 🧠 Structured command parsing (`--flag`, `--key=value`, positional args)
- ⚙️ Command registry with handlers
- 🔁 Interactive mode (REPL)
- 🧩 Modular architecture (parser, engine, command, io)
- ⚡ Lightweight and fast
- 🌍 Built for real-world environments

---

## 📦 Module Structure

```text
cli/
├── parser/     # tokenization + parsing
├── command/    # command definitions + handlers
├── engine/     # orchestration
├── core/       # config + context + session
├── io/         # input/output abstraction
└── utils/      # formatting helpers
```

---

## 🚀 Quick Start

### Minimal CLI

```cpp
#include <softadastra/cli/cli.hpp>

int main()
{
    softadastra::cli::core::CliConfig config;
    config.app_name = "my-cli";

    softadastra::cli::CliService cli(config);

    softadastra::cli::CliOptions options;
    options.interactive = true;

    return cli.run(options);
}
```

---

## 🧪 Example Commands

Built-in commands:

| Command | Description |
|---------|-------------|
| `help`  | Show available commands |
| `version` | Display current version |
| `exit`  | Quit the CLI |

Custom commands can be registered using:

```cpp
registry.register_command(
    CliCommand{ ... },
    std::make_shared<MyHandler>()
);
```

---

## 🧠 Architecture

The CLI is built around a simple pipeline:

```
input string
      ↓
  Tokenizer
      ↓
  CommandLine
      ↓
  ArgParser
      ↓
  ParsedCommand
      ↓
  CliEngine
      ↓
  CommandRegistry
      ↓
  ICommandHandler
```

---

## 🔧 Usage Modes

### Interactive (REPL)

```
> help
> run file.cpp
> exit
```

### Single command

```cpp
options.command = "run file.cpp";
```

---

## 📌 Design Principles

- **Separation of concerns** — each module has a single responsibility
- **Minimal dependencies** — no bloat, no unnecessary coupling
- **Type-safe parsing** — powered by `std::variant`
- **Explicit error handling** — no silent failures
- **Extensible command system** — plug in new commands without touching core logic

---

## 🔗 Integration

Softadastra CLI is designed to work with the full Softadastra stack:

| Module | Role |
|--------|------|
| `core` | Config, context, session |
| `fs` | File system operations |
| `wal` | Write-ahead log |
| `store` | Local data store |
| `sync` | Synchronization layer |
| `transport` | Network transport |
| `metadata` | Metadata management |

Each module can expose its own commands via the CLI.

---

## 📄 License

MIT
