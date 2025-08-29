#pragma once

#include "at_basic.h"
#include "at_basicobject.h"
#include "at_textcolor.h"

namespace AsciiTools {
// 基本字符类
class AsciiBasicChar : public AsciiBasicObject {
public:
  // 构造基本字符
  AsciiBasicChar();
  AsciiBasicChar(char chr, bool trprState = false)
      : character(chr), color(getDefaultColor()), trprState(trprState) {}
  AsciiBasicChar(char chr, AsciiTextColor clr, bool trprState = false)
      : character(chr), color(clr), trprState(trprState) {}

  // 输出信息
  void info() const override;
  // AsciiBasicChar转换为std::string
  std::string toString() const override;

  bool operator==(const AsciiBasicChar &chr) const noexcept;
  bool operator!=(const AsciiBasicChar &chr) const noexcept;

  friend std::ostream &operator<<(std::ostream &output,
                                  const AsciiBasicChar &chr);

  friend std::istream &operator>>(std::istream &input, AsciiBasicChar &chr);

  // 设置透明字符
  static void setTrprChr(char chr) noexcept;
  // 获取透明字符
  static char getTrprChr() noexcept;
  // 设置默认颜色
  static void setDefaultColor(const AsciiTextColor &clr) noexcept;
  // 获取默认颜色
  static AsciiTextColor getDefaultColor() noexcept;

  // 获取字符
  char getChr() const noexcept { return character; }
  // 设置字符
  void setChr(char chr) noexcept { character = chr; }
  // 获取透明状态
  bool isTrpr() const noexcept { return trprState; }
  // 设置透明
  void setTrpr(bool trprState) noexcept { this->trprState = trprState; }
  // 获取颜色
  AsciiTextColor getColor() const noexcept { return color; }
  // 设置颜色
  void setColor(const AsciiTextColor &clr) noexcept { color = clr; }

private:
  std::string getSerializeStr() const override;
  void loadSerializeStr(const std::string &str) override;

private:
  char character;       // 字符
  bool trprState;       // 透明状态
  AsciiTextColor color; // 颜色

  static char trprChr;               // 透明字符(透明时填充的字符)
  static AsciiTextColor default_clr; // 默认颜色
};
} // namespace AsciiTools