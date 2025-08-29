#pragma once

#include <iostream>
#include <stack>
#include <string>
#include <vector>

#ifdef _WIN64
#define __FUNC__ __FUNCSIG__
#else
#define __FUNC__ __PRETTY_FUNCTION__
#endif

namespace AsciiTools {
template <typename Type> struct Coordinate2d;
struct AsciiColor;
struct AsciiTextColor;

typedef Coordinate2d<int> Vec2d;
typedef Coordinate2d<int> Coord2d;

template <typename Type> using Coord = Coordinate2d<Type>;
using Point2D = Coord2d;                                // 二维点坐标
using AsciiTrprData = std::vector<bool>;                // 透明数据
using AsciiColorData = std::vector<AsciiColor>;         // 颜色数据
using AsciiTextColorData = std::vector<AsciiTextColor>; // 文本颜色数据

class AsciiBasicObject;
class AsciiBasicChar;
class AsciiBasicString;

using AsciiObject = std::shared_ptr<AsciiBasicObject>;
using AsciiChar = std::shared_ptr<AsciiBasicChar>;
using AsciiString = std::shared_ptr<AsciiBasicString>;
template <typename ElementType> using AsciiType = std::shared_ptr<ElementType>;

const std::string LABEL_ENTITY_DEFAULT = "untitled_entity";

// 分割字符串
std::vector<std::string> split(const std::string &str, char chr);

template <typename T> std::string serializeType(const T &arg);
template <typename T, typename... Args>
std::string serializeType(const T &arg, const Args &...args);
template <typename T> void deserializeType(T &obj, const std::string &str);

// 设置字体颜色
void setWordColor(const AsciiColor &color);
// 设置背景颜色
void setBackgroundColor(const AsciiColor &color);
// 设置颜色(word,background)
void setColor(const AsciiTextColor &color);
// 还原控制台所有ANSI颜色
void restoreConsoleColor();

AsciiTextColor forecolor(int r, int g, int b, double a = 1.0);
AsciiTextColor backcolor(int r, int g, int b, double a = 1.0);

// 混合两个颜色(color1占主导地位)
AsciiColor mixAsciiColor(const AsciiColor &color1, const AsciiColor &color2);
AsciiTextColor mixAsciiTextColor(const AsciiTextColor &color1,
                                 const AsciiTextColor &color2);

// 获取字符串行数
int getStringLineCount(const std::string &str);
// 按行截取字符串(line1-line2)
std::string interceptString(const std::string &str, int line1, int line2);
// 拼接字符串
std::string spliceString(const std::string &str,
                         const std::vector<std::string> &strs);

// 括号匹配
std::vector<std::string> bracketMatch(const std::string &str,
                                      int layerCount = 1,
                                      char leftBracket = '[',
                                      char rightBracket = ']');

// 按比例根据长宽获取新坐标
Coord2d getCoord(int length, int width, double px, double py);

/**
 *  @brief  获取名字/取名器(随着名字重复而添加编号)
 *  @brief  请谨慎使用，若在死循环中一直调用这个函数，会导致程序运行效率逐渐低下
 *  @param  prefix - 字符串前缀
 *  @param  link - 字符串连接符
 *  @retval        - 自动处理过的标识符/名字
 */
std::string generateLabel(const std::string &prefix,
                          const std::string &link = "_");

/**
 *  @brief  获取容器指定元素的下标(成功了返回元素下标，失败了返回0)
 *  @tparam T       - 指定元素类型
 *  @param  vec     - vector容器
 *  @param  element - 指定元素
 *  @retval         - 指定元素的下标
 */
template <typename T> int getIndex(const std::vector<T> &vec, const T &element);

/**
 *  @brief  判断容器是否存在指定元素
 *  @tparam T       - 指定元素类型
 *  @param  vec     - vector容器
 *  @param  element - 指定元素
 *  @retval         - 是否存在该元素的布尔值
 */
template <typename T> bool isExist(const std::vector<T> &vec, const T &element);

// 获取自适应字符串
AsciiBasicString getAdaptiveStr(const AsciiBasicChar &chr);

// 剪裁字符串(获取index位置及之前的字符串)
AsciiBasicString cutText(const AsciiBasicString &str, int index);

// 重叠字符串
// 将strB重叠在strA的position的位置上
// 当isLimit为true时，得到的字符串大小以strA为标准
// 如:
//    ①当strA的长度大于strB的长度且处于非限定模式下:
//      "egg"重叠在"apple"的0位置上，得到"eggle"
//    ②当strA的长度小于strB的长度且处于非限定模式下:
//      "apple"重叠在"egg"的0位置上，得到"apple"
//    ③当strA的长度小于strB的长度且处于限定模式下:
//      "apple"重叠在"egg"的0位置上，得到"app"
AsciiBasicString overlapText(const AsciiBasicString &str_a,
                             const AsciiBasicString &str_b, int psotion = 0,
                             bool is_limit = false);

// 平均分配容器中的元素至若干个新容器中
template <typename T>
std::vector<std::vector<T>> equalDivision(int count,
                                          const std::vector<T> &vec) {
  std::vector<std::vector<T>> ret;

  const int numElement = vec.size() / count;
  bool isPerfectDivision = (vec.size() % count == 0);

  std::vector<T> temp;
  int size;

  for (int i = 0; i < count; i++) {
    if (i < count - 1 || isPerfectDivision)
      size = numElement;
    else
      size = vec.size() - numElement * (count - 1);

    for (int j = 0; j < size; j++) {
      temp.emplace_back(vec[i * numElement + j]);
    }
    ret.emplace_back(temp);
  }
  return ret;
}

template <typename T>
inline int getIndex(const std::vector<T> &vec, const T &element) {
  const size_t size = vec.size();
  for (size_t i = 0; i < size; i++) {
    if (vec[i] == element)
      return i;
  }
  return 0;
}

template <typename T>
inline bool isExist(const std::vector<T> &vec, const T &element) {
  for (const auto &index : vec) {
    if (index == element)
      return true;
  }
  return false;
}
} // namespace AsciiTools