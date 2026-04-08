/*
 * HelpFormatter.cpp
 */

#include <sstream>

#include <softadastra/cli/utils/HelpFormatter.hpp>

namespace softadastra::cli::utils
{
  std::string HelpFormatter::format(const std::vector<command::CliCommand> &commands,
                                    const std::string &app_name)
  {
    std::ostringstream out;

    out << app_name << " - available commands\n\n";

    for (const auto &cmd : commands)
    {
      out << "  " << cmd.name;

      if (!cmd.aliases.empty())
      {
        out << " (";
        for (std::size_t i = 0; i < cmd.aliases.size(); ++i)
        {
          out << cmd.aliases[i];
          if (i + 1 < cmd.aliases.size())
          {
            out << ", ";
          }
        }
        out << ")";
      }

      out << "\n    " << cmd.description << "\n";
    }

    out << "\nUse '" << app_name << " <command> --help' for more information.\n";

    return out.str();
  }

  std::string HelpFormatter::format_command(const command::CliCommand &command)
  {
    std::ostringstream out;

    out << "Command: " << command.name << "\n\n";

    if (!command.description.empty())
    {
      out << command.description << "\n\n";
    }

    out << "Usage:\n";
    out << "  " << format_command_line(command) << "\n";

    if (!command.aliases.empty())
    {
      out << "\nAliases:\n  ";
      for (std::size_t i = 0; i < command.aliases.size(); ++i)
      {
        out << command.aliases[i];
        if (i + 1 < command.aliases.size())
        {
          out << ", ";
        }
      }
      out << "\n";
    }

    return out.str();
  }

  std::string HelpFormatter::format_command_line(const command::CliCommand &command)
  {
    if (!command.usage.empty())
    {
      return command.usage;
    }

    return command.name;
  }

} // namespace softadastra::cli::utils
