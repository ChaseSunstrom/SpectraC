#include "grammar.hpp"

namespace Spectra {

GrammarRule &GrammarRule::Token(TokenType type) {
  m_components.push_back(GrammarSymbol(type));
  return *this;
}

GrammarRule &GrammarRule::NonTerminal(const std::string &name) {
  m_components.push_back(GrammarSymbol(Spectra::NonTerminal(name)));
  return *this;
}

GrammarRule &GrammarRule::Optional() {
  if (m_components.empty()) {
    throw std::runtime_error("Cannot make an empty rule optional");
  }
  auto last_component = std::move(m_components.back());
  m_components.pop_back();
  auto optional_rule = std::make_unique<GrammarRule>();
  optional_rule->m_components.push_back(std::move(last_component));
  m_components.push_back(Spectra::Optional{std::move(optional_rule)});
  return *this;
}

GrammarRule &GrammarRule::ZeroOrMore() {
  if (m_components.empty()) {
    throw std::runtime_error("Cannot apply zero-or-more to an empty rule");
  }
  auto last_component = std::move(m_components.back());
  m_components.pop_back();
  auto zero_or_more_rule = std::make_unique<GrammarRule>();
  zero_or_more_rule->m_components.push_back(std::move(last_component));
  m_components.push_back(Spectra::ZeroOrMore{std::move(zero_or_more_rule)});
  return *this;
}

GrammarRule &GrammarRule::OneOrMore() {
  if (m_components.empty()) {
    throw std::runtime_error("Cannot apply one-or-more to an empty rule");
  }
  auto last_component = std::move(m_components.back());
  m_components.pop_back();
  auto one_or_more_rule = std::make_unique<GrammarRule>();
  one_or_more_rule->m_components.push_back(std::move(last_component));
  m_components.push_back(Spectra::OneOrMore{std::move(one_or_more_rule)});
  return *this;
}

GrammarRule &GrammarRule::Action(
    std::function<AstNodePtr(const std::vector<AstNodePtr> &)> action) {
  m_action = std::move(action);
  return *this;
}

GrammarRule &GrammarRule::Or() {
  if (m_components.empty()) {
    throw std::runtime_error("Cannot apply 'or' to an empty rule");
  }
  OrRule or_rule;
  or_rule.rules.push_back(std::make_unique<GrammarRule>());
  *(or_rule.rules.back()) = std::move(*this);
  *this = GrammarRule();
  m_components.push_back(std::move(or_rule));
  return *this;
}

GrammarRule &GrammarRule::And() {
  if (m_components.empty()) {
    throw std::runtime_error("Cannot apply 'and' to an empty rule");
  }
  AndRule and_rule;
  and_rule.rules.push_back(std::make_unique<GrammarRule>());
  *(and_rule.rules.back()) = std::move(*this);
  *this = GrammarRule();
  m_components.push_back(std::move(and_rule));
  return *this;
}

GrammarRule &GrammarRule::End() {
  m_components.push_back(GrammarSymbol(TokenType::END_OF_FILE));
  return *this;
}

void Grammar::AddRule(const std::string &name, const GrammarRule &rule) {
  m_rules[name] = rule;
}

const GrammarRule &Grammar::GetRule(const std::string &name) const {
  auto it = m_rules.find(name);
  if (it == m_rules.end()) {
    throw std::runtime_error("Grammar rule not found: " + name);
  }
  return it->second;
}

} // namespace Spectra
