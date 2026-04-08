/*
 * TableFormatter.hpp
 */

#ifndef SOFTADASTRA_CLI_TABLE_FORMATTER_HPP
#define SOFTADASTRA_CLI_TABLE_FORMATTER_HPP

#include <string>
#include <vector>

namespace softadastra::cli::utils
{
  /**
   * @brief Formats tabular CLI output
   *
   * Used for:
   * - command lists
   * - aligned output
   * - simple CLI tables
   */
  class TableFormatter
  {
  public:
    /**
     * @brief Format a table with headers and rows
     */
    static std::string format(const std::vector<std::string> &headers,
                              const std::vector<std::vector<std::string>> &rows);

  private:
    static std::vector<std::size_t> compute_column_widths(
        const std::vector<std::string> &headers,
        const std::vector<std::vector<std::string>> &rows);

    static std::string format_row(const std::vector<std::string> &row,
                                  const std::vector<std::size_t> &widths);

    static std::string repeat(char c, std::size_t count);
  };

} // namespace softadastra::cli::utils

#endif
