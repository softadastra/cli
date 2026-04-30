/*
 * TableFormatter.cpp
 */

#include <algorithm>
#include <sstream>

#include <softadastra/cli/utils/Style.hpp>
#include <softadastra/cli/utils/TableFormatter.hpp>

namespace softadastra::cli::utils
{
  namespace
  {
    namespace style = softadastra::cli::utils::style;

    constexpr const char *COLUMN_SEPARATOR = "  ";
  }

  std::string TableFormatter::format(
      const std::vector<std::string> &headers,
      const std::vector<std::vector<std::string>> &rows)
  {
    std::ostringstream out;

    const auto widths = compute_column_widths(headers, rows);

    if (widths.empty())
    {
      return {};
    }

    if (!headers.empty())
    {
      out << style::BOLD
          << format_row(headers, widths)
          << style::RESET
          << "\n";

      out << style::GRAY;

      for (std::size_t i = 0; i < widths.size(); ++i)
      {
        out << repeat('-', widths[i]);

        if (i + 1 < widths.size())
        {
          out << COLUMN_SEPARATOR;
        }
      }

      out << style::RESET << "\n";
    }

    for (const auto &row : rows)
    {
      out << format_row(row, widths) << "\n";
    }

    return out.str();
  }

  std::vector<std::size_t> TableFormatter::compute_column_widths(
      const std::vector<std::string> &headers,
      const std::vector<std::vector<std::string>> &rows)
  {
    std::size_t column_count = headers.size();

    for (const auto &row : rows)
    {
      column_count = std::max(column_count, row.size());
    }

    std::vector<std::size_t> widths(column_count, 0);

    for (std::size_t i = 0; i < headers.size(); ++i)
    {
      widths[i] = headers[i].size();
    }

    for (const auto &row : rows)
    {
      for (std::size_t i = 0; i < row.size(); ++i)
      {
        widths[i] = std::max(widths[i], row[i].size());
      }
    }

    return widths;
  }

  std::string TableFormatter::format_row(
      const std::vector<std::string> &row,
      const std::vector<std::size_t> &widths)
  {
    std::ostringstream out;

    for (std::size_t i = 0; i < widths.size(); ++i)
    {
      const std::string cell =
          i < row.size()
              ? row[i]
              : std::string{};

      out << cell;

      if (cell.size() < widths[i])
      {
        out << repeat(' ', widths[i] - cell.size());
      }

      if (i + 1 < widths.size())
      {
        out << COLUMN_SEPARATOR;
      }
    }

    return out.str();
  }

  std::string TableFormatter::repeat(
      char c,
      std::size_t count)
  {
    return std::string(count, c);
  }

} // namespace softadastra::cli::utils
