# softadastra/cli

> Command-line interface for Softadastra systems.

The `cli` module provides the **user-facing interface** to interact with Softadastra.

It allows users to:

> Start, control, and inspect the system through simple commands.

---

## Purpose

The goal of `softadastra/cli` is simple:

> Expose the system capabilities through a clean and minimal command-line interface.

---

## Core Principle

> Interface, not logic.

This module:

* Parses commands
* Triggers actions
* Displays results

It does **not implement core logic**.

---

## Responsibilities

The `cli` module provides:

* Command parsing
* Command execution
* User interaction (output, status)
* Entry points for application control

---

## What this module does NOT do

* No sync logic (sync module)
* No storage logic (store module)
* No network communication (transport module)
* No filesystem observation (fs module)

👉 It only connects the user to the system.

---

## Design Principles

### 1. Thin layer

The CLI must remain minimal and lightweight.

---

### 2. Delegation

All logic must be delegated to the `app` module.

---

### 3. Predictability

Commands must be:

* Simple
* Consistent
* Explicit

---

### 4. Scriptable

The CLI should be usable in:

* Shell scripts
* Automation
* Dev workflows

---

## Module Structure

```id="cli1x"
modules/cli/
├── include/softadastra/cli/
│   ├── Command.hpp
│   ├── RunCommand.hpp
│   ├── StatusCommand.hpp
│   ├── PairCommand.hpp
│   └── InitCommand.hpp
└── src/
```

---

## Core Components

### Command

Base abstraction for all CLI commands.

Defines:

* Interface for execution
* Common utilities

---

### RunCommand

Starts the system.

Example:

```bash id="cmd1"
drive run
```

---

### StatusCommand

Displays current state.

Example:

```bash id="cmd2"
drive status
```

---

### PairCommand

Connects to another peer.

Example:

```bash id="cmd3"
drive pair 192.168.1.10:9000
```

---

### InitCommand

Initializes a workspace.

Example:

```bash id="cmd4"
drive init
```

---

## Example Usage

```bash id="cmd5"
drive init
drive run --folder ~/SoftadastraDrive
drive status
```

---

## Integration

The CLI interacts only with:

* `softadastra/app`

It does not directly call:

* sync
* transport
* wal
* fs

---

## Execution Flow

1. User runs command
2. CLI parses input
3. CLI calls app layer
4. App orchestrates modules
5. CLI displays result

---

## Output Model

The CLI should support:

* Human-readable output
* Structured output (future: JSON)

---

## Dependencies

### Internal

* softadastra/app
* softadastra/core

### External

* Standard C++ libraries

---

## MVP Scope

* Basic commands:

  * init
  * run
  * status
  * pair
* Simple argument parsing
* Minimal output

---

## Roadmap

* JSON output mode
* Interactive CLI mode
* Command autocompletion
* Advanced diagnostics
* Remote control commands

---

## Rules

* Never contain business logic
* Never bypass app layer
* Always keep commands simple
* Always fail with clear messages

---

## Philosophy

The CLI is the **interface, not the system**.

> It should make the system usable, not define how it works.

---

## Summary

* Exposes commands
* Delegates to app
* Displays results
* Remains lightweight

---

## License

See root LICENSE file.
