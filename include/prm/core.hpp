#ifndef PRM_CORE_HPP
#define PRM_CORE_HPP

#define PRM_VERSION "0.0.1"

#include <filesystem>
#include <prm/function.hpp>

namespace prm {

int create_project(std::vector<std::string> args);
void create_help();

int run(std::vector<std::string> args);

static const std::vector<Function> commands = {
    {"create", create_project, 2, create_help},
    {"new", create_project, 2, create_help},
    {"run", run, -1, nullptr}};

namespace fs = std::filesystem;

} // namespace prm

#endif