/*
 * HelpFormatter.cpp
 */

#include <sstream>

#include <softadastra/cli/utils/HelpFormatter.hpp>

namespace softadastra::cli::utils
{
  namespace
  {
    std::string format_option_line(const command::CliOption &option)
    {
      std::ostringstream out;

      out << "  ";

      if (!option.short_name.empty())
      {
        out << "-" << option.short_name << ", ";
      }
      else
      {
        out << "    ";
      }

      out << "--" << option.name;

      if (option.takes_value && !option.value_name.empty())
      {
        out << " <" << option.value_name << ">";
      }

      if (!option.description.empty())
      {
        out << "\n      " << option.description;
      }

      return out.str();
    }
  }

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

    out << "\nUse '" << app_name << " help <command>' for more information.\n";

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

    if (!command.options.empty())
    {
      out << "\nOptions:\n";
      for (const auto &option : command.options)
      {
        out << format_option_line(option) << "\n";
      }
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
