#pragma once

#include "at_basicobject.h"
#include <iostream>

namespace AsciiTools {
// AsciiColor参数个数
const int paramCount_asciicolor = 4;

// AsciiTextColor参数个数
const int paramCount_asciitextcolor = 2;

// RGBA颜色
struct AsciiColor : public AsciiBasicObject {
  int r;
  int g;
  int b;
  double a;

  AsciiColor();
  AsciiColor(int r, int g, int b, double a = 1.0);
  AsciiColor(const std::string &str);

  bool operator==(const AsciiColor &color) const noexcept;
  bool operator!=(const AsciiColor &color) const noexcept;

  friend std::ostream &operator<<(std::ostream &output,
                                  const AsciiColor &color);
  friend std::istream &operator>>(std::istream &input, AsciiColor &color);

  void info() const override;
  std::string toString() const override;

private:
  std::string getSerializeStr() const override;
  void loadSerializeStr(const std::string &str) override;
};

// 文本颜色
struct AsciiTextColor : public AsciiBasicObject {
  AsciiColor color_text;
  AsciiColor color_background;

  AsciiTextColor() = default;
  AsciiTextColor(const AsciiColor &color_text,
                 const AsciiColor &color_background);
  AsciiTextColor(const std::string &str);

  bool operator==(const AsciiTextColor &color) const noexcept;
  bool operator!=(const AsciiTextColor &color) const noexcept;

  friend std::ostream &operator<<(std::ostream &output,
                                  const AsciiTextColor &color);
  friend std::istream &operator>>(std::istream &input, AsciiTextColor &color);

  void info() const override;
  std::string toString() const override;

private:
  std::string getSerializeStr() const override;
  void loadSerializeStr(const std::string &str) override;
};

const AsciiColor ASCII_COLOR_RED = {255, 0, 0};
const AsciiColor ASCII_COLOR_ORANGE = {255, 128, 0};
const AsciiColor ASCII_COLOR_YELLOW = {255, 255, 0};
const AsciiColor ASCII_COLOR_YELLOW_GREEN = {128, 255, 0};
const AsciiColor ASCII_COLOR_GREEN = {0, 255, 0};
const AsciiColor ASCII_COLOR_CYAN_GREEN = {0, 255, 128};
const AsciiColor ASCII_COLOR_CYAN = {0, 255, 255};
const AsciiColor ASCII_COLOR_INDIGO = {0, 128, 255};
const AsciiColor ASCII_COLOR_BLUE = {0, 0, 255};
const AsciiColor ASCII_COLOR_PURPLE = {128, 0, 255};
const AsciiColor ASCII_COLOR_MAGENTA = {255, 0, 255};
const AsciiColor ASCII_COLOR_PURPLE_RED = {255, 0, 128};
const AsciiColor ASCII_COLOR_GREY = {128, 128, 128};
const AsciiColor ASCII_COLOR_BLACK = {0, 0, 0};
const AsciiColor ASCII_COLOR_WHITE = {255, 255, 255};
const AsciiColor ASCII_ALPHA = {0, 0, 0, 0.0};

const AsciiTextColor WHITE_BLACK = {ASCII_COLOR_WHITE, ASCII_COLOR_BLACK};
const AsciiTextColor RED_BLACK = {ASCII_COLOR_RED, ASCII_COLOR_BLACK};
const AsciiTextColor ORANGE_BLACK = {ASCII_COLOR_ORANGE, ASCII_COLOR_BLACK};
const AsciiTextColor YELLOW_BLACK = {ASCII_COLOR_YELLOW, ASCII_COLOR_BLACK};
const AsciiTextColor YELLOWGREEN_BLACK = {ASCII_COLOR_YELLOW_GREEN,
                                          ASCII_COLOR_BLACK};
const AsciiTextColor GREEN_BLACK = {ASCII_COLOR_GREEN, ASCII_COLOR_BLACK};
const AsciiTextColor CYAN_BLACK = {ASCII_COLOR_CYAN_GREEN, ASCII_COLOR_BLACK};
const AsciiTextColor INDIGO_BLACK = {ASCII_COLOR_INDIGO, ASCII_COLOR_BLACK};
const AsciiTextColor BLUE_BLACK = {ASCII_COLOR_BLUE, ASCII_COLOR_BLACK};
const AsciiTextColor PURPLE_BLACK = {ASCII_COLOR_PURPLE, ASCII_COLOR_BLACK};
const AsciiTextColor MAGENTA_BLACK = {ASCII_COLOR_MAGENTA, ASCII_COLOR_BLACK};
const AsciiTextColor PURPLERED_BLACK = {ASCII_COLOR_PURPLE_RED,
                                        ASCII_COLOR_BLACK};
const AsciiTextColor GREY_BLACK = {ASCII_COLOR_GREY, ASCII_COLOR_BLACK};
const AsciiTextColor BLACK_BLACK = {ASCII_COLOR_BLACK, ASCII_COLOR_BLACK};

const AsciiTextColor FG_WHITE = {ASCII_COLOR_WHITE, ASCII_ALPHA};
const AsciiTextColor FG_RED = {ASCII_COLOR_RED, ASCII_ALPHA};
const AsciiTextColor FG_ORANGE = {ASCII_COLOR_ORANGE, ASCII_ALPHA};
const AsciiTextColor FG_YELLOW = {ASCII_COLOR_YELLOW, ASCII_ALPHA};
const AsciiTextColor FG_YELLOWGREEN = {ASCII_COLOR_YELLOW_GREEN, ASCII_ALPHA};
const AsciiTextColor FG_GREEN = {ASCII_COLOR_GREEN, ASCII_ALPHA};
const AsciiTextColor FG_CYAN = {ASCII_COLOR_CYAN_GREEN, ASCII_ALPHA};
const AsciiTextColor FG_INDIGO = {ASCII_COLOR_INDIGO, ASCII_ALPHA};
const AsciiTextColor FG_BLUE = {ASCII_COLOR_BLUE, ASCII_ALPHA};
const AsciiTextColor FG_PURPLE = {ASCII_COLOR_PURPLE, ASCII_ALPHA};
const AsciiTextColor FG_MAGENTA = {ASCII_COLOR_MAGENTA, ASCII_ALPHA};
const AsciiTextColor FG_PURPLERED = {ASCII_COLOR_PURPLE_RED, ASCII_ALPHA};
const AsciiTextColor FG_GREY = {ASCII_COLOR_GREY, ASCII_ALPHA};
const AsciiTextColor FG_BLACK = {ASCII_COLOR_BLACK, ASCII_ALPHA};

const AsciiTextColor BG_WHITE = {ASCII_ALPHA, ASCII_COLOR_WHITE};
const AsciiTextColor BG_RED = {ASCII_ALPHA, ASCII_COLOR_RED};
const AsciiTextColor BG_ORANGE = {ASCII_ALPHA, ASCII_COLOR_ORANGE};
const AsciiTextColor BG_YELLOW = {ASCII_ALPHA, ASCII_COLOR_YELLOW};
const AsciiTextColor BG_YELLOWGREEN = {ASCII_ALPHA, ASCII_COLOR_YELLOW_GREEN};
const AsciiTextColor BG_GREEN = {ASCII_ALPHA, ASCII_COLOR_GREEN};
const AsciiTextColor BG_CYAN = {ASCII_ALPHA, ASCII_COLOR_CYAN_GREEN};
const AsciiTextColor BG_INDIGO = {ASCII_ALPHA, ASCII_COLOR_INDIGO};
const AsciiTextColor BG_BLUE = {ASCII_ALPHA, ASCII_COLOR_BLUE};
const AsciiTextColor BG_PURPLE = {ASCII_ALPHA, ASCII_COLOR_PURPLE};
const AsciiTextColor BG_MAGENTA = {ASCII_ALPHA, ASCII_COLOR_MAGENTA};
const AsciiTextColor BG_PURPLERED = {ASCII_ALPHA, ASCII_COLOR_PURPLE_RED};
const AsciiTextColor BG_GREY = {ASCII_ALPHA, ASCII_COLOR_GREY};
const AsciiTextColor BG_BLACK = {ASCII_ALPHA, ASCII_COLOR_BLACK};
} // namespace AsciiTools