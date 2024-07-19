#ifndef SPECTRAC_LEXER_HPP
#define SPECTRAC_LEXER_HPP

#include "../pch.hpp"
#include "token.hpp"

namespace Spectra {

class Lexer {
public:
  Lexer(const std::string &source) : m_source(source) {}
  ~Lexer() = default;

  void LexTokens();
  void PrintTokens() const;
  void String();
  void Number();
  void Identifier();
  bool Match(char expected);
  bool MatchNext(char expected);
  bool IsAlpha(char c) const { return std::isalpha(c) || c == '_'; }
  bool IsDigit(char c) const { return std::isdigit(c); }
  bool IsAtEnd() const { return m_current >= m_source.size(); }
  char Advance() { return m_source[m_current++]; }
  char Peek() const { return m_source[m_current]; }
  char PeekNext() const { return m_source[m_current + 1]; }
  void AddToken(TokenType type) {
    m_tokens.emplace_back(type, m_source.substr(m_start, m_current - m_start),
                          m_line);
  }

  const std::vector<Token> &GetTokens() const { return m_tokens; }

private:
  i32 m_start = 0;
  i32 m_current = 0;
  i32 m_line = 1;
  std::string m_source;
  std::vector<Token> m_tokens;
};

} // namespace Spectra

#endif
