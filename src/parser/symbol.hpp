#ifndef SPECTRAC_SYMBOL_HPP
#define SPECTRAC_SYMBOL_HPP

#include "../pch.hpp"

namespace Spectra {

enum class SymbolType {
    TERMINAL,
    NON_TERMINAL,
    VARIABLE,
    FUNCTION,
    CLASS,
    INTERFACE,
    NAMESPACE,
    ENUM
};

enum class ValueType {
    STR,
    I8, I16, I32, I64,
    U8, U16, U32, U64,
    F32, F64,
    BOOL,
    VOID,
    CUSTOM,
    NONE
};

class Symbol {
public:
    Symbol(const std::string& name, SymbolType type)
        : m_name(name), m_type(type) {}

    const std::string& GetName() const { return m_name; }
    SymbolType GetType() const { return m_type; }
    
    void SetValueType(ValueType type) { m_value_type = type; }
    ValueType GetValueType() const { return m_value_type; }
    
    void SetReturnType(ValueType type) { m_return_type = type; }
    ValueType GetReturnType() const { return m_return_type; }
    
    void SetParams(const std::vector<ValueType>& params) { m_params = params; }
    const std::vector<ValueType>& GetParams() const { return m_params; }
    
    void SetIsConst(bool is_const) { m_is_const = is_const; }
    bool IsConst() const { return m_is_const; }
    
    void SetIsPublic(bool is_public) { m_is_public = is_public; }
    bool IsPublic() const { return m_is_public; }
    
    void SetCustomTypeName(const std::string& name) { m_custom_type_name = name; }
    const std::optional<std::string>& GetCustomTypeName() const { return m_custom_type_name; }

private:
    std::string m_name;
    SymbolType m_type;
    ValueType m_value_type = ValueType::NONE;
    ValueType m_return_type = ValueType::NONE;
    std::vector<ValueType> m_params;
    bool m_is_const = false;
    bool m_is_public = false;
    std::optional<std::string> m_custom_type_name;
};

class SymbolTable {
public:
    void AddSymbol(const Symbol& symbol) { 
        m_symbols[symbol.GetName()] = symbol; 
    }
    
    const Symbol& GetSymbol(const std::string& name) const {
        auto it = m_symbols.find(name);
        if (it == m_symbols.end()) {
            throw std::runtime_error("Symbol not found: " + name);
        }
        return it->second;
    }
    
    bool HasSymbol(const std::string& name) const {
        return m_symbols.find(name) != m_symbols.end();
    }
    
    void EnterScope() {
        m_scopes.push_back(std::unordered_map<std::string, Symbol>());
    }
    
    void ExitScope() {
        if (!m_scopes.empty()) {
            m_scopes.pop_back();
        }
    }
    
    void AddSymbolToCurrentScope(const Symbol& symbol) {
        if (m_scopes.empty()) {
            AddSymbol(symbol);
        } else {
            m_scopes.back()[symbol.GetName()] = symbol;
        }
    }
    
    const Symbol& LookupSymbol(const std::string& name) const {
        for (auto it = m_scopes.rbegin(); it != m_scopes.rend(); ++it) {
            auto symbol_it = it->find(name);
            if (symbol_it != it->end()) {
                return symbol_it->second;
            }
        }
        return GetSymbol(name);  // Look in the global scope
    }

private:
    std::unordered_map<std::string, Symbol> m_symbols;  // Global symbols
    std::vector<std::unordered_map<std::string, Symbol>> m_scopes;  // Local scopes
};

} // namespace Spectra

#endif // SPECTRAC_SYMBOL_HPP
