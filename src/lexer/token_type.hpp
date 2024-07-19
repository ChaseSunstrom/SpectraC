#ifndef SPECTRAC_TOKEN_TYPE_HPP
#define SPECTRAC_TOKEN_TYPE_HPP

#include "../pch.hpp"

namespace Spectra {

enum class TokenType {

  // Single-character tokens
  LEFT_PAREN,
  RIGHT_PAREN,
  LEFT_BRACE,
  RIGHT_BRACE,
  LEFT_BRACKET,
  RIGHT_BRACKET,
  COMMA,
  DOT,
  MINUS,
  PLUS,
  SEMICOLON,
  SLASH,
  STAR,
  PERCENT,
  COLON,
  QUESTION,
  LEFT_ANGLE,
  RIGHT_ANGLE,
  ASSIGN,
  BANG,
  TILDE,
  CARET,
  AMPERSAND,
  PIPE,
  AT,
  ARM,
  DOLLAR,
  HASH,
  UNDERSCORE,

  // Two-character tokens
  BANG_EQUAL,
  EQUAL,
  GREATER_EQUAL,
  LESS_EQUAL,
  PLUS_ASSIGN,
  MINUS_ASSIGN,
  STAR_ASSIGN,
  SLASH_ASSIGN,
  AMPERSAND_ASSIGN,
  PIPE_ASSIGN,
  CARET_ASSIGN,
  PERCENT_ASSIGN,
  LEFT_SHIFT,
  RIGHT_SHIFT,
  DOUBLE_COLON,
  RANGE,
  ARROW,
  INCREMENT,
  DECREMENT,

  // Three-character tokens
  LEFT_SHIFT_ASSIGN,
  RIGHT_SHIFT_ASSIGN,
  RANGE_INCLUSIVE,

  // Keywords
  AND_KW,
  OR_KW,
  IF_KW,
  ELSE_KW,
  WHILE_KW,
  FOR_KW,
  BREAK_KW,
  CONTINUE_KW,
  RETURN_KW,
  TRUE_KW,
  FALSE_KW,
  NULL_KW,
  FN_KW,
  CLASS_KW,
  STRUCT_KW,
  ENUM_KW,
  USE_KW,
  ANALYZE_KW,
  TYPE_KW,
  EXTERN_KW,
  FOREACH_KW,
  IN_KW,
  AS_KW,
  IS_KW,
  MATCH_KW,
  CASE_KW,
  DEFAULT_KW,
  NEW_KW,
  DELETE_KW,
  SIZEOF_KW,
  TYPEOF_KW,
  VAR_KW,
  CONST_KW,
  STATIC_KW,
  INLINE_KW,
  PUB_KW,
  PRIV_KW,
  INTERFACE_KW,
  IMPLS_KW,
  STR_KW,
  BOOL_KW,
  I8_KW,
  I16_KW,
  I32_KW,
  I64_KW,
  U8_KW,
  U16_KW,
  U32_KW,
  U64_KW,
  F32_KW,
  F64_KW,

  // Literals
  IDENTIFIER,
  STR,
  BOOL,
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

  // This gets parsed into the specific number types
  // after the lexer has finished lexing
  NUMBER,

  END_OF_FILE
};

std::string TokenTypeToString(TokenType type);

} // namespace Spectra

#endif
