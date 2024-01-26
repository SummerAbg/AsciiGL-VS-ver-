#include "AsciiBasicChar.h"

char AsciiBasicChar::trprChr = ' ';
ColorRGB AsciiBasicChar::default_clr = ASCII_WORD_COLOR_WHITE;

AsciiBasicChar::AsciiBasicChar() {
  character = '\0';
  m_isTrpr = false;
  colorVal = ColorRGB();
}

std::ostream &operator<<(std::ostream &output, const AsciiBasicChar &chr) {
  // setWordColor(chr.colorVal);
  static AsciiBasicChar buffer_chr;

  if (chr.getColor() != buffer_chr.getColor())
    setWordColor(chr.colorVal);

  if (!chr.m_isTrpr)
    output << chr.character;
  else
    output << AsciiBasicChar::trprChr;

  // setWordColor(AsciiBasicChar::default_clr);

  buffer_chr = chr;

  return output;
}

std::istream &operator>>(std::istream &input, AsciiBasicChar &chr) {
  input >> chr.character;
  input >> chr.colorVal;
  input >> chr.m_isTrpr;
  return input;
}

void AsciiBasicChar::info() const {
  std::cout << "character:" << character << std::endl
            << "m_isTrpr:" << m_isTrpr << std::endl;
}

std::string AsciiBasicChar::toString() const {
  return std::string(1, character);
}

bool AsciiBasicChar::operator==(const AsciiBasicChar &chr) const {
  if (character == chr.getChr() && m_isTrpr == chr.isTrpr() &&
      colorVal == chr.getColor()) {
    return true;
  }
  return false;
}

bool AsciiBasicChar::operator!=(const AsciiBasicChar &chr) const {
  return !(*this == chr);
}

void AsciiBasicChar::setTrprChr(char chr) { trprChr = chr; }

char AsciiBasicChar::getTrprChr() { return trprChr; }

void AsciiBasicChar::setDefaultColor(ColorRGB clr) { default_clr = clr; }

ColorRGB AsciiBasicChar::getDefaultColor() { return default_clr; }

std::string AsciiBasicChar::getSerializeStr() const {
  std::string result;
  result += std::string(1, character) + ";";
  result += std::to_string(m_isTrpr) + ";";
  result += colorVal.toString() + ";";
  return result;
}

void AsciiBasicChar::loadSerializeStr(const std::string &str) {
  const auto tokens = split(str, ';');

  if (tokens.size() != 2) {
    throw AsciiBasicError(__FUNC__, FileFormatError);
  }

  this->character = str[0];
  this->m_isTrpr = charToBool(str[1]);
  colorVal = ColorRGB(tokens[1]);
}
