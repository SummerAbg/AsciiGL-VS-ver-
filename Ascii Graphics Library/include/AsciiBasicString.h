#pragma once

#include "AsciiBasicChar.h"

/*using TrprData = std::vector<bool>;

template <typename CharType> class BasicString : public AsciiBasicObject {
public:
  using DataType = std::vector<CharType>;

  // 构造基本字符串
  BasicString() {}
  BasicString(const char *str, const TrprData &trprData);
  BasicString(const char *str, bool isTrpr = false);
  BasicString(const std::string &str, const TrprData &trprData);
  BasicString(const std::string &str, bool isTrpr = false);
  BasicString(CharType chr);
  // 输出信息
  void info() const;

  // 获取头尾地址的函数(为了能够使用c++11的新特性)
  auto begin() const { return text.begin(); }
  auto end() const { return text.end(); }

  // 基本运算符
  bool operator==(const BasicString<CharType> &str) const;
  bool operator!=(const BasicString<CharType> &str) const;

  BasicString operator+=(const BasicString<CharType> &str);
  BasicString operator+=(CharType chr);
  BasicString operator+(const BasicString<CharType> &str) const;
  BasicString operator+(CharType chr) const;

  CharType &operator[](int index);
  const CharType &operator[](int index) const;

  /////////////////////////////////////////////////////////////

  // 在指定位置插入字符/字符串
  // void insert(int index, const AsciiBasicString &str);
  // void insert(int index, const AsciiBasicChar &chr);

  // 删除字符串指定位置的字符
  void del(int index);
  // 给字符串的末尾添加字符
  void add(CharType chr) { text.push_back(chr); }

  // AsciiBasicString转换为std::string
  std::string toString() const;

  // 获取字符串大小
  int size() const { return text.size(); }

  // 获取透明数据
  TrprData getTrprData() const;

  // 重载输出运算符
  friend std::ostream &operator<<(std::ostream &output,
                                  const BasicString<CharType> &str) {
    for (const auto &index : str) {
      output << index;
    }
    return output;
  }
  // 重载输入运算符
  friend std::istream &operator>>(std::istream &input,
                                  BasicString<CharType> &str) {
    input >> str;
    input.ignore();
    return input;
  }

private:
  std::string getSerializeStr() const;
  void loadSerializeStr(const std::string &str);

private:
  DataType text; // 字符容器
};

using AsciiBasicString = BasicString<AsciiBasicChar>;
using AsciiString = BasicString<AsciiChar>;*/

// 基本字符串类
class AsciiBasicString : public AsciiBasicObject {
public:
  using DataType = std::vector<AsciiBasicChar>;

  // 构造基本字符串
  AsciiBasicString() {}
  AsciiBasicString(const char *str, bool isTrpr = false,
                   const ColorRGB clr = AsciiBasicChar::getDefaultColor());
  AsciiBasicString(const std::string &str, bool isTrpr = false,
                   const ColorRGB clr = AsciiBasicChar::getDefaultColor());
  AsciiBasicString(const char *str, const ColorData &clr, const TrprData &trpr);
  AsciiBasicString(const std::string &str, const ColorData &clr,
                   const TrprData &trpr);
  AsciiBasicString(const AsciiBasicChar &chr);

  // 输出信息
  void info() const;
  // AsciiBasicString转换为std::string
  std::string toString() const;

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

  // 获取字符串大小
  int size() const { return static_cast<int>(text.size()); }

  // 获取透明数据
  TrprData getTrprData() const;
  // 获取颜色数据
  ColorData getColorData() const;

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

/* template <typename CharType>
inline BasicString<CharType>::BasicString(const char *str,
                                          const TrprData &trprData) {
  const std::string text = str;

  for (int i = 0; i < text.size(); i++) {
    const CharType chr = {text[i], trprData[i]};

    this->text.push_back(chr);
  }
}

template <typename CharType>
inline BasicString<CharType>::BasicString(const char *str, bool isTrpr) {
  const std::string text = str;
  const TrprData trprData(text.size(), isTrpr);

  *this = BasicString(str, trprData);
}

template <typename CharType>
inline BasicString<CharType>::BasicString(const std::string &str,
                                          const TrprData &trprData) {
  *this = BasicString(str.c_str(), trprData);
}

template <typename CharType>
inline BasicString<CharType>::BasicString(const std::string &str, bool isTrpr) {
  *this = BasicString(str.c_str(), isTrpr);
}

template <typename CharType>
inline BasicString<CharType>::BasicString(CharType chr) {
  text.push_back(chr);
}

template <typename CharType> inline void BasicString<CharType>::info() const {
  std::cout << "Size:" << text.size() << std::endl;
  std::cout << "trprData:";
  for (const auto &index : text) {
    std::cout << index.isTrpr();
  }
  std::cout << std::endl;
}

template <typename CharType>
inline bool
BasicString<CharType>::operator==(const BasicString<CharType> &str) const {
  if (this->toString() == str.toString() &&
      str.getTrprData() == this->getTrprData())
    return true;
  return false;
}

template <typename CharType>
inline bool
BasicString<CharType>::operator!=(const BasicString<CharType> &str) const {
  return !(*this == str);
}

template <typename CharType>
inline BasicString<CharType>
BasicString<CharType>::operator+=(const BasicString<CharType> &str) {
  return *this = *this + str;
}

template <typename CharType>
inline BasicString<CharType> BasicString<CharType>::operator+=(CharType chr) {
  this->text.push_back(chr);
  return *this;
}

template <typename CharType>
inline BasicString<CharType>
BasicString<CharType>::operator+(const BasicString<CharType> &str) const {
  const std::string text = this->toString() + str.toString();
  const auto pTrprData = str.getTrprData();

  auto trprData = this->getTrprData();
  trprData.insert(trprData.end(), pTrprData.begin(), pTrprData.end());

  const BasicString result(text, trprData);

  return result;
}

template <typename CharType>
inline BasicString<CharType>
BasicString<CharType>::operator+(CharType chr) const {
  BasicString result = *this;
  result.add(chr);
  return result;
}

template <typename CharType>
inline CharType &BasicString<CharType>::operator[](int index) {
  if (index < 0 || index >= text.size()) {
    throw AsciiBasicError("BasicString::operator[]", ArrayOverflow);
  }
  return text[index];
}

template <typename CharType>
inline const CharType &BasicString<CharType>::operator[](int index) const {
  if (index < 0 || index >= text.size()) {
    throw AsciiBasicError("BasicString::operator[] const", ArrayOverflow);
  }
  return text[index];
}

template <typename CharType> inline void BasicString<CharType>::del(int index) {
  if (index < 0 || index >= text.size()) {
    throw AsciiBasicError("BasicString::del()", ArrayOverflow);
  }
  text.erase(text.begin() + index);
}

template <typename CharType>
inline std::string BasicString<CharType>::toString() const {
  std::string result;
  for (const auto &index : text) {
    result += std::string(1, index.getChr());
  }
  return result;
}

template <typename CharType>
inline TrprData BasicString<CharType>::getTrprData() const {
  TrprData result;
  for (const auto &index : text) {
    result.push_back(index.isTrpr());
  }
  return result;
}

template <typename CharType>
inline std::string BasicString<CharType>::getSerializeStr() const {
  std::string result;
  for (const auto &index : text) {
    const auto buffer = serialize(&index);
    result += buffer;
  }
  return result;
}

template <typename CharType>
inline void BasicString<CharType>::loadSerializeStr(const std::string &str) {
  for (int i = 0; i < str.size(); i += 2) {
    CharType chr;
    const std::string data =
        std::string(1, str[i]) + std::string(1, str[i + 1]);
    deserialize(&chr, data);
    this->text.push_back(chr);
  }
}*/

/* template <typename CharType>
std::ostream &operator<<(std::ostream &output,
                         const BasicString<CharType> &str) {
  for (const auto &index : str) {
    output << index;
  }
  return output;
}

template <typename CharType>
std::istream &operator>>(std::istream &input, BasicString<CharType> &str) {
  input >> str;
  input.ignore();
  return input;
}*/

const AsciiBasicString TRPRSTR = {"  ", true, ASCII_WORD_COLOR_BLACK};