# softadastra/cli

> Command-line interface primitives for reliable Softadastra products.

`softadastra/cli` provides the CLI foundation layer of the Softadastra C++ stack.

Softadastra builds reliability-first products for local-first, offline-first, and distributed applications. This module provides the command-line infrastructure used to build operator tools, developer tools, diagnostics, and automation entry points.

## Purpose

`softadastra/cli` exists to provide a clean and reusable command-line foundation.

It is used by Softadastra root CLI tools, module-specific CLIs, local node control tools, diagnostics, and future automation layers.

The core rule is simple:

> CLI owns interaction. Application code owns meaning.

It is designed to be:

- Lightweight
- Script-friendly
- Human-friendly
- Handler-based
- Extensible
- Product-ready

## What it provides

This module provides CLI primitives such as:

- Command parsing
- Argument parsing
- Command registration
- Command aliases
- Command handlers
- CLI session lifecycle
- Built-in commands
- Terminal output helpers
- Help formatting
- Table formatting
- High-level CLI service

## What it does not do

`softadastra/cli` does not contain:

- Store logic
- WAL persistence
- Sync orchestration
- Peer discovery
- Transport delivery
- Metadata management
- Shell command execution
- Product-specific business logic

It parses input, dispatches commands, and formats output. Higher-level modules decide what each command means.

## Core model

```txt
Raw input
    |
Tokenizer
    |
Argument parser
    |
Command registry
    |
Command handler
    |
Output
```

The CLI module keeps interaction separate from infrastructure logic.

## Where it fits

```txt
Softadastra products
        |
CLI tools and automation
        |
softadastra/cli
        |
Softadastra modules and services
```

`softadastra/cli` provides the command-line entry point used to expose Softadastra systems to humans, scripts, operators, and automation.

## Installation

```bash
vix add @softadastra/cli
```

## Usage

```cpp
#include <softadastra/cli/cli.hpp>
```

## Example

```cpp
#include <softadastra/cli/cli.hpp>

#include <iostream>

int main()
{
    softadastra::cli::core::CliConfig config;
    config.app_name = "softadastra";
    config.version = "0.1.0";
    config.interactive = false;
    config.show_banner = false;

    softadastra::cli::CliService service{config};

    return service.run(
        softadastra::cli::CliOptions::single_command("help")
    );
}
```

## Requirements

- C++20
- Standard library
- ANSI-compatible terminal for styled output

## Documentation

For the full documentation, visit [docs.softadastra.com](https://docs.softadastra.com).

## License

Licensed under the Apache License, Version 2.0.
