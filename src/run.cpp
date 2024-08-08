#include <prm/prm.hpp>

#include <algorithm>
#include <fstream>
#include <iostream>

#include <libs/json.hpp>

int prm::run_project(prm::prm_ctx &ctx) {

  ctx.open("prm_config.json");
  if (!ctx.is_open()) {
    std::printf("Could not open prm_config.json\n");
    return 1;
  }

  nlohmann::json config = nlohmann::json::parse(ctx.read());
  ctx.close();

  std::string builder = config["builder"];

  int flag = 0;

  if (builder == "make") {
    flag = build_project(ctx);

    if (flag)
      return flag;
  } else {
    std::printf("Unknown builder\n");
    return 1;
  }

  std::string target = config["target"];

  for (int i = 0; i < ctx.args_size(); i++) {
    target += " " + ctx.get_arg(i);
  }

#ifdef _WIN32
  std::replace(target.begin(), target.end(), '/', '\\');
  flag = std::system((".\\" + target).c_str());
#else
  flag = std::system(("./" + target).c_str());
#endif

  return flag;
}