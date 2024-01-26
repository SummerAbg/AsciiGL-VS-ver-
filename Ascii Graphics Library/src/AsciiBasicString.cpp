#include "AsciiBasicString.h"

AsciiBasicString::AsciiBasicString(const char *str, bool isTrpr,
                                   const ColorRGB clr) {
  const std::string text = str;
  const TrprData trpr(text.size(), isTrpr);
  const ColorData color(text.size(), clr);

  *this = AsciiBasicString(str, color, trpr);
}

AsciiBasicString::AsciiBasicString(const std::string &str, bool isTrpr,
                                   const ColorRGB clr) {
  *this = AsciiBasicString(str.c_str(), isTrpr, clr);
}

AsciiBasicString::AsciiBasicString(const char *str, const ColorData &clr,
                                   const TrprData &trpr) {
  const std::string text = str;

  for (int i = 0; i < text.size(); i++) {
    const AsciiBasicChar chr = {text[i], clr[i], trpr[i]};

    this->text.push_back(chr);
  }
}

AsciiBasicString::AsciiBasicString(const std::string &str, const ColorData &clr,
                                   const TrprData &trpr) {
  *this = AsciiBasicString(str.c_str(), clr, trpr);
}

AsciiBasicString::AsciiBasicString(const AsciiBasicChar &chr) {
  text.push_back(chr);
}

void AsciiBasicString::info() const {
  std::cout << "Size:" << text.size() << std::endl;
  std::cout << "trprData:";
  for (const auto &index : text) {
    std::cout << index.isTrpr();
  }
  std::cout << std::endl;
}

bool AsciiBasicString::operator==(const AsciiBasicString &str) const {
  if (this->toString() == str.toString() &&
      this->getTrprData() == str.getTrprData() &&
      this->getColorData() == str.getColorData())
    return true;
  return false;
}

bool AsciiBasicString::operator!=(const AsciiBasicString &str) const {
  return !(*this == str);
}

AsciiBasicString AsciiBasicString::operator+=(const AsciiBasicString &str) {
  return *this = *this + str;
}

AsciiBasicString AsciiBasicString::operator+=(const AsciiBasicChar &chr) {
  this->text.push_back(chr);
  return *this;
}

AsciiBasicString
AsciiBasicString::operator+(const AsciiBasicString &str) const {
  const std::string text = this->toString() + str.toString();
  const TrprData obj_Trpr = str.getTrprData();
  const ColorData obj_clr = str.getColorData();

  TrprData trpr = this->getTrprData();
  ColorData color = this->getColorData();

  trpr.insert(trpr.end(), obj_Trpr.begin(), obj_Trpr.end());
  color.insert(color.end(), obj_clr.begin(), obj_clr.end());

  const AsciiBasicString result(text, color, trpr);

  return result;
}

AsciiBasicString AsciiBasicString::operator+(const AsciiBasicChar &chr) const {
  AsciiBasicString result = *this;
  result.add(chr);
  return result;
}

AsciiBasicChar &AsciiBasicString::operator[](int index) {
  if (index < 0 || index >= text.size()) {
    throw AsciiBasicError(__FUNC__, ArrayOverflow);
  }
  return text[index];
}

const AsciiBasicChar &AsciiBasicString::operator[](int index) const {
  if (index < 0 || index >= text.size()) {
    throw AsciiBasicError(__FUNC__, ArrayOverflow);
  }
  return text[index];
}

void AsciiBasicString::del(int index) {
  if (index < 0 || index >= text.size()) {
    throw AsciiBasicError(__FUNC__, ArrayOverflow);
  }
  text.erase(text.begin() + index);
}

std::string AsciiBasicString::toString() const {
  std::string result;
  for (const auto &index : text) {
    result += index.toString();
  }
  return result;
}

TrprData AsciiBasicString::getTrprData() const {
  TrprData result;
  for (const auto &index : text) {
    result.push_back(index.isTrpr());
  }
  return result;
}

ColorData AsciiBasicString::getColorData() const {
  ColorData result;
  for (const auto &index : text) {
    result.push_back(index.getColor());
  }
  return result;
}

std::string AsciiBasicString::getSerializeStr() const {
  std::string result;
  for (const auto &index : text) {
    result += serialize(&index) + ";";
  }
  return result;
}

void AsciiBasicString::loadSerializeStr(const std::string &str) {
  const auto tokens = split(str, ';');

  for (int i = 0; i < tokens.size(); i += 2) {
    AsciiBasicChar chr;
    const std::string chr_data = tokens[i] + ";" + tokens[i + 1];
    deserialize(&chr, chr_data);
    this->text.push_back(chr);
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