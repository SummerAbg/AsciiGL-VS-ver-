#include "at_tools.h"

namespace AsciiTools {
AsciiBasicString::AsciiBasicString() { this->text = std::make_unique<Text>(); }

/************************/
AsciiBasicString::AsciiBasicString(const char *str, bool trprState,
                                   const AsciiTextColor clr)
    : AsciiBasicString(str, AsciiTextColorData(strlen(str), clr),
                       AsciiTrprData(strlen(str), trprState)) {
  /* const int size_str = strlen(str);
  const AsciiTrprData trpr(size_str, trprState);
  const AsciiTextColorData color(size_str, clr);

  *this = std::move(AsciiBasicString(str, color, trpr));*/
}

AsciiBasicString::AsciiBasicString(const std::string &str, bool trprState,
                                   const AsciiTextColor clr)
    : AsciiBasicString(str.c_str(), trprState, clr) {
  //*this = std::move(AsciiBasicString(str.c_str(), trprState, clr));
}

AsciiBasicString::AsciiBasicString(const char *str,
                                   const AsciiTextColorData &clr,
                                   const AsciiTrprData &trpr)
    : AsciiBasicString() {
  const size_t size = strlen(str);
  for (size_t i = 0; i < size; i++) {
    this->text->emplace_back(str[i], clr[i], trpr[i]);
    // this->text->push_back(
    //     std::make_shared<AsciiBasicChar>(str[i], clr[i], trpr[i]));
  }
}

AsciiBasicString::AsciiBasicString(const std::string &str,
                                   const AsciiTextColorData &clr,
                                   const AsciiTrprData &trpr)
    : AsciiBasicString(str.c_str(), clr, trpr) {
  // this->text->push_back(
  //     std::make_shared<AsciiBasicChar>(str[i], clr[i], trpr[i]));
}

AsciiBasicString::AsciiBasicString(const AsciiBasicChar &chr)
    : AsciiBasicString() {
  // this->text = std::make_unique<Text>();
  this->text->push_back(chr);
  // this->text->push_back(std::make_shared<AsciiBasicChar>(chr));
}

AsciiBasicString::AsciiBasicString(const AsciiBasicString &str) {
  this->text = std::make_unique<Text>(*str.text);
}

AsciiBasicString::AsciiBasicString(AsciiBasicString &&str) noexcept {
  this->text = std::move(str.text);
  str.text = nullptr;
}

AsciiBasicString::AsciiBasicString(const std::string &str,
                                   const AsciiTextColor clr)
    : AsciiBasicString(str, false, clr) {}

void AsciiBasicString::info() const noexcept {
  std::cout << "AsciiBasicString对象" << std::endl;
  std::cout << "size:" << text->size() << std::endl;
  std::cout << "trprData:";
  for (const auto &index : *text) {
    // std::cout << index->isTrpr();
    std::cout << index.isTrpr();
  }
  std::cout << std::endl;
  std::cout << "colorData:";
  for (const auto &index : *text) {
    // std::cout << index->getColor() << "^^^";
    std::cout << index.getColor() << "^^^";
  }
  std::cout << std::endl;
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
    throw AsciiBasicException(ArrayOverflow);

  // return *(*text)[index];
  return (*text)[index];
}

const AsciiBasicChar &AsciiBasicString::operator[](int index) const {
  if (index < 0 || index >= text->size())
    throw AsciiBasicException(ArrayOverflow);

  // return *(*text)[index];
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

void AsciiBasicString::remove(int index) {
  if (index < 0 || index >= text->size())
    throw AsciiBasicException(ArrayOverflow);

  text->erase(text->begin() + index);
}

void AsciiBasicString::append(const AsciiBasicString &str) {
  this->text->insert(this->text->end(), str.text->begin(), str.text->end());
}

void AsciiBasicString::append(const AsciiBasicChar &chr) {
  // text->push_back(std::make_shared<AsciiBasicChar>(chr));
  text->push_back(chr);
}

/*void AsciiBasicString::append(AsciiBasicChar &&chr) noexcept {
  text->emplace_back(std::move(chr));
  // text->push_back(std::make_shared<AsciiBasicChar>(std::move(chr)));
}*/

void AsciiBasicString::append(AsciiBasicString &&str) noexcept {
  this->text->insert(this->text->end(), str.text->begin(), str.text->end());

  str.text = nullptr;
}

void AsciiBasicString::clear() {
  this->text->clear();
  // 有必要吗？感觉会造成一定开销。（难怪使用setText函数会慢很多，可能是这个造成的）
  this->text->shrink_to_fit();
}

std::string AsciiBasicString::toString() const noexcept {
  std::string ret;
  for (const auto &index : *text) {
    // ret += index->toString();
    ret += index.toString();
  }
  return ret;
}

AsciiTrprData AsciiBasicString::getTrprData() const {
  AsciiTrprData ret;
  for (const auto &index : *text) {
    // ret.emplace_back(index->isTrpr());
    ret.emplace_back(index.isTrpr());
  }
  return ret;
}

AsciiTextColorData AsciiBasicString::getTextColorData() const {
  AsciiTextColorData ret;
  for (const auto &index : *text) {
    // ret.emplace_back(index->getColor());
    ret.emplace_back(index.getColor());
  }
  return ret;
}

std::string AsciiBasicString::getSerializeStr() const {
  std::string ret;
  for (const auto &index : *text) {
    ret += serializeType(index);
    // ret += serializeType(*index);
  }
  return ret;
}

void AsciiBasicString::loadSerializeStr(const std::string &str) {
  const auto tokens = bracketMatch(str);

  AsciiBasicChar chr;
  for (const auto &index : tokens) {
    deserializeType(chr, index);
    // this->text->push_back(std::make_shared<AsciiBasicChar>(chr));
    this->text->emplace_back(chr);
  }
}

std::ostream &operator<<(std::ostream &output, const AsciiBasicString &str) {
  for (const auto &chr : str) {
    output << chr;
    // output << *chr;
  }
  output << AsciiBasicChar('\0', AsciiBasicChar::getDefaultColor());
  return output;
}

std::istream &operator>>(std::istream &input, AsciiBasicString &str) {
  input >> str;
  input.ignore();
  return input;
}
} // namespace AsciiTools