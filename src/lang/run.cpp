//
// Created by chase on 7/8/24. nuh uh
//

#include "run.hpp"
#include "../lexer/lexer.hpp"
#include "args.hpp"

namespace Spectra {
void Run::RunFiles(const std::vector<Args> &parsed_args) {
  std::ifstream file;
  std::stringstream buffer;

  for (const auto &parsed_arg : parsed_args) {
    // Print the arguments
    std::ifstream file(parsed_arg.GetPath());
    if (!file.is_open()) {
      std::cerr << "Failed to open file: " << parsed_arg.GetPath() << std::endl;
      continue;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    std::string source = buffer.str();
    std::cout << "File Content: " << std::endl << source << std::endl;

    Lexer lexer(source);
    lexer.LexTokens();
    lexer.PrintTokens();

    // Clear the buffer for the next file
    buffer.str("");
    buffer.clear();
  }
}

void Run::RunPrompt() { std::cout << "Running prompt" << std::endl; }
} // namespace Spectra
