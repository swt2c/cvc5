/******************************************************************************
 * Top contributors (to current version):
 *   Andrew Reynolds, Andres Noetzli
 *
 * This file is part of the cvc5 project.
 *
 * Copyright (c) 2009-2022 by the authors listed in the file AUTHORS
 * in the top-level source directory and their institutional affiliations.
 * All rights reserved.  See the file COPYING in the top-level source
 * directory for licensing information.
 * ****************************************************************************
 *
 * The interface for parsing an input with a parser.
 */

#include "parser/input_parser.h"

#include "base/output.h"
#include "parser/api/cpp/command.h"
#include "parser/input.h"
#include "parser/parser_builder.h"
#include "theory/logic_info.h"

namespace cvc5 {
namespace parser {

InputParser::InputParser(Solver* solver, SymbolManager* sm, bool useOptions)
    : d_solver(solver), d_sm(sm), d_useOptions(useOptions)
{
  // Allocate an ANTLR parser
  ParserBuilder parserBuilder(solver, sm, useOptions);
  d_state = parserBuilder.build();
}

Command* InputParser::nextCommand()
{
  Trace("parser") << "nextCommand()" << std::endl;
  return d_state->nextCommand();
}

Term InputParser::nextExpression()
{
  Trace("parser") << "nextExpression()" << std::endl;
  return d_state->nextExpression();
}

void InputParser::setFileInput(const std::string& lang,
                               const std::string& filename)
{
  Trace("parser") << "setFileInput(" << lang << ", " << filename << ")"
                  << std::endl;
  d_state->setInput(Input::newFileInput(lang, filename));
}

void InputParser::setStreamInput(const std::string& lang,
                                 std::istream& input,
                                 const std::string& name)
{
  Trace("parser") << "setStreamInput(" << lang << ", ..., " << name << ")"
                  << std::endl;
  d_state->setInput(Input::newStreamInput(lang, input, name));
}

void InputParser::setIncrementalStringInput(const std::string& lang,
                                            const std::string& name)
{
  Trace("parser") << "setIncrementalStringInput(" << lang << ", ..., " << name
                  << ")" << std::endl;
  d_istringLang = lang;
  d_istringName = name;
  // if ANTLR, parser is already initialized
}
void InputParser::appendIncrementalStringInput(const std::string& input)
{
  Trace("parser") << "appendIncrementalStringInput(...)" << std::endl;
  d_state->setInput(Input::newStringInput(d_istringLang, input, d_istringName));
}

}  // namespace parser
}  // namespace cvc5
