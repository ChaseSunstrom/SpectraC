#include "keywords.hpp"
#include "token_type.hpp"

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
    {"var", TokenType::VAR_KW},
    {"const", TokenType::CONST_KW},
    {"static", TokenType::STATIC_KW},
    {"inline", TokenType::INLINE_KW},
    {"interface", TokenType::INTERFACE_KW},
    {"impls", TokenType::IMPLS_KW},
    {"str", TokenType::STR_KW},
    {"bool", TokenType::BOOL_KW},
    {"i8", TokenType::I8_KW},
    {"i16", TokenType::I16_KW},
    {"i32", TokenType::I32_KW},
    {"i64", TokenType::I64_KW},
    {"u8", TokenType::U8_KW},
    {"u16", TokenType::U16_KW},
    {"u32", TokenType::U32_KW},
    {"u64", TokenType::U64_KW},
    {"f32", TokenType::F32_KW},
    {"f64", TokenType::F64_KW}};

TokenType Keywords::GetKeywordType(const std::string &text) {
  auto it = keywords.find(text);
  if (it != keywords.end()) {
    return it->second;
  }
  return TokenType::IDENTIFIER;
}


} // namespace Spectra
