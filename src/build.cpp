#include <prm/prm.hpp>

#include <fstream>
#include <iostream>

#include <libs/json.hpp>

int prm::build_project(prm_ctx &ctx) {

  ctx.open("prm_config.json");
  if (!ctx.is_open()) {
    std::printf("Could not open prm_config.json\n");
    return 1;
  }

  nlohmann::json config = nlohmann::json::parse(ctx.read());
  
  ctx.close();

  std::string version = config["prm_version"];

  if (version != PRM_VERSION) {
    std::printf("Version mismatch, expected: %s, got %s\n", PRM_VERSION,
                version.c_str());
    return 1;
  }

  std::string builder = config["builder"];

  int flag = 0;

  if (builder == "make") {
    flag = std::system("make");
  } else {
    std::printf("Unknown builder\n");
    return 1;
  }

  if (flag != 0) {
    std::printf("Failed to build project\n");
    return 1;
  }

  // TODO
  return 0;
}