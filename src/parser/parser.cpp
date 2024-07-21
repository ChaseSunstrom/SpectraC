#include "parser.hpp"
#include <algorithm>
#include <queue>

namespace Spectra {

ParsingTables LALRParserGenerator::Generate(const Grammar &grammar) {
  auto lr0_items = ComputeLR0Items(grammar);
  auto canonical_collection = GenerateCanonicalCollection(lr0_items, grammar);
  ComputeLALR1Lookaheads(canonical_collection, grammar);
  ParsingTables tables;
  ConstructParsingTables(canonical_collection, grammar, tables);
  return tables;
}

std::vector<LR0Item>
LALRParserGenerator::ComputeLR0Items(const Grammar &grammar) {
  std::vector<LR0Item> items;
  for (const auto &[non_terminal, rule] : grammar.GetRules()) {
    for (size_t i = 0; i <= rule.GetComponents().size(); ++i) {
      items.push_back({non_terminal, rule.GetComponents(), i});
    }
  }
  return items;
}

ItemSet LALRParserGenerator::Closure(const ItemSet &I, const Grammar &grammar) {
  ItemSet result = I;
  bool changed;
  do {
    changed = false;
    for (const auto &item : result) {
      if (item.dot_position < item.production.size()) {
        const auto &symbol = item.production[item.dot_position];
        if (std::holds_alternative<NonTerminal>(symbol)) {
          const auto &non_terminal = std::get<NonTerminal>(symbol);
          const auto &rule = grammar.GetRule(non_terminal.GetName());
          std::set<TokenType> lookahead = ComputeLookahead(item, grammar);
          for (const auto &component : rule.GetComponents()) {
            LR1Item new_item{{non_terminal.GetName(), {component}, 0},
                             lookahead};
            if (result.insert(new_item).second) {
              changed = true;
            }
          }
        }
      }
    }
  } while (changed);
  return result;
}

std::set<TokenType>
LALRParserGenerator::ComputeLookahead(const LR1Item &item,
                                      const Grammar &grammar) {
  std::set<TokenType> lookahead;
  if (item.dot_position + 1 < item.production.size()) {
    auto first = ComputeFirst(item.production[item.dot_position + 1], grammar);
    lookahead.insert(first.begin(), first.end());
  } else {
    lookahead.insert(item.lookahead.begin(), item.lookahead.end());
  }
  return lookahead;
}

std::set<TokenType>
LALRParserGenerator::ComputeFirst(const GrammarSymbol &symbol,
                                  const Grammar &grammar) {
  std::set<TokenType> first;
  if (std::holds_alternative<TokenType>(symbol)) {
    first.insert(std::get<TokenType>(symbol));
  } else {
    const auto &non_terminal = std::get<NonTerminal>(symbol);
    const auto &rule = grammar.GetRule(non_terminal.GetName());
    for (const auto &component : rule.GetComponents()) {
      auto component_first = ComputeFirst(component, grammar);
      first.insert(component_first.begin(), component_first.end());
      if (component_first.find(TokenType::EPSILON) == component_first.end()) {
        break;
      }
    }
  }
  return first;
}

std::vector<ItemSet> LALRParserGenerator::GenerateCanonicalCollection(
    const std::vector<LR0Item> &lr0_items, const Grammar &grammar) {
  std::vector<ItemSet> C;
  ItemSet initial_set =
      Closure({{grammar.GetStartSymbol(), {}, 0, {TokenType::END}}}, grammar);
  C.push_back(initial_set);

  bool changed;
  do {
    changed = false;
    std::vector<ItemSet> new_sets;
    for (const auto &I : C) {
      for (const auto &item : I) {
        if (item.dot_position < item.production.size()) {
          const auto &symbol = item.production[item.dot_position];
          ItemSet J;
          for (const auto &item_j : I) {
            if (item_j.dot_position < item_j.production.size() &&
                item_j.production[item_j.dot_position] == symbol) {
              J.insert({item_j.non_terminal, item_j.production,
                        item_j.dot_position + 1, item_j.lookahead});
            }
          }
          J = Closure(J, grammar);
          if (std::find(C.begin(), C.end(), J) == C.end() &&
              std::find(new_sets.begin(), new_sets.end(), J) == new_sets.end()) {
            new_sets.push_back(J);
            changed = true;
          }
        }
      }
    }
    C.insert(C.end(), new_sets.begin(), new_sets.end());
  } while (changed);

  return C;
}

void LALRParserGenerator::ComputeLALR1Lookaheads(
    std::vector<ItemSet> &canonical_collection, const Grammar &grammar) {
  std::map<std::pair<i32, i32>, std::set<TokenType>> propagation_graph;
  std::queue<std::pair<i32, i32>> work_list;

  // Initialize propagation graph and work list
  for (size_t i = 0; i < canonical_collection.size(); ++i) {
    for (const auto &item : canonical_collection[i]) {
      if (item.dot_position < item.production.size()) {
        const auto &symbol = item.production[item.dot_position];
        if (std::holds_alternative<NonTerminal>(symbol)) {
          size_t j = GetGotoState(canonical_collection, canonical_collection[i],
                                  symbol);
          propagation_graph[{i, j}].insert(item.lookahead.begin(),
                                           item.lookahead.end());
          work_list.push({i, j});
        }
      }
    }
  }

  // Propagate lookaheads
  while (!work_list.empty()) {
    auto [from_state, to_state] = work_list.front();
    work_list.pop();

    for (const auto &item : canonical_collection[to_state]) {
      if (item.dot_position == item.production.size()) {
        std::set<TokenType> new_lookahead =
            propagation_graph[{from_state, to_state}];
        if (!std::includes(item.lookahead.begin(), item.lookahead.end(),
                           new_lookahead.begin(), new_lookahead.end())) {
          item.lookahead.insert(new_lookahead.begin(), new_lookahead.end());
          for (size_t i = 0; i < canonical_collection.size(); ++i) {
            if (propagation_graph.find({to_state, i}) !=
                propagation_graph.end()) {
              work_list.push({to_state, i});
            }
          }
        }
      }
    }
  }
}

void LALRParserGenerator::ConstructParsingTables(
    const std::vector<ItemSet> &canonical_collection, const Grammar &grammar,
    ParsingTables &tables) {
  for (size_t i = 0; i < canonical_collection.size(); ++i) {
    const auto &item_set = canonical_collection[i];
    for (const auto &item : item_set) {
      if (item.dot_position < item.production.size()) {
        const auto &symbol = item.production[item.dot_position];
        if (std::holds_alternative<TokenType>(symbol)) {
          auto token_type = std::get<TokenType>(symbol);
          size_t j = GetGotoState(canonical_collection, item_set, symbol);
          tables.AddAction(i, token_type, ParsingAction::Shift(j));
        } else {
          const auto &non_terminal = std::get<NonTerminal>(symbol);
          size_t j = GetGotoState(canonical_collection, item_set, symbol);
          tables.AddGoto(i, non_terminal.GetName(), j);
        }
      } else {
        for (const auto &lookahead : item.lookahead) {
          if (item.non_terminal == grammar.GetStartSymbol() &&
              lookahead == TokenType::END) {
            tables.AddAction(i, lookahead, ParsingAction::Accept());
          } else {
            size_t rule_index = GetRuleIndex(grammar, item);
            tables.AddAction(i, lookahead, ParsingAction::Reduce(rule_index));
          }
        }
      }
    }
  }
}

size_t LALRParserGenerator::GetGotoState(
    const std::vector<ItemSet> &canonical_collection, const ItemSet &item_set,
    const GrammarSymbol &symbol) {
  ItemSet goto_set;
  for (const auto &item : item_set) {
    if (item.dot_position < item.production.size() &&
        item.production[item.dot_position] == symbol) {
      goto_set.insert({item.non_terminal, item.production,
                       item.dot_position + 1, item.lookahead});
    }
  }
  auto it = std::find(canonical_collection.begin(), canonical_collection.end(),
                      goto_set);
  return std::distance(canonical_collection.begin(), it);
}

size_t LALRParserGenerator::GetRuleIndex(const Grammar &grammar,
                                         const LR1Item &item) {
  const auto &rules = grammar.GetRules();
  auto it = std::find_if(rules.begin(), rules.end(), [&item](const auto &pair) {
    return pair.first == item.non_terminal &&
           pair.second.GetComponents() == item.production;
  });
  return std::distance(rules.begin(), it);
}

AstNodePtr Parser::Parse(const std::vector<Token> &tokens) {
  std::stack<i32> state_stack;
  std::stack<AstNodePtr> node_stack;
  state_stack.push(0);

  size_t index = 0;
  while (true) {
    i32 state = state_stack.top();
    TokenType lookahead =
        (index < tokens.size()) ? tokens[index].GetType() : TokenType::END;

    const ParsingAction &action = m_tables.GetAction(state, lookahead);
    switch (action.GetType()) {
    case ActionType::SHIFT: {
      state_stack.push(action.GetValue());
      node_stack.push(std::make_shared<TokenNode>(tokens[index]));
      index++;
      break;
    }
    case ActionType::REDUCE: {
      const auto &rule = m_grammar.GetRule(action.GetValue());
      std::vector<AstNodePtr> children(rule.GetComponents().size());
      for (i32 i = rule.GetComponents().size() - 1; i >= 0; i--) {
        state_stack.pop();
        children[i] = node_stack.top();
        node_stack.pop();
      }
      AstNodePtr new_node = rule.GetAction()(children);
      node_stack.push(new_node);
      i32 next_state = m_tables.GetGoto(state_stack.top(), rule.GetComponents()[0].GetName());
      state_stack.push(next_state);
      break;
    }
    case ActionType::ACCEPT:
      return node_stack.top();
    case ActionType::ERROR:
      throw std::runtime_error("Parsing error at token: " +
                               tokens[index].GetLexeme());
    }
  }
}

} // namespace Spectra
