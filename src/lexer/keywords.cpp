#include "keywords.hpp"

namespace Spectra {

// Private to this file
static const std::unordered_map<std::string, TokenType> keywords = {
    {"and", TokenType::AND_KW},
    {"or", TokenType::OR_KW},
    {"if", TokenType::IF_KW},
    {"else", TokenType::ELSE_KW},
    {"for", TokenType::FOR_KW},
    {"while", TokenType::WHILE_KW},
    {"break", TokenType::BREAK_KW},
    {"continue", TokenType::CONTINUE_KW},
    {"return", TokenType::RETURN_KW},
    {"true", TokenType::TRUE_KW},
    {"false", TokenType::FALSE_KW},
    {"null", TokenType::NULL_KW},
    {"fn", TokenType::FN_KW},
    {"class", TokenType::CLASS_KW},
    {"struct", TokenType::STRUCT_KW},
    {"enum", TokenType::ENUM_KW},
    {"use", TokenType::USE_KW},
    {"type", TokenType::TYPE_KW},
    {"extern", TokenType::EXTERN_KW},
    {"foreach", TokenType::FOREACH_KW},
    {"in", TokenType::IN_KW},
    {"as", TokenType::AS_KW},
    {"is", TokenType::IS_KW},
    {"match", TokenType::MATCH_KW},
    {"case", TokenType::CASE_KW},
    {"default", TokenType::DEFAULT_KW},
    {"new", TokenType::NEW_KW},
    {"delete", TokenType::DELETE_KW},
    {"sizeof", TokenType::SIZEOF_KW},
    {"typeof", TokenType::TYPEOF_KW},
    {"pub", TokenType::PUB_KW},
    {"priv", TokenType::PRIV_KW},
    {"i8", TokenType::I8},
    {"i16", TokenType::I16},
    {"i32", TokenType::I32},
    {"i64", TokenType::I64},
    {"u8", TokenType::U8},
    {"u16", TokenType::U16},
    {"u32", TokenType::U32},
    {"u64", TokenType::U64},
    {"f32", TokenType::F32},
    {"f64", TokenType::F64}};

TokenType Keywords::GetKeywordType(const std::string &text) {
  auto it = keywords.find(text);
  if (it != keywords.end()) {
    return it->second;
  }
  return TokenType::IDENTIFIER;
}
} // namespace Spectra
