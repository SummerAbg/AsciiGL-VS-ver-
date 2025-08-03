#pragma once

#include "at_Basic.h"
#include "at_Exception.h"

namespace AsciiTools {
class Option {
public:
  Option(int argc, char **argv) {
    this->argc = argc;
    for (int i = 0; i < argc; i++) {
      args.push_back(argv[i]);
    }
  }

  std::string getArg(int index) const {
    if (index >= 0 && index < args.size())
      return args[index];
    throw AsciiBasicException(__FUNC__, ArrayOverflow);
  }

  std::string operator[](int index) const {
    if (index >= 0 && index < args.size())
      return getArg(index);
    throw AsciiBasicException(__FUNC__, ArrayOverflow);
  }

  int getArgc() const { return argc; }

  auto begin() { return args.begin(); }
  auto end() { return args.end(); }

private:
  std::vector<std::string> args;
  int argc;
};
}; // namespace AsciiTools