/*
 * CommandRegistry.cpp
 */

#include <softadastra/cli/command/CommandRegistry.hpp>

#include <utility>

namespace softadastra::cli::command
{
  void CommandRegistry::register_command(
      const CliCommand &command,
      std::shared_ptr<ICommandHandler> handler)
  {
    if (!command.valid() || handler == nullptr)
    {
      return;
    }

    const bool is_new_command =
        entries_.find(command.name) == entries_.end();

    Entry entry{
        command,
        std::move(handler),
        command.name,
    };

    entries_[command.name] = entry;

    if (is_new_command)
    {
      canonical_order_.push_back(command.name);
    }

    for (const auto &alias : command.aliases)
    {
      if (alias.empty())
      {
        continue;
      }

      entries_[alias] = entry;
    }
  }

  bool CommandRegistry::exists(
      std::string_view name) const
  {
    return find_entry(name) != nullptr;
  }

  std::optional<CliCommand> CommandRegistry::find_command(
      std::string_view name) const
  {
    const Entry *entry = find_entry(name);

    if (entry == nullptr)
    {
      return std::nullopt;
    }

    return entry->command;
  }

  std::shared_ptr<ICommandHandler> CommandRegistry::get_handler(
      std::string_view name) const
  {
    const Entry *entry = find_entry(name);

    if (entry == nullptr)
    {
      return nullptr;
    }

    return entry->handler;
  }

  std::vector<CliCommand> CommandRegistry::all_commands() const
  {
    std::vector<CliCommand> result;
    result.reserve(canonical_order_.size());

    for (const auto &name : canonical_order_)
    {
      const auto it = entries_.find(name);

      if (it == entries_.end())
      {
        continue;
      }

      result.push_back(it->second.command);
    }

    return result;
  }

  void CommandRegistry::clear()
  {
    entries_.clear();
    canonical_order_.clear();
  }

  std::size_t CommandRegistry::size() const noexcept
  {
    return canonical_order_.size();
  }

  bool CommandRegistry::empty() const noexcept
  {
    return canonical_order_.empty();
  }

  const CommandRegistry::Entry *CommandRegistry::find_entry(
      std::string_view name) const
  {
    const auto it = entries_.find(std::string{name});

    if (it == entries_.end())
    {
      return nullptr;
    }

    return &it->second;
  }

} // namespace softadastra::cli::command
