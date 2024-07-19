#ifndef SPECRTAC_KEYWORDS_HPP
#define SPECRTAC_KEYWORDS_HPP

#include "../pch.hpp"
#include "token_type.hpp"

namespace Spectra {
class Keywords {
public:
  static TokenType GetKeywordType(const std::string &text);

private:
  Keywords() = default;
  ~Keywords() = default;
};

} // namespace Spectra

#endif // SPECRTAC_KEYWORDS_HPP
