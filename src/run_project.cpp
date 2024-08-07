#include <prm/prm.hpp>

#include <algorithm>
#include <fstream>
#include <iostream>

#include <libs/json.hpp>

int prm::run_project(Args args) {

  std::ifstream in("prm_config.json");
  if (!in.is_open()) {
    std::printf("Could not open prm_config.json\n");
    return 1;
  }

  nlohmann::json config;
  in >> config;
  in.close();

  std::string builder = config["builder"];

  int flag = 0;

  if (builder == "make") {
    flag = build_project(args);

    if (flag)

      return flag;
  } else {
    std::printf("Unknown builder\n");
    return 1;
  }

  std::string target = config["target"];

  for (auto &arg : args) {
    target += " " + arg;
  }

#ifdef _WIN32
  std::replace(target.begin(), target.end(), '/', '\\');
  flag = std::system((".\\" + target).c_str());
#else
  flag = std::system(("./" + target).c_str());
#endif

  return flag;
}