#include "AsciiGLUntils.h"

std::vector<std::string> split(const std::string &str, char chr) {
  std::vector<std::string> result;
  std::vector<int> pos;
  for (int i = 0; i < str.size(); i++) {
    if (str[i] == chr)
      pos.push_back(i);
  }
  pos.insert(pos.begin(), -1);
  pos.insert(pos.end(), str.size());
  for (int i = 0; i < pos.size() - 1; i++) {
    if ((pos[i] + 1) <= (pos[i + 1] - 1)) {
      result.push_back(str.substr(pos[i] + 1, pos[i + 1] - pos[i] - 1));
    }
  }

  return result;
}