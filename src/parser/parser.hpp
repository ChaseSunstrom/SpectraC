#ifndef SPECTRAC_PARSER_HPP
#define SPECTRAC_PARSER_HPP

#include "grammar.hpp"
#include "symbol.hpp"

namespace Spectra {

enum class ActionType { SHIFT, REDUCE, ACCEPT, ERROR };

class ParsingAction {
public:
  static ParsingAction Shift(i32 state) {
    return ParsingAction(ActionType::SHIFT, state);
  }

  static ParsingAction Reduce(i32 rule_index) {
    return ParsingAction(ActionType::REDUCE, rule_index);
  }

  static ParsingAction Accept() { return ParsingAction(ActionType::ACCEPT, 0); }

  static ParsingAction Error() { return ParsingAction(ActionType::ERROR, 0); }

  ActionType GetType() const { return m_type; }
  i32 GetValue() const { return m_value; }

private:
  ParsingAction(ActionType type, i32 value) : m_type(type), m_value(value) {}

  ActionType m_type;
  i32 m_value;
};
class ParsingTable {
public:
  ParsingTable() = default;
  ~ParsingTable() = default;

  void AddEntry(const Symbol &non_terminal, const Symbol &terminal,
                const std::vector<GrammarRule> &rules) {
    m_table[non_terminal.GetName()][terminal.GetName()] = rules;
  }

  const std::vector<GrammarRule> &GetRules(const Symbol &non_terminal,
                                           const Symbol &terminal) const {
    return m_table.at(non_terminal.GetName()).at(terminal.GetName());
  }

private:
  std::unordered_map<std::string,
                     std::unordered_map<std::string, std::vector<GrammarRule>>>
      m_table;
};

class ParsingTables {
public:
  using Tables = std::unordered_map<std::string, std::unique_ptr<ParsingTable>>;

  ParsingTables() = default;
  ~ParsingTables() = default;

  void AddTable(const std::string &name, std::unique_ptr<ParsingTable> table) {
    m_tables[name] = std::move(table);
  }

  const ParsingTable &GetTable(const std::string &name) const {
    return *m_tables.at(name);
  }

  void AddAction(i32 state, TokenType token, const ParsingAction &action) {
    m_action_table[state][token] = action;
  }

  void AddGoto(i32 state, const std::string &non_terminal, i32 next_state) {
    m_goto_table[state][non_terminal] = next_state;
  }

  const ParsingAction &GetAction(i32 state, TokenType token) const {
    return m_action_table.at(state).at(token);
  }

  i32 GetGoto(i32 state, const std::string &non_terminal) const {
    return m_goto_table.at(state).at(non_terminal);
  }

private:
  Tables m_tables;
  std::unordered_map<i32, std::unordered_map<TokenType, ParsingAction>>
      m_action_table;
  std::unordered_map<i32, std::unordered_map<std::string, i32>> m_goto_table;
};

struct LR0Item {
  std::string non_terminal;
  std::vector<GrammarSymbol> production;
  size_t dot_position;

  bool operator==(const LR0Item &other) const {
    return non_terminal == other.non_terminal &&
           production == other.production && dot_position == other.dot_position;
  }
};

struct LR1Item : LR0Item {
  std::set<TokenType> lookahead;

  bool operator==(const LR1Item &other) const {
    return LR0Item::operator==(other) && lookahead == other.lookahead;
  }
};

using ItemSet = std::set<LR1Item>;

class LALRParserGenerator {
public:
  ParsingTables Generate(const Grammar &grammar);

private:
  std::vector<LR0Item> ComputeLR0Items(const Grammar &grammar);
  ItemSet Closure(const ItemSet &I, const Grammar &grammar);
  std::set<TokenType> ComputeLookahead(const LR1Item &item,
                                       const Grammar &grammar);
  std::set<TokenType> ComputeFirst(const GrammarSymbol &symbol,
                                   const Grammar &grammar);
  std::vector<ItemSet>
  GenerateCanonicalCollection(const std::vector<LR0Item> &lr0_items,
                              const Grammar &grammar);
  void ComputeLALR1Lookaheads(std::vector<ItemSet> &canonical_collection,
                              const Grammar &grammar);
  void ConstructParsingTables(const std::vector<ItemSet> &canonical_collection,
                              const Grammar &grammar, ParsingTables &tables);
  size_t GetGotoState(const std::vector<ItemSet> &canonical_collection,
                      const ItemSet &item_set, const GrammarSymbol &symbol);
  size_t GetRuleIndex(const Grammar &grammar, const LR1Item &item);
};

class Parser {
public:
  Parser(const ParsingTables &tables, const Grammar &grammar)
      : m_tables(tables), m_grammar(grammar) {}

  AstNodePtr Parse(const std::vector<Token> &tokens);

private:
  const ParsingTables &m_tables;
  const Grammar &m_grammar;
};

} // namespace Spectra
#endif // SPECTRAC_PARSER_HPP
