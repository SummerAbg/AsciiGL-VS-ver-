#pragma once

#include "AsciiBasicObject.h"

// 基本字符类
class AsciiBasicChar : public AsciiBasicObject {
public:
  // 构造基本字符
  AsciiBasicChar();
  AsciiBasicChar(char chr, bool isTrpr = false)
      : character(chr), colorVal(getDefaultColor()), m_isTrpr(isTrpr) {}
  AsciiBasicChar(char chr, ColorRGB clr, bool isTrpr = false)
      : character(chr), colorVal(clr), m_isTrpr(isTrpr) {}

  // 输出信息
  void info() const;
  // AsciiBasicChar转换为std::string
  std::string toString() const;

  bool operator==(const AsciiBasicChar &chr) const;
  bool operator!=(const AsciiBasicChar &chr) const;

  friend std::ostream &operator<<(std::ostream &output,
                                  const AsciiBasicChar &chr);

  friend std::istream &operator>>(std::istream &input, AsciiBasicChar &chr);

  // 设置透明字符
  static void setTrprChr(char chr);
  // 获取透明字符
  static char getTrprChr();
  // 设置默认颜色
  static void setDefaultColor(ColorRGB clr);
  // 获取默认颜色
  static ColorRGB getDefaultColor();

  // 获取字符
  char getChr() const { return character; }
  // 设置字符
  void setChr(char chr) { character = chr; }
  // 获取透明状态
  bool isTrpr() const { return m_isTrpr; }
  // 设置透明
  void setTrpr(bool isTrpr) { m_isTrpr = isTrpr; }
  // 获取颜色值
  ColorRGB getColor() const { return colorVal; }
  // 设置颜色值
  void setColor(ColorRGB clr) { colorVal = clr; }

private:
  std::string getSerializeStr() const;
  void loadSerializeStr(const std::string &str);

private:
  char character;    // 字符
  bool m_isTrpr;     // 是否透明
  ColorRGB colorVal; // 颜色值

  static char trprChr;         // 透明字符(透明时填充的字符)
  static ColorRGB default_clr; // 默认颜色
};

// 字符类
/* class AsciiChar : public AsciiBasicChar {
public:
  using Color16 = unsigned short;

  AsciiChar() : AsciiBasicChar() { colorVal = 0; }
  AsciiChar(char chr, bool isTrpr, Color16 colorVal)
      : AsciiBasicChar(chr, isTrpr) {
    this->colorVal = colorVal;
  };

  // 获取颜色值
  Color16 getColor() const { return colorVal; }
  // 设置颜色值
  void setColor(Color16 colorVal) { this->colorVal = colorVal; }

private:
  Color16 colorVal;
};*/