#ifndef PRM_PRM_HPP
#define PRM_PRM_HPP

#include <prm/function.hpp>
#include <prm/prm_ctx.hpp>

#include <filesystem>
#include <utility>

#ifndef PRM_VERSION
#define PRM_VERSION "0.0.1"
#endif

namespace fs = std::filesystem;

namespace prm {

void create_cpp_project(const std::string &name, const std::string &builder);

int new_project(prm_ctx &ctx);
int build_project(prm_ctx &ctx);
int run_project(prm_ctx &ctx);

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