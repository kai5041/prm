#include <prm/core.hpp>

#include <fstream>
#include <libs/json.hpp>

namespace prm {

int run(std::vector<std::string> args) {
  nlohmann::json data;

  std::ifstream file("prm.json");
  file >> data;
  file.close();

  std::string executable = data["project_executable"];
  std::string language = data["language"];

  if (language == "c_make" || language == "cpp_make") {
    std::string command = "make";
    system(command.c_str());

    command = executable + " ";
    for (auto &arg : args) {
      command += arg + " ";
    }

    system(command.c_str());
  }

  return 0;
}

} // namespace prm