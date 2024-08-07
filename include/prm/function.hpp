#ifndef PRM_FUNCTION_HPP
#define PRM_FUNCTION_HPP

#include <functional>
#include <string>
#include <vector>

namespace prm {

typedef const std::vector<std::string> &Args;

struct Function {
  std::string name;
  std::string usage;
  std::function<int(Args)> exec;
};

}; // namespace prm

#endif