#ifndef PRM_FUNCTION_HPP
#define PRM_FUNCTION_HPP

#include <functional>
#include <string>
#include <vector>

namespace prm {

struct Function {
  std::string name;
  std::function<int(std::vector<std::string>)> func;
  int args_expected;
  std::function<void()> help;
};

} // namespace prm

#endif