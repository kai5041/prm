#include <prm/core.hpp>

#include <fstream>
#include <iostream>

#include <libs/json.hpp>

using nlohmann::json;

namespace prm {

void generate_makefile(const std::string &project_name,
                       const std::string &extension) {
  std::ofstream makefile(project_name + "/Makefile");

  makefile << "PROJECT_NAME = " << project_name << std::endl;
  makefile << "SRC_DIR = src" << std::endl;
  makefile << "BUILD_DIR = build" << std::endl;
  makefile << "SRC = $(wildcard $(SRC_DIR)/*." << extension << ")" << std::endl;
  makefile << "TARGET = $(BUILD_DIR)/$(PROJECT_NAME)" << std::endl;

  if (extension == "c") {
    makefile << "CC_FLAGS = -Iinclude -std=c++17";
  } else {
    makefile << "CXX_FLAGS = -Iinclude -std=c++17";
  }

  makefile << "\n\n$(TARGET): $(SRC)" << std::endl;
  makefile << "\t@ mkdir -p $(BUILD_DIR)\n\t";
  if (extension == "c") {
    makefile << "$(CC) -o $@ $^ $(CXX_FLAGS)" << std::endl;
  } else {
    makefile << "$(CXX) -o $@ $^ $(CXX_FLAGS)\n";
  }

  makefile.close();
}

int create_project(std::vector<std::string> args) {
  std::string project_name = args[0];
  std::string language = args[1];

  if (fs::exists(project_name)) {
    std::cerr << "Error: Project " << project_name << " already exists"
              << std::endl;
    return 1;
  }

  fs::create_directory(project_name);

  if (language == "c_make" || language == "cpp_make") {
    fs::create_directory(project_name + "/src");
    fs::create_directory(project_name + "/include");
    fs::create_directory(project_name + "/include/libs");
    fs::create_directory(project_name + "/include/" + project_name);
    generate_makefile(project_name, language == "c_make" ? "c" : "cpp");

    std::ofstream file(project_name + "/src/" +
                       (language == "c_make" ? "main.c" : "main.cpp"));
    file << (language == "c_make"
                 ? "#include <stdio.h>\n\nint main() "
                   "{\n  printf(\"Hello world!\");\n  return 0;\n}\n"
                 : "#include <iostream>\n\nusing "
                   "namespace std;\n\nint main() {\n  cout << "
                   "\"Hello world!\";\n  return 0;\n}\n")
         << std::endl;

    file.close();

    file.open(project_name + "/prm.json");

    file << (json){{"project_executable",
                    fs::absolute(project_name + "/build/" + project_name)},
                   {"language", language},
                   {"prm_version", "0.0.1"}}
                .dump(2)
         << std::endl;

    file.close();

  } else {
    std::cout << "Invalid language" << std::endl;
  }

  return 0;
}

void create_help() {
  std::cout << "Usage: create <project_name> <language>" << std::endl;
}

} // namespace prm