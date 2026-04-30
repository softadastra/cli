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

    constexpr std::size_t COMMAND_COLUMN_WIDTH = 28;
    constexpr std::size_t OPTION_COLUMN_WIDTH = 28;

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
          << style::CYAN << std::left
          << std::setw(OPTION_COLUMN_WIDTH)
          << opt.str()
          << style::RESET;

      if (!option.description.empty())
      {
        out << style::GRAY << option.description << style::RESET;
      }

      return out.str();
    }

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

    std::string format_command_name(const command::CliCommand &cmd)
    {
      std::ostringstream out;

      out << cmd.name;

      if (!cmd.aliases.empty())
      {
        out << " "
            << style::GRAY << "("
            << format_aliases(cmd.aliases)
            << ")" << style::RESET;
      }

      return out.str();
    }
  }

  std::string HelpFormatter::format(
      const std::vector<command::CliCommand> &commands,
      const std::string &app_name)
  {
    std::ostringstream out;

    out << style::BOLD << style::CYAN
        << app_name
        << style::RESET
        << "\n\n";

    ui::section(out, "Usage");
    out << "  " << app_name << " <command> [options]\n\n";

    ui::section(out, "Commands");

    for (const auto &cmd : commands)
    {
      out << "  "
          << style::BOLD << std::left
          << std::setw(COMMAND_COLUMN_WIDTH)
          << format_command_name(cmd)
          << style::RESET;

      if (!cmd.description.empty())
      {
        out << style::GRAY << cmd.description << style::RESET;
      }

      out << "\n";
    }

    out << "\n";
    out << style::GRAY
        << "Run '"
        << app_name
        << " help <command>' for details."
        << style::RESET
        << "\n";

    return out.str();
  }

  std::string HelpFormatter::format_command(
      const command::CliCommand &command)
  {
    std::ostringstream out;

    out << style::BOLD << style::CYAN
        << command.name
        << style::RESET
        << "\n";

    out << ui::faint_sep() << "\n\n";

    if (!command.description.empty())
    {
      out << style::GRAY
          << command.description
          << style::RESET
          << "\n\n";
    }

    ui::section(out, "Usage");
    out << "  " << format_command_line(command) << "\n";

    if (!command.aliases.empty())
    {
      out << "\n";
      ui::section(out, "Aliases");
      out << "  "
          << style::YELLOW
          << format_aliases(command.aliases)
          << style::RESET
          << "\n";
    }

    if (!command.options.empty())
    {
      out << "\n";
      ui::section(out, "Options");

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
