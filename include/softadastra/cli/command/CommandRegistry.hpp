/**
 *
 *  @file CommandRegistry.hpp
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

#ifndef SOFTADASTRA_CLI_COMMAND_REGISTRY_HPP
#define SOFTADASTRA_CLI_COMMAND_REGISTRY_HPP

#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

#include <softadastra/cli/command/CliCommand.hpp>
#include <softadastra/cli/command/ICommandHandler.hpp>

namespace softadastra::cli::command
{
  /**
   * @brief Registry of CLI command definitions and handlers.
   *
   * CommandRegistry owns the command metadata and handler mapping used by the
   * CLI engine.
   *
   * It supports:
   * - canonical command lookup
   * - alias lookup
   * - handler retrieval
   * - command listing for help output
   *
   * Commands are indexed by both their canonical name and aliases, while the
   * canonical command list is preserved separately for clean help rendering.
   */
  class CommandRegistry
  {
  public:
    /**
     * @brief Registers a command with its execution handler.
     *
     * Invalid commands or null handlers are ignored.
     *
     * @param command Command metadata.
     * @param handler Command handler.
     */
    void register_command(
        const CliCommand &command,
        std::shared_ptr<ICommandHandler> handler);

    /**
     * @brief Returns true if a command or alias exists.
     *
     * @param name Command name or alias.
     * @return true if the registry contains the command.
     */
    [[nodiscard]] bool exists(std::string_view name) const;

    /**
     * @brief Finds command metadata by command name or alias.
     *
     * @param name Command name or alias.
     * @return Command metadata if found.
     */
    [[nodiscard]] std::optional<CliCommand> find_command(
        std::string_view name) const;

    /**
     * @brief Returns the handler associated with a command name or alias.
     *
     * @param name Command name or alias.
     * @return Command handler or nullptr if not found.
     */
    [[nodiscard]] std::shared_ptr<ICommandHandler> get_handler(
        std::string_view name) const;

    /**
     * @brief Returns all canonical registered commands.
     *
     * Aliases are not duplicated in the returned list.
     *
     * @return Registered command metadata.
     */
    [[nodiscard]] std::vector<CliCommand> all_commands() const;

    /**
     * @brief Removes all registered commands and aliases.
     */
    void clear();

    /**
     * @brief Returns the number of canonical commands.
     *
     * @return Registered command count, excluding aliases.
     */
    [[nodiscard]] std::size_t size() const noexcept;

    /**
     * @brief Returns true when the registry has no commands.
     *
     * @return true if no canonical commands are registered.
     */
    [[nodiscard]] bool empty() const noexcept;

  private:
    struct Entry
    {
      CliCommand command{};
      std::shared_ptr<ICommandHandler> handler{};
      std::string canonical_name{};
    };

    [[nodiscard]] const Entry *find_entry(
        std::string_view name) const;

  private:
    std::unordered_map<std::string, Entry> entries_{};
    std::vector<std::string> canonical_order_{};
  };

} // namespace softadastra::cli::command

#endif // SOFTADASTRA_CLI_COMMAND_REGISTRY_HPP
