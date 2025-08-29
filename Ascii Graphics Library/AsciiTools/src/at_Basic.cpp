#include "at_basic.h"
#include "at_tools.h"

namespace AsciiTools {
std::vector<std::string> split(const std::string &str, char chr) {
  if (str == "")
    return std::vector<std::string>();

  std::vector<std::string> ret;
  std::vector<int> pos;

  const size_t size_str = str.size();
  for (size_t i = 0; i < size_str; i++) {
    if (str[i] == chr)
      pos.emplace_back(i);
  }

  pos.insert(pos.begin(), -1);
  pos.insert(pos.end(), size_str);

  int pos_a;
  int pos_b;
  const size_t size_pos = pos.size() - 1;
  for (size_t i = 0; i < size_pos; i++) {
    pos_a = pos[i] + 1;
    pos_b = pos[i + 1] - 1;
    if (pos_a <= pos_b)
      ret.emplace_back(str.substr(pos_a, pos_b - pos_a + 1));
  }

  return ret;
}

inline void setWordColor(const AsciiColor &color) {
  printf("\033[38;2;%d;%d;%dm", color.r, color.g, color.b);
  // std::cout << "\033[38;2;" << color.r << ";" << color.g << ";" << color.b
  //           << "m";
}

inline void setBackgroundColor(const AsciiColor &color) {
  printf("\033[48;2;%d;%d;%dm", color.r, color.g, color.b);
  // std::cout << "\033[48;2;" << color.r << ";" << color.g << ";" << color.b
  //           << "m";
}

void setColor(const AsciiTextColor &color) {
  setWordColor(color.color_text);
  setBackgroundColor(color.color_background);
}

void restoreConsoleColor() {
  printf("\033[0m"); /*
std::cout << "\033[0m";
*/
}

inline AsciiTextColor forecolor(int r, int g, int b, double a) {
  return AsciiTextColor({r, g, b, a}, ASCII_ALPHA);
}

inline AsciiTextColor backcolor(int r, int g, int b, double a) {
  return AsciiTextColor(ASCII_ALPHA, {r, g, b, a});
}

AsciiColor mixAsciiColor(const AsciiColor &color1, const AsciiColor &color2) {
  AsciiColor ret;
  ret.a = (1.0 - ((1.0 - color1.a) * (1.0 - color2.a)));
  // 是否将AsciiColor存储的rgb数据类型换为double,以更加精确的数据进行存储，再通过与光栅化相似的逻辑将rgb值应用在int格式上？
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
  return static_cast<int>(split(str, '\n').size());
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
    ret += index;
    ret += "\n";
  }
  return ret;
}

std::string spliceString(const std::string &str,
                         const std::vector<std::string> &strs) {
  std::string ret;
  const size_t index_end = strs.size() - 1;
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
    throw AsciiBasicException("layerCount应该大于0!");

  const size_t size_str = str.size();
  char index_chr;
  int size_postions_left;
  for (int i = 0; i < size_str; i++) {
    index_chr = str[i];
    if (index_chr == leftBracket)
      positions_left.push(i);
    else if (index_chr == rightBracket) {
      size_postions_left = static_cast<int>(positions_left.size());

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

std::string generateLabel(const std::string &prefix, const std::string &link) {
  static std::vector<std::string> label_library;
  static std::vector<int> numbers;

  // 获取指定元素的下标
  const int index = getIndex(label_library, prefix);

  // 当prefix与名字库中的其中一个元素相同时，将与其元素下标相同的numbers元素自加
  if (isExist(label_library, prefix)) {
    numbers[index]++;
  } else {
    // 若名字库里没有与prefix相同的元素，那么添加该元素
    numbers.emplace_back(0);
    numbers.emplace_back(0);
  }
  const auto label = spliceString(link, prefix, numbers[index]);

  label_library.emplace_back(prefix);
  label_library.emplace_back(label);

  return label;
}

AsciiBasicString getAdaptiveStr(const AsciiBasicChar &chr) {
  AsciiBasicString ret;
  const size_t size_trprstr = TRPRSTR.size();
  for (size_t i = 0; i < size_trprstr; i++) {
    ret += chr;
  }
  return ret;
}

AsciiBasicString cutText(const AsciiBasicString &str, int index) {
  AsciiBasicString ret;
  for (int i = 0; i <= index; i++) {
    // ret += str[i];
    ret.append(str[i]);
  }
  return ret;
}

AsciiBasicString overlapText(const AsciiBasicString &str_a,
                             const AsciiBasicString &str_b, int position,
                             bool is_limit) {
  AsciiBasicString ret = str_a;

  const size_t size_a = str_a.size();
  const size_t size_b = str_b.size();

  const size_t size_str = is_limit ? size_a : size_b;

  int index;
  int size_ret;
  for (size_t i = 0; i < size_str; i++) {
    index = i + position;
    size_ret = static_cast<int>(ret.size());

    if (index < size_ret && i < size_b)
      ret[index] = str_b[i];
    else if (index >= size_ret && i < size_b)
      // ret += str_b[i];
      ret.append(str_b[i]);
  }

  return ret;
}
} // namespace AsciiTools