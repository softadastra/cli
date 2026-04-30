/**
 *
 *  @file TableFormatter.hpp
 *  @author Gaspard Kirira
 *
 *  Copyright 2026, Softadastra.
 *  All rights reserved.
 *  https://github.com/softadastra/softadastra
 *
 *  Licensed under the Apache License, Version 2.0.
 *
 *  Softadastra CLI
 *
 */

#ifndef SOFTADASTRA_CLI_TABLE_FORMATTER_HPP
#define SOFTADASTRA_CLI_TABLE_FORMATTER_HPP

#include <cstddef>
#include <string>
#include <vector>

namespace softadastra::cli::utils
{
  /**
   * @brief Formats aligned table output for terminal display.
   *
   * TableFormatter provides a small deterministic formatter for simple CLI
   * tables such as command lists, peer lists, status output, diagnostics, and
   * structured summaries.
   *
   * The formatter is stateless and does not write directly to stdout.
   */
  class TableFormatter
  {
  public:
    /**
     * @brief Formats a table using headers and rows.
     *
     * @param headers Table column headers.
     * @param rows Table rows. Missing cells are rendered as empty values.
     * @return Formatted table text.
     */
    [[nodiscard]] static std::string format(
        const std::vector<std::string> &headers,
        const std::vector<std::vector<std::string>> &rows);

  private:
    /**
     * @brief Computes the display width of each column.
     *
     * @param headers Table headers.
     * @param rows Table rows.
     * @return Column widths.
     */
    [[nodiscard]] static std::vector<std::size_t> compute_column_widths(
        const std::vector<std::string> &headers,
        const std::vector<std::vector<std::string>> &rows);

    /**
     * @brief Formats one table row using computed column widths.
     *
     * @param row Row cells.
     * @param widths Column widths.
     * @return Formatted row.
     */
    [[nodiscard]] static std::string format_row(
        const std::vector<std::string> &row,
        const std::vector<std::size_t> &widths);

    /**
     * @brief Repeats a character.
     *
     * @param c Character to repeat.
     * @param count Number of repetitions.
     * @return Repeated string.
     */
    [[nodiscard]] static std::string repeat(
        char c,
        std::size_t count);
  };

} // namespace softadastra::cli::utils

#endif // SOFTADASTRA_CLI_TABLE_FORMATTER_HPP
