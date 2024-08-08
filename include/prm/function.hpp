#ifndef PRM_FUNCTION_HPP
#define PRM_FUNCTION_HPP

#include <functional>
#include <prm/prm_ctx.hpp>
#include <string>
#include <vector>

namespace prm {

struct Function {
  std::string name;
  std::string usage;
  std::function<int(prm_ctx &)> exec;
};

}; // namespace prm

#endif