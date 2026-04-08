/*
 * CommandRegistry.hpp
 */

#ifndef SOFTADASTRA_CLI_COMMAND_REGISTRY_HPP
#define SOFTADASTRA_CLI_COMMAND_REGISTRY_HPP

#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include <softadastra/cli/command/CliCommand.hpp>
#include <softadastra/cli/command/ICommandHandler.hpp>

namespace softadastra::cli::command
{
  /**
   * @brief Registry of CLI commands and their handlers
   */
  class CommandRegistry
  {
  public:
    /**
     * @brief Register a command with its handler
     */
    void register_command(const CliCommand &command,
                          std::shared_ptr<ICommandHandler> handler);

    /**
     * @brief Check if a command exists
     */
    bool exists(const std::string &name) const;

    /**
     * @brief Find a command definition
     */
    std::optional<CliCommand> find_command(const std::string &name) const;

    /**
     * @brief Get handler for a command
     */
    std::shared_ptr<ICommandHandler> get_handler(const std::string &name) const;

    /**
     * @brief Return all registered commands
     */
    std::vector<CliCommand> all_commands() const;

  private:
    struct Entry
    {
      CliCommand command;
      std::shared_ptr<ICommandHandler> handler;
    };

    std::unordered_map<std::string, Entry> commands_;
  };

} // namespace softadastra::cli::command

#endif
