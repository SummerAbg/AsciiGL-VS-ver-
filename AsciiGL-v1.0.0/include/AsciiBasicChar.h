#pragma once

#include "AsciiBasicObject.h"

// 基本字符类
class AsciiBasicChar : public AsciiBasicObject {
public:
  // 构造基本字符
  AsciiBasicChar();
  AsciiBasicChar(char chr, bool isTrpr = false)
      : character(chr), m_isTrpr(isTrpr) {}

  // 输出信息
  void info() const;

  friend std::ostream &operator<<(std::ostream &output,
                                  const AsciiBasicChar &chr);

  friend std::istream &operator>>(std::istream &input, AsciiBasicChar &chr);

  // 设置透明字符
  static void setTrprChr(char chr);
  // 获取透明字符
  static char getTrprChr();

  // 获取字符
  char getChr() const { return character; }
  // 设置字符
  void setChr(char chr) { character = chr; }
  // 获取透明状态
  bool isTrpr() const { return m_isTrpr; }
  // 设置透明
  void setTrpr(bool isTrpr) { m_isTrpr = isTrpr; }

private:
  std::string getSerializeStr() const;
  void loadSerializeStr(const std::string &str);

private:
  char character;
  bool m_isTrpr;
  static char trprChr; // 透明字符(透明时填充的字符)
};