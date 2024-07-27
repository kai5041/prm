#ifndef PRM_CORE_HPP
#define PRM_CORE_HPP

#define PRM_VERSION "0.0.1"

#include <functional>
#include <string>
#include <utility>
#include <vector>

namespace prm {

int create(const std::vector<std::string> &args);
void create_help();

int run(const std::vector<std::string> &args);
void run_help();

struct Function {
  std::string name;
  std::function<int(const std::vector<std::string> &)> func;
  int expeced_args;
  std::function<void()> help;
};

static std::vector<prm::Function> functions = {
    {"create", create, 2, prm::create_help},
    {"run", run, 0, prm::run_help},
};

} // namespace prm

#endif