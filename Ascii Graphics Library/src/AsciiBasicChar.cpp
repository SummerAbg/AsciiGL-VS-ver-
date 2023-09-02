#include "AsciiBasicChar.h"

char AsciiBasicChar::trprChr = ' ';

AsciiBasicChar::AsciiBasicChar() {
  character = '\0';
  m_isTrpr = false;
}

std::ostream &operator<<(std::ostream &output, const AsciiBasicChar &chr) {
  if (!chr.m_isTrpr)
    output << chr.character;
  else
    output << AsciiBasicChar::trprChr;
  return output;
}

std::istream &operator>>(std::istream &input, AsciiBasicChar &chr) {
  input >> chr.character;
  input >> chr.m_isTrpr;
  input.ignore();
  return input;
}

void AsciiBasicChar::info() const {
  std::cout << "character:" << character << std::endl
            << "m_isTrpr:" << m_isTrpr << std::endl;
}

void AsciiBasicChar::setTrprChr(char chr) { trprChr = chr; }

char AsciiBasicChar::getTrprChr() { return trprChr; }

std::string AsciiBasicChar::getSerializeStr() const {
  std::string result;
  result += std::string(1, character);
  result += std::to_string(m_isTrpr);
  return result;
}

void AsciiBasicChar::loadSerializeStr(const std::string &str) {
  if (str.size() < 2) {
    throw AsciiBasicError("AsciiBasicChar::loadSerializeStr()",
                          FileFormatError);
  }

  this->character = str[0];
  this->m_isTrpr = (bool)atoi(std::string(1, str[1]).c_str());
}
