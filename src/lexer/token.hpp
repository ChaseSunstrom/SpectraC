#ifndef SPECTRAC_TOKEN_HPP
#define SPECTRAC_TOKEN_HPP

#include "../pch.hpp"
#include "token_type.hpp"

namespace Spectra {

class Token {
public:
  Token(TokenType type, const std::string &literal, i32 line)
      : m_type(type), m_literal(literal), m_line(line) {}

  TokenType GetType() const { return m_type; }
  std::string GetLiteral() const { return m_literal; }

private:
  i32 m_line;
  TokenType m_type;
  std::string m_literal;
};

} // namespace Spectra

#endif // SPECTRAC_TOKEN_HPP
