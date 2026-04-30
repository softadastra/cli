/**
 *
 *  @file cli.hpp
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

#ifndef SOFTADASTRA_CLI_CLI_HPP
#define SOFTADASTRA_CLI_CLI_HPP

#include <softadastra/cli/CliOptions.hpp>
#include <softadastra/cli/CliService.hpp>

#include <softadastra/cli/command/BuiltinCommand.hpp>
#include <softadastra/cli/command/CliCommand.hpp>
#include <softadastra/cli/command/CliOption.hpp>
#include <softadastra/cli/command/CommandRegistry.hpp>
#include <softadastra/cli/command/ICommandHandler.hpp>

#include <softadastra/cli/core/CliApplication.hpp>
#include <softadastra/cli/core/CliConfig.hpp>
#include <softadastra/cli/core/CliContext.hpp>
#include <softadastra/cli/core/CliSession.hpp>

#include <softadastra/cli/engine/CliEngine.hpp>

#include <softadastra/cli/io/Console.hpp>
#include <softadastra/cli/io/InputReader.hpp>
#include <softadastra/cli/io/OutputWriter.hpp>
#include <softadastra/cli/io/TerminalStyle.hpp>

#include <softadastra/cli/parser/ArgParser.hpp>
#include <softadastra/cli/parser/CommandLine.hpp>
#include <softadastra/cli/parser/ParsedCommand.hpp>
#include <softadastra/cli/parser/Tokenizer.hpp>

#include <softadastra/cli/types/CliCommandType.hpp>
#include <softadastra/cli/types/CliErrorCode.hpp>
#include <softadastra/cli/types/CliStatus.hpp>
#include <softadastra/cli/types/OptionValue.hpp>

#include <softadastra/cli/utils/HelpFormatter.hpp>
#include <softadastra/cli/utils/StringUtils.hpp>
#include <softadastra/cli/utils/Style.hpp>
#include <softadastra/cli/utils/TableFormatter.hpp>
#include <softadastra/cli/utils/Ui.hpp>

#endif // SOFTADASTRA_CLI_CLI_HPP
