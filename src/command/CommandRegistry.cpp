/*
 * CommandRegistry.cpp
 */

#include <softadastra/cli/command/CommandRegistry.hpp>

namespace softadastra::cli::command
{
  void CommandRegistry::register_command(const CliCommand &command,
                                         std::shared_ptr<ICommandHandler> handler)
  {
    if (!command.valid() || handler == nullptr)
    {
      return;
    }

    Entry entry{command, std::move(handler)};

    // Register main command name
    commands_[command.name] = entry;

    // Register aliases
    for (const auto &alias : command.aliases)
    {
      if (!alias.empty())
      {
        commands_[alias] = entry;
      }
    }
  }

  bool CommandRegistry::exists(const std::string &name) const
  {
    return commands_.find(name) != commands_.end();
  }

  std::optional<CliCommand> CommandRegistry::find_command(const std::string &name) const
  {
    auto it = commands_.find(name);
    if (it == commands_.end())
    {
      return std::nullopt;
    }

    return it->second.command;
  }

  std::shared_ptr<ICommandHandler> CommandRegistry::get_handler(const std::string &name) const
  {
    auto it = commands_.find(name);
    if (it == commands_.end())
    {
      return nullptr;
    }

    return it->second.handler;
  }

  std::vector<CliCommand> CommandRegistry::all_commands() const
  {
    std::vector<CliCommand> result;
    result.reserve(commands_.size());

    for (const auto &[_, entry] : commands_)
    {
      result.push_back(entry.command);
    }

    return result;
  }

} // namespace softadastra::cli::command
