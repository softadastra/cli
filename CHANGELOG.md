# Changelog - softadastra/cli

All notable changes to the **cli module** are documented in this file.

The `cli` module provides a **command-line interface** for interacting with Softadastra systems.
It acts as a thin layer between the user and the application runtime.

---

## [0.1.0] - Initial CLI Interface

### Added

* Base command abstraction (`Command`)
* Core commands:

  * `RunCommand` → start the system
  * `StatusCommand` → display current state
  * `PairCommand` → connect to a peer
  * `InitCommand` → initialize workspace
* Basic argument parsing
* Command execution pipeline
* Standard output for user feedback

### Design

* Thin interface layer
* Delegation to application layer (`softadastra/app`)
* No business logic inside CLI

---

## [0.1.1] - Stability Improvements

### Improved

* Safer argument parsing
* More consistent command execution flow
* Better handling of invalid input

### Fixed

* Edge cases with missing arguments
* Incorrect command dispatch in certain scenarios

---

## [0.2.0] - Usability Improvements

### Added

* Help command and usage output
* Improved command descriptions
* Basic validation for arguments

### Improved

* User experience for command execution
* Clarity of CLI output

---

## [0.3.0] - Output Improvements

### Added

* Structured output support (basic)
* Standardized formatting for command responses

### Improved

* Readability of CLI output
* Consistency across commands

---

## [0.4.0] - Command System Refinement

### Added

* Command registry system
* Dynamic command dispatch
* Extensible command structure

### Improved

* Maintainability of CLI commands
* Cleaner separation between commands

---

## [0.5.0] - Integration Enhancements

### Added

* Stronger integration with `softadastra/app`
* Clear command-to-action mapping

### Improved

* Reduced coupling with internal modules
* More predictable execution flow

---

## [0.6.0] - Error Handling & Feedback

### Added

* Improved error messages
* Exit codes for command outcomes
* Validation feedback for users

### Improved

* Debuggability of CLI interactions
* User guidance on failure

---

## [0.7.0] - Extraction Ready

### Added

* Namespace stabilization (`softadastra::cli`)
* Public API cleanup
* Documentation for command interfaces

### Improved

* Decoupling from application-specific assumptions
* Prepared for reuse in:

  * Softadastra CLI tools
  * SDK utilities
  * Dev tooling

---

## Roadmap

### Planned

* JSON output mode
* Interactive CLI (REPL)
* Command autocompletion
* Remote CLI control
* Advanced diagnostics and debugging commands

---

## Philosophy

The CLI is not the system.

> It is the gateway to the system.

---

## Rules

* Never contain business logic
* Always delegate to app
* Always provide clear output
* Always be predictable

---

## Summary

The `cli` module ensures:

* User interaction
* Command execution
* System control

It is the **interface layer of Softadastra**.
