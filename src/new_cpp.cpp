#include <prm/prm.hpp>

#include <fstream>
#include <iostream>

void prm::create_cpp_project(const std::string &name,
                             const std::string &builder) {
  fs::create_directory(name);
  fs::create_directory(name + "/src");
  fs::create_directory(name + "/include");
  fs::create_directory(name + "/include/" + name);

  std::ofstream file;

  file.open(name + "/src/main.cpp");
  file << "#include <iostream>\n\nusing namespace std;\n\n";
  file << "int main() {\n";
  file << "  std::cout << \"Hello, World!\" << std::endl;\n";
  file << "  return 0;\n";
  file << "}\n";
  file.close();

  file.open(name + "/README.md");
  file << "# \n";
  file.close();

  if (builder == "make") {
    file.open(name + "/Makefile");
    file << "PROJECT_NAME = " << name << "\n";
    file << "BUILD_DIR = build\n";
    file << "SRC_DIR = src\n";
    file << "SRC = $(wildcard $(SRC_DIR)/*.cpp)\n\n";
    file << "CXX_FLAGS = -Iinclude\n\n";
    file << "$(BUILD_DIR)/$(PROJECT_NAME): $(SRC)\n";
    file << "\t@ mkdir -p $(BUILD_DIR)\n";
    file << "\t$(CXX) $(CXX_FLAGS) -o $@ $^\n\n";
    file.close();
  } else if (builder == "cmake") {
    std::printf("cmake not implemented yet\n");
  }
}
