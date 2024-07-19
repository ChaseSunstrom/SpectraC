#include "lexer.hpp"
#include "keywords.hpp"

namespace Spectra {

void Lexer::LexTokens() {
  while (!IsAtEnd()) {
    m_start = m_current;
    char c = Advance();

    switch (c) {
    case ' ':
    case '\t':
    case '\r':
      break;
    case '\n':
      m_line++;
      break;
    case '(':
      AddToken(TokenType::LEFT_PAREN);
      break;
    case ')':
      AddToken(TokenType::RIGHT_PAREN);
      break;
    case '{':
      AddToken(TokenType::LEFT_BRACE);
      break;
    case '}':
      AddToken(TokenType::RIGHT_BRACE);
      break;
    case ',':
      AddToken(TokenType::COMMA);
      break;
    case '.':
      if (Match('.')) {
        Advance();
        AddToken(Match('=') ? TokenType::RANGE_INCLUSIVE : TokenType::RANGE);
      } else {
        AddToken(TokenType::DOT);
      }
      break;
    case '-':
      AddToken(Match('=')   ? TokenType::MINUS_ASSIGN
               : Match('>') ? TokenType::ARROW
               : Match('-') ? TokenType::DECREMENT
                            : TokenType::MINUS);
      break;
    case '+':
      AddToken(Match('=')   ? TokenType::PLUS_ASSIGN
               : Match('+') ? TokenType::INCREMENT
                            : TokenType::PLUS);
      break;
    case ';':
      AddToken(TokenType::SEMICOLON);
      break;
    case '?':
      AddToken(TokenType::QUESTION);
      break;
    case '~':
      AddToken(TokenType::TILDE);
      break;
    case '^':
      AddToken(Match('=') ? TokenType::CARET_ASSIGN : TokenType::CARET);
      break;
    case '@':
      AddToken(TokenType::AT);
      break;
    case '$':
      AddToken(TokenType::DOLLAR);
      break;
    case '#':
      AddToken(TokenType::HASH);
      break;
    case '|':
      AddToken(Match('=') ? TokenType::PIPE_ASSIGN : TokenType::PIPE);
      break;
    case ':':
      AddToken(Match(':') ? TokenType::DOUBLE_COLON : TokenType::COLON);
      break;
    case '%':
      AddToken(Match('=') ? TokenType::AMPERSAND_ASSIGN : TokenType::AMPERSAND);
      break;
    case '*':
      AddToken(Match('=') ? TokenType::STAR_ASSIGN : TokenType::STAR);
      break;
    case '!':
      AddToken(Match('=') ? TokenType::BANG_EQUAL : TokenType::BANG);
      break;
    case '=':
      AddToken(Match('=') ? TokenType::EQUAL : TokenType::ASSIGN);
      break;
    case '<':
      AddToken(Match('=')   ? TokenType::LESS_EQUAL
               : Match('<') ? TokenType::LEFT_SHIFT
                            : TokenType::LEFT_ANGLE);
      break;
    case '>':
      AddToken(Match('=')   ? TokenType::GREATER_EQUAL
               : Match('>') ? TokenType::RIGHT_SHIFT
                            : TokenType::RIGHT_ANGLE);
      break;
    case '/':
      if (Match('/')) {
        while (Peek() != '\n' && !IsAtEnd()) {
          Advance();
        }
      } else {
        AddToken(TokenType::SLASH);
      }
      break;
    case '"':
      String();
      break;
    default:
      if (IsDigit(c)) {
        Number();
      } else if (IsAlpha(c)) {
        Identifier();
      } else {
        std::cerr << "Unexpected character: " << c << std::endl;
      }
      break;
    }
  }

  m_tokens.emplace_back(TokenType::END_OF_FILE, "", m_line);
}

bool Lexer::Match(char expected) {
  if (IsAtEnd()) {
    return false;
  }

  if (m_source[m_current] != expected) {
    return false;
  }

  m_current++;
  return true;
}

void Lexer::String() {
  while (Peek() != '"' && !IsAtEnd()) {
    if (Peek() == '\n') {
      m_line++;
    }
    Advance();
  }

  if (IsAtEnd()) {
    std::cerr << "Unterminated string" << std::endl;
    return;
  }

  Advance();

  AddToken(TokenType::STR);
}

void Lexer::Number() {
  while (IsDigit(Peek())) {
    Advance();
  }

  if (Peek() == '.' && IsDigit(PeekNext())) {
    Advance();

    while (IsDigit(Peek())) {
      Advance();
    }
  }

  std::string num = m_source.substr(m_start, m_current - m_start);

  if (num.find('.') != std::string::npos) {
    if (num.find('f') != std::string::npos) {
      AddToken(TokenType::F32);
    } else {
      AddToken(TokenType::F64);
    }
  } else {
    i64 value = std::stoll(num);

    if (value >= std::numeric_limits<i8>::min() &&
        value <= std::numeric_limits<i8>::max()) {
      AddToken(TokenType::I8);
    } else if (value >= std::numeric_limits<i16>::min() &&
               value <= std::numeric_limits<i16>::max()) {
      AddToken(TokenType::I16);
    } else if (value >= std::numeric_limits<i32>::min() &&
               value <= std::numeric_limits<i32>::max()) {
      AddToken(TokenType::I32);
    } else {
      AddToken(TokenType::I64);
    }
  }

  AddToken(TokenType::NUMBER);
}

void Lexer::Identifier() {
  while (IsAlpha(Peek()) || IsDigit(Peek())) {
    Advance();
  }

  std::string text = m_source.substr(m_start, m_current - m_start);
  TokenType type = Keywords::GetKeywordType(text);
  AddToken(type);
}

void Lexer::PrintTokens() const {
  for (const auto &token : m_tokens) {
    std::cout << "Token: " << TokenTypeToString(token.GetType())
              << " Literal: " << token.GetLiteral() << std::endl;
  }
}
} // namespace Spectra
