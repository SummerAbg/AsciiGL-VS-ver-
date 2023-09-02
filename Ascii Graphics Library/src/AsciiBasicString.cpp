#include "AsciiBasicString.h"

AsciiBasicString::AsciiBasicString(const char *str, const TrprData &trprData) {
  const std::string text = str;

  for (int i = 0; i < text.size(); i++) {
    const AsciiBasicChar chr = {text[i], trprData[i]};

    this->text.push_back(chr);
  }
}

AsciiBasicString::AsciiBasicString(const char *str, bool isTrpr) {
  const std::string text = str;
  const TrprData trprData(text.size(), isTrpr);

  *this = AsciiBasicString(str, trprData);
}

AsciiBasicString::AsciiBasicString(const std::string &str,
                                   const TrprData &trprData) {
  *this = AsciiBasicString(str.c_str(), trprData);
}

AsciiBasicString::AsciiBasicString(const std::string &str, bool isTrpr) {
  *this = AsciiBasicString(str.c_str(), isTrpr);
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
      str.getTrprData() == this->getTrprData())
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
  const auto pTrprData = str.getTrprData();

  auto trprData = this->getTrprData();
  trprData.insert(trprData.end(), pTrprData.begin(), pTrprData.end());

  const AsciiBasicString result(text, trprData);

  return result;
}

AsciiBasicString AsciiBasicString::operator+(const AsciiBasicChar &chr) const {
  AsciiBasicString result = *this;
  result.add(chr);
  return result;
}

AsciiBasicChar &AsciiBasicString::operator[](int index) {
  if (index < 0 || index >= text.size()) {
    throw AsciiBasicError("AsciiBasicString::operator[]", ArrayOverflow);
  }
  return text[index];
}

const AsciiBasicChar &AsciiBasicString::operator[](int index) const {
  if (index < 0 || index >= text.size()) {
    throw AsciiBasicError("AsciiBasicString::operator[] const", ArrayOverflow);
  }
  return text[index];
}

void AsciiBasicString::del(int index) {
  if (index < 0 || index >= text.size()) {
    throw AsciiBasicError("AsciiBasicString::del()", ArrayOverflow);
  }
  text.erase(text.begin() + index);
}

std::string AsciiBasicString::toString() const {
  std::string result;
  for (const auto &index : text) {
    result += std::string(1, index.getChr());
  }
  return result;
}

AsciiBasicString::TrprData AsciiBasicString::getTrprData() const {
  TrprData result;
  for (const auto &index : text) {
    result.push_back(index.isTrpr());
  }
  return result;
}

std::string AsciiBasicString::getSerializeStr() const {
  std::string result;
  for (const auto &index : text) {
    const auto buffer = serialize(&index);
    result += buffer;
  }
  return result;
}

void AsciiBasicString::loadSerializeStr(const std::string &str) {
  for (int i = 0; i < str.size(); i += 2) {
    AsciiBasicChar chr;
    const std::string data =
        std::string(1, str[i]) + std::string(1, str[i + 1]);
    deserialize(&chr, data);
    this->text.push_back(chr);
  }
}

std::ostream &operator<<(std::ostream &output, const AsciiBasicString &str) {
  for (const auto &index : str) {
    output << index;
  }
  return output;
}

std::istream &operator>>(std::istream &input, AsciiBasicString &str) {
  input >> str;
  input.ignore();
  return input;
}
