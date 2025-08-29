#pragma once

#include "at_basic.h"
#include "at_exception.h"

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
    throw AsciiBasicException(ArrayOverflow);
  }

  std::string operator[](int index) const {
    if (index >= 0 && index < args.size())
      return getArg(index);
    throw AsciiBasicException(ArrayOverflow);
  }

  int getArgc() const noexcept { return argc; }

  auto begin() const noexcept { return args.begin(); }
  auto end() const noexcept { return args.end(); }

private:
  std::vector<std::string> args;
  int argc;
};
}; // namespace AsciiTools