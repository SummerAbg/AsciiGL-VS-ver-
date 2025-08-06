#include "at_Tools.h"

namespace AsciiTools {
AsciiBasicString::AsciiBasicString() { this->text = std::make_unique<Text>(); }

AsciiBasicString::AsciiBasicString(const char *str, bool trprState,
                                   const AsciiTextColor clr) {
  const int size_str = strlen(str);
  const AsciiTrprData trpr(size_str, trprState);
  const AsciiTextColorData color(size_str, clr);

  *this = std::move(AsciiBasicString(str, color, trpr));
}

AsciiBasicString::AsciiBasicString(const std::string &str, bool trprState,
                                   const AsciiTextColor clr) {
  *this = std::move(AsciiBasicString(str.c_str(), trprState, clr));
}

AsciiBasicString::AsciiBasicString(const char *str,
                                   const AsciiTextColorData &clr,
                                   const AsciiTrprData &trpr) {
  this->text = std::make_unique<Text>();

  const int size = strlen(str);
  for (int i = 0; i < size; i++) {
    this->text->emplace_back(str[i], clr[i], trpr[i]);
  }
}

AsciiBasicString::AsciiBasicString(const std::string &str,
                                   const AsciiTextColorData &clr,
                                   const AsciiTrprData &trpr) {
  *this = std::move(AsciiBasicString(str.c_str(), clr, trpr));
}

AsciiBasicString::AsciiBasicString(const AsciiBasicChar &chr) {
  this->text = std::make_unique<Text>();
  this->text->push_back(chr);
}

AsciiBasicString::AsciiBasicString(const AsciiBasicString &str) {
  this->text = std::make_unique<Text>(*str.text);
}

AsciiBasicString::AsciiBasicString(AsciiBasicString &&str) noexcept {
  this->text = std::move(str.text);
  str.text = nullptr;
}

void AsciiBasicString::info() const {
  std::cout << "AsciiBasicString¶ÔÏó" << std::endl;
  std::cout << "size:" << text->size() << std::endl;
  std::cout << "trprData:";
  for (const auto &index : *text) {
    std::cout << index.isTrpr();
  }
  std::cout << std::endl;
  std::cout << "colorData:";
  for (const auto &index : *text) {
    std::cout << index.getColor() << "^^^";
  }
  std::cout << std::endl;
}

bool AsciiBasicString::operator==(const AsciiBasicString &str) const {
  return *this->text == *str.text ? true : false;
}

bool AsciiBasicString::operator!=(const AsciiBasicString &str) const {
  return !(*this == str);
}

AsciiBasicString &AsciiBasicString::operator+=(const AsciiBasicString &str) {
  append(str);

  return *this;
}

AsciiBasicString &
AsciiBasicString::operator+=(AsciiBasicString &&str) noexcept {
  append(std::move(str));

  return *this;
}

AsciiBasicString &AsciiBasicString::operator+=(const AsciiBasicChar &chr) {
  append(chr);

  return *this;
}

AsciiBasicString
AsciiBasicString::operator+(const AsciiBasicString &str) const {
  AsciiBasicString ret;

  ret.text->insert(ret.text->end(), this->text->begin(), this->text->end());
  ret.text->insert(ret.text->end(), str.text->begin(), str.text->end());

  return ret;
}

AsciiBasicString AsciiBasicString::operator+(const AsciiBasicChar &chr) const {
  AsciiBasicString ret = *this;
  ret.append(chr);

  return ret;
}

AsciiBasicChar &AsciiBasicString::operator[](int index) {
  if (index < 0 || index >= text->size())
    throw AsciiBasicException(__FUNC__, ArrayOverflow);

  return (*text)[index];
}

const AsciiBasicChar &AsciiBasicString::operator[](int index) const {
  if (index < 0 || index >= text->size())
    throw AsciiBasicException(__FUNC__, ArrayOverflow);

  return (*text)[index];
}

AsciiBasicString &AsciiBasicString::operator=(const AsciiBasicString &str) {
  *text = *str.text;

  return *this;
}

AsciiBasicString &AsciiBasicString::operator=(AsciiBasicString &&str) noexcept {
  this->text = std::move(str.text);
  str.text = nullptr;

  return *this;
}

void AsciiBasicString::del(int index) {
  if (index < 0 || index >= text->size())
    throw AsciiBasicException(__FUNC__, ArrayOverflow);

  text->erase(text->begin() + index);
}

void AsciiBasicString::append(const AsciiBasicString &str) {
  this->text->insert(this->text->end(), str.text->begin(), str.text->end());
}

void AsciiBasicString::append(const AsciiBasicChar &chr) {
  text->push_back(chr);
}

void AsciiBasicString::append(AsciiBasicChar &&chr) noexcept {
  text->emplace_back(std::move(chr));
}

void AsciiBasicString::append(AsciiBasicString &&str) noexcept {
  this->text->insert(this->text->end(), str.text->begin(), str.text->end());

  str.text = nullptr;
}

void AsciiBasicString::clear() {
  text->clear();
  text->shrink_to_fit();
}

std::string AsciiBasicString::toString() const {
  std::string ret;
  for (const auto &index : *text) {
    ret += index.toString();
  }
  return ret;
}

AsciiTrprData AsciiBasicString::getTrprData() const {
  AsciiTrprData ret;
  for (const auto &index : *text) {
    ret.emplace_back(index.isTrpr());
  }
  return ret;
}

AsciiTextColorData AsciiBasicString::getTextColorData() const {
  AsciiTextColorData ret;
  for (const auto &index : *text) {
    ret.emplace_back(index.getColor());
  }
  return ret;
}

std::string AsciiBasicString::getSerializeStr() const {
  std::string ret;
  for (const auto &index : *text) {
    ret += serializeType(index);
  }
  return ret;
}

void AsciiBasicString::loadSerializeStr(const std::string &str) {
  const auto tokens = bracketMatch(str);

  AsciiBasicChar chr;
  for (const auto &index : tokens) {
    deserializeType(chr, index);
    this->text->push_back(chr);
  }
}

std::ostream &operator<<(std::ostream &output, const AsciiBasicString &str) {
  for (const auto &chr : str) {
    output << chr;
  }
  output << AsciiBasicChar('\0', AsciiBasicChar::getDefaultColor());
  return output;
}

std::istream &operator>>(std::istream &input, AsciiBasicString &str) {
  input >> str;
  input.ignore();
  return input;
}

AsciiBasicString getAdaptiveStr(const AsciiBasicChar &chr) {
  AsciiBasicString ret;
  const int size_trprstr = TRPRSTR.size();
  for (int i = 0; i < size_trprstr; i++) {
    ret += chr;
  }
  return ret;
}

AsciiBasicString cutText(const AsciiBasicString &str, int index) {
  AsciiBasicString ret;
  for (int i = 0; i <= index; i++) {
    ret += str[i];
  }
  return ret;
}

AsciiBasicString overlapText(const AsciiBasicString &str_a,
                             const AsciiBasicString &str_b, int position,
                             bool is_limit) {
  AsciiBasicString ret = str_a;

  const int size_a = str_a.size();
  const int size_b = str_b.size();

  const int size_str = is_limit ? size_a : size_b;

  int index;
  int size_ret;
  for (int i = 0; i < size_str; i++) {
    index = i + position;
    size_ret = ret.size();

    if (index < size_ret && i < size_b)
      ret[index] = str_b[i];
    else if (index >= size_ret && i < size_b)
      ret += str_b[i];
  }

  return ret;
}
} // namespace AsciiTools