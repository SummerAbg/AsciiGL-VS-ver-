#include "AsciiBasic.h"
#include <AsciiBasicChar.h>

bool Coordinate2D::operator==(Coordinate2D coord) const {
  if (this->x == coord.x && this->y == coord.y)
    return true;
  return false;
}

bool Coordinate2D::operator!=(Coordinate2D coord) const {
  return !(*this == coord);
}

std::ostream &operator<<(std::ostream &output, ColorRGB color) {
  setWordColor(color);
  output << color.toString();
  setWordColor(AsciiBasicChar::getDefaultColor());
  return output;
}

std::istream &operator>>(std::istream &input, ColorRGB color) {
  input >> color.r;
  input >> color.g;
  input >> color.b;
  return input;
}

void setWordColor(ColorRGB color) {
  printf("\033[38;2;%d;%d;%dm", color.r, color.g, color.b);
}

void setBackgroundColor(ColorRGB color) {
  printf("\043[38;2;%d;%d;%dm", color.r, color.g, color.b);
}

double getY(Coordinate2D coord1, Coordinate2D coord2, double x) {
  const double y_ = abs(coord1.y - coord2.y) + 1;
  const double x_ = abs(coord1.x - coord2.x) + 1;
  const double k = y_ / x_;

  if (coord1.y < coord2.y)
    return k * x;
  else if (coord1.y > coord2.y)
    return -k * x;
  else // coord1.y == coord2.y
    return 0;
}

ColorRGB::ColorRGB() {
  r = 0;
  g = 0;
  b = 0;
}

ColorRGB::ColorRGB(int r, int g, int b) {
  this->r = r;
  this->g = g;
  this->b = b;
}

ColorRGB::ColorRGB(const std::string &str) {
  const auto tokens = split(str, ',');
  if (tokens.size() == 3) {
    r = stringToInt(tokens[0]);
    g = stringToInt(tokens[1]);
    b = stringToInt(tokens[2]);
  } else {
    throw AsciiBasicError(__FUNC__,
                          "str->rgb时发现字符串读取错误(tokens.size()!=3)");
  }
}

bool ColorRGB::operator==(ColorRGB color) const {
  if (this->r == color.r && this->g == color.g && this->b == color.b)
    return true;
  return false;
}

bool ColorRGB::operator!=(ColorRGB color) const { return !(*this == color); }

std::string ColorRGB::toString() const {
  return std::to_string(r) + "," + std::to_string(g) + "," + std::to_string(b);
}
