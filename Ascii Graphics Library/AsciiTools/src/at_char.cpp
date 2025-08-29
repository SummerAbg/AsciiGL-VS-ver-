#include "at_char.h"
#include "at_tools.h"

namespace AsciiTools {
char AsciiBasicChar::trprChr = ' ';
AsciiTextColor AsciiBasicChar::default_clr = {ASCII_COLOR_WHITE,
                                              ASCII_COLOR_BLACK};

std::ostream &operator<<(std::ostream &output, const AsciiBasicChar &chr) {
  // static AsciiBasicChar buffer_chr;
  static AsciiTextColor buffer_clr;

  // if (chr.getColor() != buffer_chr.getColor())
  if (chr.getColor() != buffer_clr)
    setColor(chr.color);

  if (!chr.trprState)
    output << chr.character;
  else
    output << AsciiBasicChar::trprChr;

  // buffer_chr = chr;
  buffer_clr = chr.getColor();
  return output;
}

std::istream &operator>>(std::istream &input, AsciiBasicChar &chr) {
  input >> chr.character;
  input >> chr.color;
  input >> chr.trprState;
  return input;
}

AsciiBasicChar::AsciiBasicChar() {
  this->character = '\0';
  this->trprState = false;
  // this->color = {ASCII_COLOR_WHITE, ASCII_COLOR_BLACK};
  this->color = default_clr;
}

void AsciiBasicChar::info() const {
  std::cout << "AsciiBasicChar¶ÔÏó" << std::endl;
  std::cout << "character:" << character << std::endl
            << "trprState:" << trprState << std::endl;
}

std::string AsciiBasicChar::toString() const {
  return std::string(1, character);
}

bool AsciiBasicChar::operator==(const AsciiBasicChar &chr) const noexcept {
  return (character == chr.getChr() && trprState == chr.isTrpr() &&
          color == chr.getColor());
}

bool AsciiBasicChar::operator!=(const AsciiBasicChar &chr) const noexcept {
  return !(*this == chr);
}

void AsciiBasicChar::setTrprChr(char chr) noexcept { trprChr = chr; }

char AsciiBasicChar::getTrprChr() noexcept { return trprChr; }

void AsciiBasicChar::setDefaultColor(const AsciiTextColor &clr) noexcept {
  default_clr = clr;
}

AsciiTextColor AsciiBasicChar::getDefaultColor() noexcept {
  return default_clr;
}

std::string AsciiBasicChar::getSerializeStr() const {
  return serializeType(character, trprState, color);
}

void AsciiBasicChar::loadSerializeStr(const std::string &str) {
  const auto tokens = bracketMatch(str);

  if (tokens.size() != 3)
    throw AsciiBasicException(FileFormatException);

  deserializeType(character, tokens[0]);
  deserializeType(trprState, tokens[1]);
  deserializeType(color, tokens[2]);
}
} // namespace AsciiTools