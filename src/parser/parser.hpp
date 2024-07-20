#ifndef SPECRTAC_PARSER_HPP
#define SPECRTAC_PARSER_HPP

#include "grammer.hpp"
#include "symbol.hpp"

namespace Spectra {

class ParsingTable {
public:
  ParsingTable() = default;
  ~ParsingTable() = default;

  void AddEntry(const Symbol &nonTerminal, const Symbol &terminal,
                const std::vector<GrammerRule> &rules) {
    m_table[nonTerminal.GetName()][terminal.GetName()] = rules;
  }

  const std::vector<GrammerRule> &GetRules(const Symbol &nonTerminal,
                                           const Symbol &terminal) const {
    return m_table.at(nonTerminal.GetName()).at(terminal.GetName());
  }

private:
  std::unordered_map<std::string,
                     std::unordered_map<std::string, std::vector<GrammerRule>>>
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

private:
  Tables m_tables;
};

class LALRParserGenerator {
public:
  LALRParserGenerator() = default;
  ~LALRParserGenerator() = default;

  ParsingTables Generate(const Grammer &grammer);
};

class Parser {
public:
};
} // namespace Spectra
#endif // SPECRTAC_PARSER_HPP
