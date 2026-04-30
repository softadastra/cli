/**
 *
 *  @file CliCommand.hpp
 *  @author Gaspard Kirira
 *
 *  Copyright 2026, Softadastra.
 *  All rights reserved.
 *  https://github.com/softadastra/softadastra
 *
 *  Licensed under the Apache License, Version 2.0.
 *
 *  Softadastra CLI
 *
 */

#ifndef SOFTADASTRA_CLI_COMMAND_HPP
#define SOFTADASTRA_CLI_COMMAND_HPP

#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include <softadastra/cli/command/CliOption.hpp>
#include <softadastra/cli/types/CliCommandType.hpp>

namespace softadastra::cli::command
{
  namespace types = softadastra::cli::types;

  /**
   * @brief Declarative metadata for one CLI command.
   *
   * CliCommand describes a command exposed by the CLI module or by an
   * application embedding the CLI module.
   *
   * It is used by:
   * - CommandRegistry
   * - HelpFormatter
   * - ArgParser validation layers
   * - command dispatchers
   *
   * The command stores metadata only. It does not execute logic directly.
   */
  struct CliCommand
  {
    /**
     * @brief Command name used on the command line.
     *
     * Example: "help", "status", "store-put".
     */
    std::string name{};

    /**
     * @brief Short human-readable command description.
     */
    std::string description{};

    /**
     * @brief Usage string displayed in help output.
     *
     * Example: "store-put <key> <value>".
     */
    std::string usage{};

    /**
     * @brief Semantic command category.
     */
    types::CliCommandType type{types::CliCommandType::Unknown};

    /**
     * @brief Optional alternate command names.
     *
     * Example: "ls" as an alias for "list".
     */
    std::vector<std::string> aliases{};

    /**
     * @brief Supported options for this command.
     */
    std::vector<CliOption> options{};

    /**
     * @brief Creates an empty command declaration.
     */
    CliCommand() = default;

    /**
     * @brief Creates a CLI command declaration.
     *
     * @param command_name Command name.
     * @param command_description Short command description.
     * @param command_usage Usage text.
     * @param command_type Command category.
     * @param command_aliases Command aliases.
     * @param command_options Supported command options.
     */
    CliCommand(
        std::string command_name,
        std::string command_description,
        std::string command_usage,
        types::CliCommandType command_type,
        std::vector<std::string> command_aliases = {},
        std::vector<CliOption> command_options = {})
        : name(std::move(command_name)),
          description(std::move(command_description)),
          usage(std::move(command_usage)),
          type(command_type),
          aliases(std::move(command_aliases)),
          options(std::move(command_options))
    {
    }

    /**
     * @brief Returns true if this command declaration is usable.
     *
     * A valid command must have a name and a known command type.
     *
     * @return true when the command can be registered.
     */
    [[nodiscard]] bool valid() const noexcept
    {
      return !name.empty() &&
             types::is_known(type);
    }

    /**
     * @brief Returns true if the command has a description.
     *
     * @return true when description is not empty.
     */
    [[nodiscard]] bool has_description() const noexcept
    {
      return !description.empty();
    }

    /**
     * @brief Returns true if the command has custom usage text.
     *
     * @return true when usage is not empty.
     */
    [[nodiscard]] bool has_usage() const noexcept
    {
      return !usage.empty();
    }

    /**
     * @brief Returns true if the command has aliases.
     *
     * @return true when at least one alias exists.
     */
    [[nodiscard]] bool has_aliases() const noexcept
    {
      return !aliases.empty();
    }

    /**
     * @brief Returns true if the command has options.
     *
     * @return true when at least one option exists.
     */
    [[nodiscard]] bool has_options() const noexcept
    {
      return !options.empty();
    }

    /**
     * @brief Returns true if the given value matches this command.
     *
     * The comparison checks both the canonical command name and aliases.
     *
     * @param value Command name or alias.
     * @return true when value matches this command.
     */
    [[nodiscard]] bool matches(std::string_view value) const
    {
      if (name == value)
      {
        return true;
      }

      for (const auto &alias : aliases)
      {
        if (alias == value)
        {
          return true;
        }
      }

      return false;
    }

    /**
     * @brief Finds an option by its long or short name.
     *
     * @param value Option name without "-" or "--".
     * @return Pointer to option metadata, or nullptr when missing.
     */
    [[nodiscard]] const CliOption *find_option(
        std::string_view value) const noexcept
    {
      for (const auto &option : options)
      {
        if (option.name == value ||
            (!option.short_name.empty() && option.short_name == value))
        {
          return &option;
        }
      }

      return nullptr;
    }

    /**
     * @brief Returns true if an option exists.
     *
     * @param value Option name without "-" or "--".
     * @return true if the option is declared.
     */
    [[nodiscard]] bool has_option(std::string_view value) const noexcept
    {
      return find_option(value) != nullptr;
    }
  };

} // namespace softadastra::cli::command

#endif // SOFTADASTRA_CLI_COMMAND_HPP
