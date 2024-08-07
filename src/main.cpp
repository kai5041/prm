#include <iostream>

#include <prm/prm.hpp>

int main(int argc, char **argv) {
  if (argc == 1) {
    std::printf("PRM | A Project Manager VERSION %s\n", PRM_VERSION);
    return 0;
  }

  std::string command = argv[1];
  std::vector<std::string> args;

  for (int i = 2; i < argc; i++)
    args.push_back(argv[i]);

  prm::Function *func = nullptr;
  int flag = 0;

  for (auto &f : prm::functions) {
    if (f.name == command) {
      func = &f;
      break;
    }
  }

  if (func == nullptr) {
    std::printf("Unknown command: %s\n", command.c_str());
    return 1;
  }

  flag = func->exec(args);

  if (flag == 2) {
    std::printf("Usage: %s\n", func->usage.c_str());
    return 1;
  }

  return flag;
}