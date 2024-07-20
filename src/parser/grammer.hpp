#ifndef SPECTRAC_GRAMMER_HPP
#define SPECTRAC_GRAMMER_HPP

#include "../lexer/token.hpp"
#include "../pch.hpp"
#include "ast.hpp"

namespace Spectra {

class GrammerRule {

public:
  GrammerRule() = default;
  ~GrammerRule() = default;

  GrammerRule &Token(TokenType type);
  GrammerRule &NonTerminal(const std::string &name);
  GrammerRule &Optional();
  GrammerRule &ZeroOrMore();
  GrammerRule &OneOrMore();
  GrammerRule &
  Action(std::function<AstNodePtr(const std::vector<AstNodePtr> &)> action);
  GrammerRule &Or();
  GrammerRule &And();
  GrammerRule &End();

private:
};

class Grammer {
public:
  Grammer() = default;
  ~Grammer() = default;

  void AddRule(const std::string &name, const GrammerRule &rule);

private:
  std::unordered_map<std::string, GrammerRule> m_rules;
};

} // namespace Spectra

#endif // SPECTRAC_GRAMMER_HPP
