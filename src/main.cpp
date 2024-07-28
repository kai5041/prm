#include <iostream>

#include <prm/core.hpp>

int main(int argc, char **argv) {

  if (argc == 1) {
    std::printf("PRM version %s\n", PRM_VERSION);
    return 0;
  }

  std::string command = argv[1];
  std::vector<std::string> args;

  for (int i = 2; i < argc; i++) {
    args.push_back(argv[i]);
  }

  for (auto &c : prm::commands) {
    if (c.name == command) {
      if (c.args_expected != args.size() && c.args_expected != -1) {
        c.help();
        return 1;
      }

      return c.func(args);
    }
  }

  std::cerr << "Error: Invalid command " << command << std::endl;

  return 1;
}