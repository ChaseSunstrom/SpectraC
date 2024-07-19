#include "lang/args.hpp"
#include "lang/run.hpp"
#include "pch.hpp"

i32 main(i32 argc, char *argv[]) {
  if (argc == 1) {
    Spectra::Run::RunPrompt();
  } else {
    std::vector<Spectra::Args> parsed_args;
    std::vector<std::string> args;
    std::filesystem::path current_path;

    for (i32 i = 1; i < argc; i++) {
      if (argv[i][0] == '-') {
        args.push_back(argv[i]);
      } else {
        if (!current_path.empty()) {
          parsed_args.emplace_back(current_path, args);
          args.clear();
        }
        current_path = argv[i];
      }
    }

    // If there's a remaining file path and arguments, add them
    if (!current_path.empty()) {
      parsed_args.emplace_back(current_path, args);
    }

    Spectra::Run::RunFiles(parsed_args);
  }

  return 0;
}
