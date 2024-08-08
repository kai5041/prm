#ifndef PRM_PRM_HPP
#define PRM_PRM_HPP

#include <prm/function.hpp>

#include <filesystem>
#include <utility>

#ifndef PRM_VERSION
#define PRM_VERSION "0.0.1"
#endif

namespace fs = std::filesystem;

namespace prm {

class prm_ctx {
private:
  std::ifstream file;

public:
  inline void open(const std::string &filename) { file.open(filename); }
  inline bool is_open() { return file.is_open(); }
  inline std::string read() {
    return std::string(std::istreambuf_iterator<char>(file),
                       std::istreambuf_iterator<char>());
  }
  inline void close() { file.close(); }
};

int new_project(Args args);

void create_cpp_project(const std::string &name, const std::string &builder);

int build_project(Args args);
int run_project(Args args);

static std::vector<prm::Function> functions = {
    {"new", "prm new <name> <language> [options]", prm::new_project},
    {"build", "prm build", prm::build_project},
    {"run", "prm run [options]", prm::run_project},
};

static std::vector<std::pair<std::string, std::vector<std::string>>>
    supported_languages = {{
                               "cpp",
                               {"make", "cmake"},
                           },
                           {
                               "c",
                               {"make", "cmake"},
                           }};
} // namespace prm

#endif