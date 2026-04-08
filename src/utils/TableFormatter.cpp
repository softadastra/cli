/*
 * TableFormatter.cpp
 */

#include <sstream>
#include <algorithm>

#include <softadastra/cli/utils/TableFormatter.hpp>

namespace softadastra::cli::utils
{
  std::string TableFormatter::format(const std::vector<std::string> &headers,
                                     const std::vector<std::vector<std::string>> &rows)
  {
    std::ostringstream out;

    const auto widths = compute_column_widths(headers, rows);

    // Header
    if (!headers.empty())
    {
      out << format_row(headers, widths) << "\n";

      // Separator
      for (std::size_t i = 0; i < widths.size(); ++i)
      {
        out << repeat('-', widths[i]);
        if (i + 1 < widths.size())
        {
          out << "  ";
        }
      }
      out << "\n";
    }

    // Rows
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

    // Headers
    for (std::size_t i = 0; i < headers.size(); ++i)
    {
      widths[i] = headers[i].size();
    }

    // Rows
    for (const auto &row : rows)
    {
      for (std::size_t i = 0; i < row.size(); ++i)
      {
        widths[i] = std::max(widths[i], row[i].size());
      }
    }

    return widths;
  }

  std::string TableFormatter::format_row(const std::vector<std::string> &row,
                                         const std::vector<std::size_t> &widths)
  {
    std::ostringstream out;

    for (std::size_t i = 0; i < widths.size(); ++i)
    {
      if (i < row.size())
      {
        out << row[i];
        out << repeat(' ', widths[i] - row[i].size());
      }
      else
      {
        out << repeat(' ', widths[i]);
      }

      if (i + 1 < widths.size())
      {
        out << "  ";
      }
    }

    return out.str();
  }

  std::string TableFormatter::repeat(char c, std::size_t count)
  {
    return std::string(count, c);
  }

} // namespace softadastra::cli::utils
