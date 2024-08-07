#ifndef PRM_PRM_HPP
#define PRM_PRM_HPP

#include <prm/function.hpp>

#include <filesystem>
#include <utility>

namespace fs = std::filesystem;

namespace prm {

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