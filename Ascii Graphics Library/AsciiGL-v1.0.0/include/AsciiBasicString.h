#pragma once

#include "AsciiBasicChar.h"

// 基本字符串类
class AsciiBasicString : public AsciiBasicObject {
public:
  using TrprData = std::vector<bool>;
  using DataType = std::vector<AsciiBasicChar>;

  // 构造基本字符串
  AsciiBasicString() {}
  AsciiBasicString(const char *str, const TrprData &trprData);
  AsciiBasicString(const char *str, bool isTrpr = false);
  AsciiBasicString(const std::string &str, const TrprData &trprData);
  AsciiBasicString(const std::string &str, bool isTrpr = false);
  AsciiBasicString(const AsciiBasicChar &chr);
  // 输出信息
  void info() const;

  // 获取头尾地址的函数(为了能够使用c++11的新特性)
  auto begin() const { return text.begin(); }
  auto end() const { return text.end(); }

  // 基本运算符
  bool operator==(const AsciiBasicString &str) const;
  bool operator!=(const AsciiBasicString &str) const;

  AsciiBasicString operator+=(const AsciiBasicString &str);
  AsciiBasicString operator+=(const AsciiBasicChar &chr);
  AsciiBasicString operator+(const AsciiBasicString &str) const;
  AsciiBasicString operator+(const AsciiBasicChar &chr) const;

  AsciiBasicChar &operator[](int index);
  const AsciiBasicChar &operator[](int index) const;

  /////////////////////////////////////////////////////////////

  // 在指定位置插入字符/字符串
  // void insert(int index, const AsciiBasicString &str);
  // void insert(int index, const AsciiBasicChar &chr);

  // 删除字符串指定位置的字符
  void del(int index);
  // 给字符串的末尾添加字符
  void add(const AsciiBasicChar &chr) { text.push_back(chr); }

  // AsciiBasicString转换为std::string
  std::string toString() const;

  // 获取字符串大小
  int size() const { return text.size(); }

  // 获取透明数据
  TrprData getTrprData() const;

  // 重载输出运算符
  friend std::ostream &operator<<(std::ostream &output,
                                  const AsciiBasicString &str);
  // 重载输入运算符
  friend std::istream &operator>>(std::istream &input, AsciiBasicString &str);

private:
  std::string getSerializeStr() const;
  void loadSerializeStr(const std::string &str);

private:
  DataType text; // 字符容器
};

const AsciiBasicString TRPRSTR = {"  ", true};