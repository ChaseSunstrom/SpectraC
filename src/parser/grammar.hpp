#ifndef SPECTRAC_GRAMMAR_HPP
#define SPECTRAC_GRAMMAR_HPP

#include "../lexer/token.hpp"
#include "ast.hpp"

namespace Spectra {

class GrammarRule;

class NonTerminal {
public:
  explicit NonTerminal(const std::string &name) : m_name(name) {}
  const std::string &GetName() const { return m_name; }

private:
  std::string m_name;
};

using GrammarSymbol = std::variant<TokenType, NonTerminal>;

struct Optional {
  std::unique_ptr<GrammarRule> rule;
};

struct ZeroOrMore {
  std::unique_ptr<GrammarRule> rule;
};

struct OneOrMore {
  std::unique_ptr<GrammarRule> rule;
};

struct OrRule {
  std::vector<std::unique_ptr<GrammarRule>> rules;
};

struct AndRule {
  std::vector<std::unique_ptr<GrammarRule>> rules;
};

using RuleComponent = std::variant<GrammarSymbol, Optional, ZeroOrMore,
                                   OneOrMore, OrRule, AndRule>;

class GrammarRule {
public:
  GrammarRule() = default;
  ~GrammarRule() = default;

  GrammarRule &Token(TokenType type);
  GrammarRule &NonTerminal(const std::string &name);
  GrammarRule &Optional();
  GrammarRule &ZeroOrMore();
  GrammarRule &OneOrMore();
  GrammarRule &
  Action(std::function<AstNodePtr(const std::vector<AstNodePtr> &)> action);
  GrammarRule &Or();
  GrammarRule &And();
  GrammarRule &End();

  const std::vector<RuleComponent> &GetComponents() const {
    return m_components;
  }

  const std::function<AstNodePtr(const std::vector<AstNodePtr> &)> &
  GetAction() const {
    return m_action;
  }

private:
  std::vector<RuleComponent> m_components;
  std::function<AstNodePtr(const std::vector<AstNodePtr> &)> m_action;
};

class Grammar {
public:
  Grammar() = default;
  ~Grammar() = default;

  void AddRule(const std::string &name, const GrammarRule &rule);
  const std::unordered_map<std::string, GrammarRule> &GetRules() const {
    return m_rules;
  }
  const GrammarRule &GetRule(const std::string &name) const;
  const std::string &GetStartSymbol() const { return m_start_symbol; }
  void SetStartSymbol(const std::string &start_symbol) {
    m_start_symbol = start_symbol;
  }

private:
  std::unordered_map<std::string, GrammarRule> m_rules;
  std::string m_start_symbol;
};

} // namespace Spectra

#endif // SPECTRAC_GRAMMAR_HPP
