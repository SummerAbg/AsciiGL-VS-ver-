#pragma once

#include "at_char.h"
#include "at_vector.h"

namespace AsciiTools {
// 基本字符串类
class AsciiBasicString : public AsciiBasicObject {
public:
  using Text = std::vector<AsciiBasicChar>;
  // using Text = Vector<AsciiChar>;
  using pText = std::unique_ptr<Text>;

  // 构造基本字符串
  AsciiBasicString();
  AsciiBasicString(const char *str, const AsciiTextColorData &clr,
                   const AsciiTrprData &trpr);
  AsciiBasicString(const std::string &str, const AsciiTextColorData &clr,
                   const AsciiTrprData &trpr);
  AsciiBasicString(
      const char *str, bool isTrpr = false,
      const AsciiTextColor clr = AsciiBasicChar::getDefaultColor());
  AsciiBasicString(
      const std::string &str, bool isTrpr = false,
      const AsciiTextColor clr = AsciiBasicChar::getDefaultColor());
  AsciiBasicString(const AsciiBasicChar &chr);
  AsciiBasicString(const AsciiBasicString &str);
  AsciiBasicString(AsciiBasicString &&str) noexcept;

  AsciiBasicString(const std::string &str, const AsciiTextColor clr);

  // 输出信息
  void info() const noexcept override;
  // AsciiBasicString转换为std::string
  std::string toString() const noexcept override;

  // 获取头尾地址的函数(为了能够使用c++11的新特性)
  auto begin() const noexcept { return text->begin(); }
  auto end() const noexcept { return text->end(); }

  // 基本运算符
  bool operator==(const AsciiBasicString &str) const noexcept {
    return *this->text == *str.text;
  }

  bool operator!=(const AsciiBasicString &str) const noexcept {
    return !(*this == str);
  }

  AsciiBasicString &operator+=(const AsciiBasicString &str);
  AsciiBasicString &operator+=(AsciiBasicString &&str) noexcept;

  AsciiBasicString &operator+=(const AsciiBasicChar &chr);

  AsciiBasicString operator+(const AsciiBasicString &str) const;
  AsciiBasicString operator+(const AsciiBasicChar &chr) const;

  AsciiBasicChar &operator[](int index);
  const AsciiBasicChar &operator[](int index) const;

  AsciiBasicString &operator=(const AsciiBasicString &str);
  AsciiBasicString &operator=(AsciiBasicString &&str) noexcept;

  /////////////////////////////////////////////////////////////

  // 在指定位置插入字符/字符串
  // void insert(int index, const AsciiBasicString &str);
  // void insert(int index, const AsciiBasicChar &chr);

  // 删除字符串指定位置的字符
  void remove(int index);
  // 给字符串的末尾添加字符
  void append(const AsciiBasicChar &chr);
  // void append(AsciiBasicChar &&chr) noexcept;

  void append(const AsciiBasicString &str);
  void append(AsciiBasicString &&str) noexcept;

  // 清空字符串
  void clear();

  // 获取字符串大小
  size_t size() const noexcept { return text->size(); }

  // 获取透明数据
  AsciiTrprData getTrprData() const;
  // 获取颜色数据
  AsciiTextColorData getTextColorData() const;

  // 重载输出运算符
  friend std::ostream &operator<<(std::ostream &output,
                                  const AsciiBasicString &str);
  // 重载输入运算符
  friend std::istream &operator>>(std::istream &input, AsciiBasicString &str);

private:
  std::string getSerializeStr() const override;
  void loadSerializeStr(const std::string &str) override;

private:
  pText text; // 字符容器
};

const AsciiBasicString TRPRSTR = {
    "  ", true, {ASCII_COLOR_GREY, ASCII_COLOR_BLACK}};
} // namespace AsciiTools