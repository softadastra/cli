/*
 * CommandLine.hpp
 */

#ifndef SOFTADASTRA_CLI_COMMAND_LINE_HPP
#define SOFTADASTRA_CLI_COMMAND_LINE_HPP

#include <cstddef>
#include <string>
#include <vector>

namespace softadastra::cli::parser
{
  /**
   * @brief Represents a tokenized command line
   *
   * This is an intermediate structure between raw input
   * and a fully parsed command.
   */
  class CommandLine
  {
  public:
    CommandLine() = default;
    explicit CommandLine(std::vector<std::string> tokens);

    /**
     * @brief Return all tokens
     */
    const std::vector<std::string> &tokens() const noexcept;

    /**
     * @brief Return true if empty
     */
    bool empty() const noexcept;

    /**
     * @brief Number of tokens
     */
    std::size_t size() const noexcept;

    /**
     * @brief Access token by index
     */
    const std::string &at(std::size_t index) const;

    /**
     * @brief Return command name (first token)
     */
    std::string command() const;

    /**
     * @brief Return arguments (tokens after command)
     */
    std::vector<std::string> arguments() const;

  private:
    std::vector<std::string> tokens_;
  };

} // namespace softadastra::cli::parser

#endif
