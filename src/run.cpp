#include <prm/core.hpp>

#include <fstream>
#include <iostream>
#include <unistd.h>

#include <libs/json.hpp>

namespace prm {

int run(const std::vector<std::string> &args) {
  std::string project_name;
  std::string language;

  std::ifstream prm_file("prm.json");
  if (!prm_file.is_open()) {
    std::cerr << "Error: could not find prm.json" << std::endl;
    exit(1);
  }

  nlohmann::json config;
  prm_file >> config;
  project_name = config["project_name"];
  language = config["language"];

  if (language == "cpp_make" || language == "c_make") {
    int exit_code = std::system("make");

    if (exit_code != 0) {
      std::cerr << "Failed to run make" << std::endl;
      exit(1);
    }

#ifdef _WIN32
    std::string command = "build\\" + project_name + ".exe";
#else
    std::string command = "./build/" + project_name;
#endif

    exit_code = std::system(command.c_str());

    if (exit_code != 0) {
      std::cerr << "Failed to run the executable" << std::endl;
      exit(1);
    }

  } else {
    std::cerr << "Unsupported language: " << language << std::endl;
    exit(1);
  }

  return 0;
}

void run_help() { std::cout << "Supported languages:\ncpp_make" << std::endl; }

} // namespace prm