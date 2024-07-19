#include "token_type.hpp"

namespace Spectra {

std::string TokenTypeToString(TokenType type) {
  switch (type) {
  case TokenType::LEFT_PAREN:
    return "LEFT_PAREN";
  case TokenType::RIGHT_PAREN:
    return "RIGHT_PAREN";
  case TokenType::LEFT_BRACE:
    return "LEFT_BRACE";
  case TokenType::RIGHT_BRACE:
    return "RIGHT_BRACE";
  case TokenType::LEFT_BRACKET:
    return "LEFT_BRACKET";
  case TokenType::RIGHT_BRACKET:
    return "RIGHT_BRACKET";
  case TokenType::COMMA:
    return "COMMA";
  case TokenType::DOT:
    return "DOT";
  case TokenType::MINUS:
    return "MINUS";
  case TokenType::PLUS:
    return "PLUS";
  case TokenType::SEMICOLON:
    return "SEMICOLON";
  case TokenType::SLASH:
    return "SLASH";
  case TokenType::STAR:
    return "STAR";
  case TokenType::PERCENT:
    return "PERCENT";
  case TokenType::COLON:
    return "COLON";
  case TokenType::QUESTION:
    return "QUESTION";
  case TokenType::LEFT_ANGLE:
    return "LEFT_ANGLE";
  case TokenType::RIGHT_ANGLE:
    return "RIGHT_ANGLE";
  case TokenType::ASSIGN:
    return "ASSIGN";
  case TokenType::BANG:
    return "BANG";
  case TokenType::TILDE:
    return "TILDE";
  case TokenType::CARET:
    return "CARET";
  case TokenType::AMPERSAND:
    return "AMPERSAND";
  case TokenType::PIPE:
    return "PIPE";
  case TokenType::AT:
    return "AT";
  case TokenType::DOLLAR:
    return "DOLLAR";
  case TokenType::HASH:
    return "HASH";
  case TokenType::UNDERSCORE:
    return "UNDERSCORE";
  case TokenType::BANG_EQUAL:
    return "BANG_EQUAL";
  case TokenType::EQUAL:
    return "EQUAL";
  case TokenType::GREATER_EQUAL:
    return "GREATER_EQUAL";
  case TokenType::LESS_EQUAL:
    return "LESS_EQUAL";
  case TokenType::PLUS_ASSIGN:
    return "PLUS_ASSIGN";
  case TokenType::MINUS_ASSIGN:
    return "MINUS_ASSIGN";
  case TokenType::STAR_ASSIGN:
    return "STAR_ASSIGN";
  case TokenType::SLASH_ASSIGN:
    return "SLASH_ASSIGN";
  case TokenType::AMPERSAND_ASSIGN:
    return "AMPERSAND_ASSIGN";
  case TokenType::PIPE_ASSIGN:
    return "PIPE_ASSIGN";
  case TokenType::CARET_ASSIGN:
    return "CARET_ASSIGN";
  case TokenType::LEFT_SHIFT:
    return "LEFT_SHIFT";
  case TokenType::RIGHT_SHIFT:
    return "RIGHT_SHIFT";
  case TokenType::DOUBLE_COLON:
    return "DOUBLE_COLON";
  case TokenType::RANGE:
    return "RANGE";
  case TokenType::ARROW:
    return "ARROW";
  case TokenType::INCREMENT:
    return "INCREMENT";
  case TokenType::DECREMENT:
    return "DECREMENT";
  case TokenType::LEFT_SHIFT_ASSIGN:
    return "LEFT_SHIFT_ASSIGN";
  case TokenType::RIGHT_SHIFT_ASSIGN:
    return "RIGHT_SHIFT_ASSIGN";
  case TokenType::RANGE_INCLUSIVE:
    return "RANGE_INCLUSIVE";
  case TokenType::AND_KW:
    return "AND_KW";
  case TokenType::OR_KW:
    return "OR_KW";
  case TokenType::IF_KW:
    return "IF_KW";
  case TokenType::ELSE_KW:
    return "ELSE_KW";
  case TokenType::PUB_KW:
    return "PUB_KW";
  case TokenType::PRIV_KW:
    return "PRIV_KW";
  case TokenType::WHILE_KW:
    return "WHILE_KW";
  case TokenType::FOR_KW:
    return "FOR_KW";
  case TokenType::BREAK_KW:
    return "BREAK_KW";
  case TokenType::CONTINUE_KW:
    return "CONTINUE_KW";
  case TokenType::RETURN_KW:
    return "RETURN_KW";
  case TokenType::TRUE_KW:
    return "TRUE_KW";
  case TokenType::FALSE_KW:
    return "FALSE_KW";
  case TokenType::NULL_KW:
    return "NULL_KW";
  case TokenType::FN_KW:
    return "FN_KW";
  case TokenType::CLASS_KW:
    return "CLASS_KW";
  case TokenType::STRUCT_KW:
    return "STRUCT_KW";
  case TokenType::ENUM_KW:
    return "ENUM_KW";
  case TokenType::USE_KW:
    return "USE_KW";
  case TokenType::TYPE_KW:
    return "TYPE_KW";
  case TokenType::EXTERN_KW:
    return "EXTERN_KW";
  case TokenType::FOREACH_KW:
    return "FOREACH_KW";
  case TokenType::IN_KW:
    return "IN_KW";
  case TokenType::AS_KW:
    return "AS_KW";
  case TokenType::IS_KW:
    return "IS_KW";
  case TokenType::MATCH_KW:
    return "MATCH_KW";
  case TokenType::CASE_KW:
    return "CASE_KW";
  case TokenType::DEFAULT_KW:
    return "DEFAULT_KW";
  case TokenType::NEW_KW:
    return "NEW_KW";
  case TokenType::DELETE_KW:
    return "DELETE_KW";
  case TokenType::SIZEOF_KW:
    return "SIZEOF_KW";
  case TokenType::TYPEOF_KW:
    return "TYPEOF_KW";
  case TokenType::IDENTIFIER:
    return "IDENTIFIER";
  case TokenType::STR:
    return "STR";
  case TokenType::BOOL:
    return "BOOL";
  case TokenType::I8:
    return "I8";
  case TokenType::I16:
    return "I16";
  case TokenType::I32:
    return "I32";
  case TokenType::I64:
    return "I64";
  case TokenType::U8:
    return "U8";
  case TokenType::U16:
    return "U16";
  case TokenType::U32:
    return "U32";
  case TokenType::U64:
    return "U64";
  case TokenType::F32:
    return "F32";
  case TokenType::F64:
    return "F64";
  case TokenType::NUMBER:
    return "NUMBER";
  case TokenType::END_OF_FILE:
    return "END_OF_FILE";
  default:
    return "UNKNOWN_TOKEN_TYPE";
  }
}

} // namespace Spectra
