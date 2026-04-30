/*
 * HelpFormatter.cpp
 */

#include <iomanip>
#include <sstream>

#include <softadastra/cli/utils/HelpFormatter.hpp>
#include <softadastra/cli/utils/Style.hpp>
#include <softadastra/cli/utils/Ui.hpp>

namespace softadastra::cli::utils
{
  namespace
  {
    namespace ui = softadastra::cli::utils::ui;
    namespace style = softadastra::cli::utils::style;

    constexpr std::size_t COMMAND_COLUMN_WIDTH = 24;
    constexpr std::size_t OPTION_COLUMN_WIDTH = 28;

    std::string format_aliases(const std::vector<std::string> &aliases)
    {
      std::ostringstream out;

      for (std::size_t i = 0; i < aliases.size(); ++i)
      {
        out << aliases[i];

        if (i + 1 < aliases.size())
        {
          out << ", ";
        }
      }

      return out.str();
    }

    std::string format_command_label(const command::CliCommand &cmd)
    {
      std::ostringstream out;

      out << cmd.name;

      if (!cmd.aliases.empty())
      {
        out << " (" << format_aliases(cmd.aliases) << ")";
      }

      return out.str();
    }

    std::string format_option_line(const command::CliOption &option)
    {
      std::ostringstream out;
      std::ostringstream opt;

      if (!option.short_name.empty())
      {
        opt << "-" << option.short_name << ", ";
      }
      else
      {
        opt << "    ";
      }

      opt << "--" << option.name;

      if (option.takes_value && !option.value_name.empty())
      {
        opt << " <" << option.value_name << ">";
      }

      out << "  "
          << style::CYAN
          << std::left
          << std::setw(OPTION_COLUMN_WIDTH)
          << opt.str()
          << style::RESET;

      if (!option.description.empty())
      {
        out << style::GRAY << option.description << style::RESET;
      }

      return out.str();
    }
  }

  std::string HelpFormatter::format(
      const std::vector<command::CliCommand> &commands,
      const std::string &app_name)
  {
    std::ostringstream out;

    out << style::BOLD << app_name << style::RESET << "\n\n";

    out << "Usage\n";
    out << "  " << app_name << " <command> [options]\n\n";

    out << "Commands\n";

    for (const auto &cmd : commands)
    {
      const std::string label = format_command_label(cmd);

      out << "  "
          << std::left
          << std::setw(COMMAND_COLUMN_WIDTH)
          << label;

      if (!cmd.description.empty())
      {
        out << cmd.description;
      }

      out << "\n";
    }

    out << "\n";
    out << "Run '"
        << app_name
        << " help <command>' for details.\n";

    return out.str();
  }

  std::string HelpFormatter::format_command(
      const command::CliCommand &command)
  {
    std::ostringstream out;

    out << style::BOLD << command.name << style::RESET << "\n\n";

    if (!command.description.empty())
    {
      out << command.description << "\n\n";
    }

    out << "Usage\n";
    out << "  " << format_command_line(command) << "\n";

    if (!command.aliases.empty())
    {
      out << "\n";
      out << "Aliases\n";
      out << "  " << format_aliases(command.aliases) << "\n";
    }

    if (!command.options.empty())
    {
      out << "\n";
      out << "Options\n";

      for (const auto &option : command.options)
      {
        out << format_option_line(option) << "\n";
      }
    }

    return out.str();
  }

  std::string HelpFormatter::format_command_line(
      const command::CliCommand &command)
  {
    if (!command.usage.empty())
    {
      return command.usage;
    }

    return command.name;
  }

} // namespace softadastra::cli::utils
