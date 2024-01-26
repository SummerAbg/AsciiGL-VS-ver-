#include "AsciiGLUntils.h"

std::vector<std::string> split(const std::string &str, char chr) {
  if (str == "")
    return std::vector<std::string>();

  std::vector<std::string> result;
  std::vector<int> pos;
  for (int i = 0; i < str.size(); i++) {
    if (str[i] == chr)
      pos.push_back(i);
  }
  pos.insert(pos.begin(), -1);
  pos.insert(pos.end(), (int)str.size());
  for (int i = 0; i < pos.size() - 1; i++) {
    if ((pos[i] + 1) <= (pos[i + 1] - 1)) {
      result.push_back(str.substr(pos[i] + 1, pos[i + 1] - pos[i] - 1));
    }
  }

  return result;
}

int stringToInt(const std::string &str) { return atoi(str.c_str()); }

int charToInt(char chr) { return atoi(std::string(1, chr).c_str()); }

bool charToBool(char chr) { return intToBool(charToInt(chr)); }

bool intToBool(int number) { return (number >= 1) ? true : false; }

int getStringLineCount(const std::string &str) {
  int result = static_cast<int>(split(str, '\n').size());
  return result;
}

std::string interceptString(const std::string &str, int line1, int line2) {
  const auto &tokens = split(str, '\n');
  std::vector<std::string> strBlocks;

  if (line1 <= tokens.size() && line2 <= tokens.size() && line1 > 0 &&
      line2 > 0 && line1 < line2) {
    for (int i = line1 - 1; i < line2; i++) {
      strBlocks.push_back(tokens[i]);
    }
  }

  std::string result;
  for (const auto &index : strBlocks) {
    result += index + "\n";
  }
  return result;
}
