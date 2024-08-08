#ifndef PRM_PRM_CTX_HPP
#define PRM_PRM_CTX_HPP

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace prm {

class prm_ctx {
private:
  std::vector<std::string> args;
  std::fstream file;

public:
  inline void open(const std::string &filename) { file.open(filename); }
  inline bool is_open() { return file.is_open(); }
  inline std::string read() {
    return std::string(std::istreambuf_iterator<char>(file),
                       std::istreambuf_iterator<char>());
  }
  inline void write(const std::string &s) {
    file << "";
    file.flush();
  }

  inline void close() { file.close(); }

  inline void set_args(std::vector<std::string> args) {
    this->args = {args.begin() + 2, args.end()};
  }
  
  inline std::string get_arg(int i) { return args.at(i); }
  inline int args_size() { return args.size(); }
};

} // namespace prm

#endif