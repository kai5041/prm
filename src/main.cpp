#include <iostream>

#include <filesystem>

#include <prm/core.hpp>

int main(int argc, char **argv) {
  std::string program = std::filesystem::path(argv[0]).filename().string();

  if (argc < 2) {
    std::printf("PRM version %s\n", PRM_VERSION);
    return 0;
  }

  std::string command = argv[1];
  std::vector<std::string> args;

  for (int i = 2; i < argc; i++) {
    args.push_back(argv[i]);
  }

  for (const auto &func : prm::functions) {
    if (func.name == command) {
      if (args.size() < func.expeced_args) {
        func.help();
        return 1;
      }

      return func.func(args);
    }
  }

  std::cout << "Unknown command: " << command << std::endl;

  return 0;
}