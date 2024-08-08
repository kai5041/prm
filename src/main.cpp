#include <iostream>

#include <prm/prm.hpp>

int main(int argc, char **argv) {
  if (argc == 1) {
    std::printf("PRM | A Project Manager VERSION %s\n", PRM_VERSION);
    return 0;
  }

  prm::prm_ctx ctx;

  std::string command = argv[1];
  ctx.set_args(std::vector<std::string>(argv, argv + argc));

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

  flag = func->exec(ctx);

  if (flag == 2) {
    std::printf("Usage: %s\n", func->usage.c_str());
    return 1;
  }

  return flag;
}