#include <prm/core.hpp>

#include <filesystem>
#include <fstream>
#include <iostream>

#include <unistd.h>

#include <libs/json.hpp>

namespace prm {

void create_makefile(const std::string &extension,
                     const std::string &project_name) {

  std::ofstream makefile(project_name + "/Makefile");

  makefile << "PROJECT_NAME = " << project_name << "\n";
  makefile << "SRC_DIR = src\n";
  makefile << "BUILD_DIR = build\n\n";

  makefile << "SRC = $(wildcard $(SRC_DIR)/*." << extension << ")\n";
  makefile << "TARGET = $(BUILD_DIR)/$(PROJECT_NAME)\n\n";

  if (extension == "cpp") {
    makefile << "CXX_FLAGS = -Iinclude\n\n";
  } else if (extension == "c") {
    makefile << "CC_FLAGS = -Iinclude\n\n";
  }

  makefile << "$(TARGET): $(SRC)\n";
  if (extension == "cpp") {
    makefile << "\t$(CXX) -o $@ $^ $(CXX_FLAGS)\n\n";
  } else if (extension == "c") {
    makefile << "\t$(CC) -o $@ $^ $(CC_FLAGS)\n\n";
  } else {
    std::cerr << "Unsupported language: " << extension << std::endl;
    exit(1);
  }

  makefile.close();
}

int create_cpp_make(const std::string &project_name) {
  create_makefile("cpp", project_name);

  return 0;
}

int create(const std::vector<std::string> &args) {
  std::string project_name = args[0];
  std::string language = args[1];

  if (language != "cpp_make") {
    std::cerr << "Unknown language: " << language << std::endl;
    return 1;
  }

  if (std::filesystem::exists(project_name)) {
    std::cerr << "Directory already exists, aborting" << std::endl;
    return 1;
  }

  try {
    std::filesystem::create_directory(project_name);
  } catch (const std::filesystem::filesystem_error &e) {
    std::cerr << "Failed to create directory: " << e.what() << std::endl;
    return 1;
  }

  if (language == "c_make" || language == "cpp_make") {

    std::filesystem::create_directory(project_name + "/src");
    std::filesystem::create_directory(project_name + "/include");
    std::filesystem::create_directory(project_name + "/include/" +
                                      project_name);
    std::filesystem::create_directory(project_name + "/include/libs");
    std::filesystem::create_directory(project_name + "/build");

    {
      nlohmann::ordered_json config = {
          {"project_name", project_name},
          {"language", language},
          {"version", "0.0.1"},
      };

      std::ofstream config_file(project_name + "/prm.json");
      config_file << config.dump(2);
      config_file.close();
    }

    if (language == "cpp_make") {
      create_cpp_make(project_name);

      std::ofstream main_cpp(project_name + "/src/main.cpp");
      main_cpp << "#include <"
               << "iostream>\n\nusing namespace std; \n\nint main() {\n";

      main_cpp << "  \n  \n  \n  return 0;\n}\n";

      main_cpp.close();
    }
  }

  return 0;
}

void create_help() {
  std::cout << "Usage: create <project_name> <language>" << std::endl;
}

} // namespace prm