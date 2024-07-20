#ifndef SPECTRAC_AST_HPP
#define SPECTRAC_AST_HPP

#include "../pch.hpp"

namespace Spectra {

class IAstNode;

using AstNodePtr = std::shared_ptr<IAstNode>;

class IAstNode {
public:
  virtual ~IAstNode() = default;
  virtual void Print() const = 0;
};
} // namespace Spectra

#endif // SPECTRAC_AST_HPP
