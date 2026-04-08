# Changelog

All notable changes to this project will be documented in this file.

---

## [0.1.0]

### Added

- initial CLI module implementation
- modular architecture:
  - parser (Tokenizer, CommandLine, ArgParser, ParsedCommand)
  - command system (CliCommand, CommandRegistry, ICommandHandler, BuiltinCommand)
  - engine (CliEngine)
  - core (CliConfig, CliContext, CliApplication, CliSession)
  - io (Console, InputReader, OutputWriter, TerminalStyle)
  - utils (StringUtils, HelpFormatter, TableFormatter)

- structured command parsing:
  - positional arguments
  - flags (`--flag`)
  - key-value options (`--key=value`, `--key value`)
  - automatic type inference (bool, integer, double, string)

- command registry with:
  - handler binding
  - alias support
  - lookup and execution

- built-in commands:
  - help
  - version
  - exit

- CLI engine:
  - input parsing pipeline
  - command execution flow
  - lifecycle management (start/stop/status)

- CLI service:
  - interactive REPL mode
  - single command execution mode

- examples:
  - minimal CLI usage
  - custom command registration demo

- tests:
  - parser (Tokenizer, ArgParser)
  - command registry
  - engine execution
  - console output (manual verification)

- CMake:
  - registry-safe configuration
  - examples and tests disabled by default
  - canonical target: `softadastra::cli`

- Vix registry support:
  - `vix.json` metadata
  - compatibility with `vix install`, `vix build`, `vix run`

---

## Notes

- no external dependencies
- designed for composability and deterministic builds
- safe for integration in dependency graphs
