#include "at_Basic.h"
#include "at_Tools.h"

namespace AsciiTools {
std::vector<std::string> split(const std::string &str, char chr) {
  if (str == "")
    return std::vector<std::string>();

  std::vector<std::string> ret;
  std::vector<int> pos;

  const int size_str = str.size();
  for (int i = 0; i < size_str; i++) {
    if (str[i] == chr)
      pos.emplace_back(i);
  }

  pos.insert(pos.begin(), -1);
  pos.insert(pos.end(), size_str);

  int pos_a;
  int pos_b;
  const int size_pos = pos.size() - 1;
  for (int i = 0; i < size_pos; i++) {
    pos_a = pos[i] + 1;
    pos_b = pos[i + 1] - 1;
    if (pos_a <= pos_b)
      ret.emplace_back(str.substr(pos_a, pos_b - pos_a + 1));
  }

  return ret;
}

void setWordColor(const AsciiColor &color) {
  printf("\033[38;2;%d;%d;%dm", color.r, color.g, color.b);
}

void setBackgroundColor(const AsciiColor &color) {
  printf("\033[48;2;%d;%d;%dm", color.r, color.g, color.b);
}

void setColor(const AsciiTextColor &color) {
  setWordColor(color.color_text);
  setBackgroundColor(color.color_background);
}

AsciiColor mixAsciiColor(const AsciiColor &color1, const AsciiColor &color2) {
  AsciiColor ret;
  ret.a = (1.0 - ((1.0 - color1.a) * (1.0 - color2.a)));
  ret.r = static_cast<int>(
      (color1.r * color1.a + color2.r * color2.a * (1.0 - color1.a)) / ret.a);
  ret.g = static_cast<int>(
      (color1.g * color1.a + color2.g * color2.a * (1.0 - color1.a)) / ret.a);
  ret.b = static_cast<int>(
      (color1.b * color1.a + color2.b * color2.a * (1.0 - color1.a)) / ret.a);

  return ret;
}

AsciiTextColor mixAsciiTextColor(const AsciiTextColor &color1,
                                 const AsciiTextColor &color2) {
  AsciiTextColor ret;
  ret.color_text = mixAsciiColor(color1.color_text, color2.color_text);
  ret.color_background =
      mixAsciiColor(color1.color_background, color2.color_background);
  return ret;
}

int getStringLineCount(const std::string &str) {
  const int ret = static_cast<int>(split(str, '\n').size());
  return ret;
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

  std::string ret;
  for (const auto &index : strBlocks) {
    ret += index + "\n";
  }
  return ret;
}

std::string spliceString(const std::string &str,
                         const std::vector<std::string> &strs) {
  std::string ret;
  const int index_end = strs.size() - 1;
  for (const auto &index : strs) {
    ret += index;
    if (index != strs[index_end])
      ret += str;
  }
  return ret;
}

std::vector<std::string> bracketMatch(const std::string &str, int layerCount,
                                      char leftBracket, char rightBracket) {
  std::vector<std::string> ret;
  std::stack<int> positions_left;
  std::stack<int> positions_right;

  if (layerCount <= 0)
    throw AsciiBasicException(__FUNC__, "layerCount应该大于0!");

  const int size_str = str.size();
  char index_chr;
  int size_postions_left;
  for (int i = 0; i < size_str; i++) {
    index_chr = str[i];
    if (index_chr == leftBracket)
      positions_left.push(i);
    else if (index_chr == rightBracket) {
      size_postions_left = positions_left.size();

      positions_right.push(i);

      if (size_postions_left < 1)
        continue;

      if (size_postions_left == layerCount) {
        const int n = positions_right.top() - positions_left.top() - 1;
        ret.emplace_back(str.substr(positions_left.top() + 1, n));
      }

      positions_left.pop();
      positions_right.pop();
    }
  }

  return ret;
}

Coord2d getCoord(int length, int width, double px, double py) {
  Coord2d ret;
  ret.x = static_cast<int>(length * px);
  ret.y = static_cast<int>(width * py);

  return ret;
}
} // namespace AsciiTools
/*#include "at_Basic.h"
#include "at_Tools.h"

namespace AsciiTools {
std::vector<std::string> split(const std::string &str, char chr) {
  if (str == "")
    return std::vector<std::string>();

  std::vector<std::string> ret;
  std::vector<int> pos;
  for (int i = 0; i < str.size(); i++) {
    if (str[i] == chr)
      pos.emplace_back(i);
  }
  pos.insert(pos.begin(), -1);
  pos.insert(pos.end(), (int)str.size());
  for (int i = 0; i < pos.size() - 1; i++) {
    if ((pos[i] + 1) <= (pos[i + 1] - 1)) {
      ret.emplace_back(str.substr(pos[i] + 1, pos[i + 1] - pos[i] - 1));
    }
  }

  return ret;
}

void setWordColor(const AsciiColor &color) {
  printf("\033[38;2;%d;%d;%dm", color.r, color.g, color.b);
}

void setBackgroundColor(const AsciiColor &color) {
  printf("\033[48;2;%d;%d;%dm", color.r, color.g, color.b);
}

void setColor(const AsciiTextColor &color) {
  setWordColor(color.color_text);
  setBackgroundColor(color.color_background);
}

AsciiColor mixAsciiColor(const AsciiColor &color1, const AsciiColor &color2) {
  AsciiColor ret;
  ret.a = (1.0 - ((1.0 - color1.a) * (1.0 - color2.a)));
  ret.r =
      (color1.r * color1.a + color2.r * color2.a * (1.0 - color1.a)) / ret.a;
  ret.g =
      (color1.g * color1.a + color2.g * color2.a * (1.0 - color1.a)) / ret.a;
  ret.b =
      (color1.b * color1.a + color2.b * color2.a * (1.0 - color1.a)) / ret.a;

  return ret;
}

AsciiTextColor mixAsciiTextColor(const AsciiTextColor &color1,
                                 const AsciiTextColor &color2) {
  AsciiTextColor ret;
  ret.color_text = mixAsciiColor(color1.color_text, color2.color_text);
  ret.color_background =
      mixAsciiColor(color1.color_background, color2.color_background);
  return ret;
}

int getStringLineCount(const std::string &str) {
  int ret = static_cast<int>(split(str, '\n').size());
  return ret;
}

std::string interceptString(const std::string &str, int line1, int line2) {
  const auto &tokens = split(str, '\n');
  std::vector<std::string> strBlocks;

  if (line1 <= tokens.size() && line2 <= tokens.size() && line1 > 0 &&
      line2 > 0 && line1 < line2) {
    for (int i = line1 - 1; i < line2; i++) {
      strBlocks.emplace_back(tokens[i]);
    }
  }

  std::string ret;
  for (const auto &index : strBlocks) {
    ret += index + "\n";
  }
  return ret;
}

std::string spliceString(const std::string &str,
                         const std::vector<std::string> &strs) {
  std::string ret;
  for (const auto &index : strs) {
    ret += index;
    if (index != strs[strs.size() - 1]) {
      ret += str;
    }
  }
  return ret;
}

std::vector<std::string> bracketMatch(const std::string &str, int layerCount,
                                      char leftBracket, char rightBracket) {
  std::vector<std::string> ret;
  std::stack<int> positions_left;
  std::stack<int> positions_right;

  if (layerCount <= 0) {
    throw AsciiBasicException(__FUNC__, "layerCount应该大于0!");
  }

  for (int i = 0; i < str.size(); i++) {
    if (str[i] == leftBracket) {
      positions_left.push(i);
    } else if (str[i] == rightBracket) {
      positions_right.push(i);

      if (positions_left.size() < 1) {
        continue;
      }
      if (positions_left.size() == layerCount) {
        const int n = positions_right.top() - positions_left.top() - 1;

        ret.emplace_back(str.substr(positions_left.top() + 1, n));
      }

      positions_left.pop();
      positions_right.pop();
    }
  }

  return ret;
}
} // namespace AsciiTools*/