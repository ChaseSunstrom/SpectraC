#ifndef SPECTRAC_SYMBOL_HPP
#define SPECTRAC_SYMBOL_HPP

#include "../pch.hpp"

namespace Spectra {

enum class SymbolType {
  TERMINAL,
  NON_TERMINAL,
};

enum class ValueType {
  STR,
  I8,
  I16,
  I32,
  I64,
  U8,
  U16,
  U32,
  U64,
  F32,
  F64,
  BOOL,
  VOID,
  CUSTOM,
  NONE
};

class Symbol {
public:
  Symbol(const std::string &name, SymbolType type)
      : m_name(name), m_type(type) {}
  ~Symbol() = default;

  const std::string &GetName() const { return m_name; }
  SymbolType GetType() const { return m_type; }

private:
  std::string m_name;
  SymbolType m_type;
  ValueType m_value_type;
  // Return type for functions
  ValueType m_return_type;
};

class SymbolTable {
public:
  SymbolTable() = default;
  ~SymbolTable() = default;

  void AddSymbol(const Symbol &symbol) { m_symbols[symbol.GetName()] = symbol; }
  const Symbol &GetSymbol(const std::string &name) const {
    return m_symbols.at(name);
  }

  bool HasSymbol(const std::string &name) const {
    return m_symbols.find(name) != m_symbols.end();
  }

private:
  std::unordered_map<std::string, Symbol> m_symbols;
};

} // namespace Spectra

#endif // SPECTRAC_SYMBOL_HPP
