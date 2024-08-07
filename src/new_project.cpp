#include <libs/json.hpp>
#include <prm/prm.hpp>

#include <fstream>
#include <iostream>

int prm::new_project(const Args &project_args) {
  if (project_args.size() < 2)
    return 2; // Not enough arguments

  // Extract arguments
  const std::string name = project_args[0];
  const std::string language = project_args[1];
  const std::string builder = project_args.size() > 2 ? project_args[2] : "";
  const std::string vcs = project_args.size() > 3 ? project_args[3] : "";

  // Create project configuration
  nlohmann::json project_config{
      {"name", name},
      {"language", language},
      {"builder", builder},
      {"vcs", vcs},
      {"prm_version", PRM_VERSION},
  };

  // Check if language is supported
  auto it = std::find_if(
      prm::supported_languages.begin(), prm::supported_languages.end(),
      [&](const auto &lang) { return lang.first == language; });

  if (it == prm::supported_languages.end()) {
    std::printf("Language '%s' is not supported\n", language.c_str());
    return 1;
  }

  // Check if builder is supported
  const auto &builders = it->second;
  if (!builder.empty() &&
      std::find(builders.begin(), builders.end(), builder) == builders.end()) {
    std::printf("Builder '%s' is not supported\n", builder.c_str());
    return 1;
  }

  // Check if VCS is supported
  if (vcs == "git") {
  } else if (!vcs.empty()) {
    std::printf("VCS '%s' is not supported\n", vcs.c_str());
    return 1;
  }

  if (fs::exists(name)) {
    std::printf("Directory '%s' already exists\n", name.c_str());
    return 1;
  }

  if (language == "cpp") {
    create_cpp_project(name, builder);

    #ifdef _WIN32
      project_config += {"target", "build/" + name + ".exe"};
    #else
      project_config += {"target", "build/" + name};
    #endif

  


  } else {
    std::printf("Language '%s' is not implemented yet\n", language.c_str());
  }

  // Write project configuration to JSON file
  std::ofstream file;
  file.open(name + "/prm_config.json");
  file << project_config.dump(2);
  file.close();

  return 0;
}