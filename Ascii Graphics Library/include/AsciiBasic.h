#pragma once

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#ifdef _WIN64
#define __FUNC__ __FUNCSIG__
#else
#define __FUNC__ __PRETTY_FUNCTION__
#endif

#if defined(_WIN64) || defined(_WIN32)
#include <windows.h>
#endif

// 2D坐标
struct Coordinate2D {
  int x;
  int y;

  Coordinate2D();
  Coordinate2D(int x, int y);

  bool operator==(Coordinate2D coord) const;
  bool operator!=(Coordinate2D coord) const;
};

// RGB颜色
struct ColorRGB {
  int r;
  int g;
  int b;

  ColorRGB();
  ColorRGB(int r, int g, int b);
  ColorRGB(const std::string &str);

  bool operator==(ColorRGB color) const;
  bool operator!=(ColorRGB color) const;

  friend std::ostream &operator<<(std::ostream &output, ColorRGB color);
  friend std::istream &operator>>(std::istream &input, ColorRGB color);

  std::string toString() const;
};

const ColorRGB ASCII_WORD_COLOR_RED = {255, 0, 0};
const ColorRGB ASCII_WORD_COLOR_ORANGE = {255, 128, 0};
const ColorRGB ASCII_WORD_COLOR_YELLOW = {255, 255, 0};
const ColorRGB ASCII_WORD_COLOR_YELLOW_GREEN = {128, 255, 0};
const ColorRGB ASCII_WORD_COLOR_GREEN = {0, 255, 0};
const ColorRGB ASCII_WORD_COLOR_CYAN_GREEN = {0, 255, 128};
const ColorRGB ASCII_WORD_COLOR_CYAN = {0, 255, 255};
const ColorRGB ASCII_WORD_COLOR_INDIGO = {0, 128, 255};
const ColorRGB ASCII_WORD_COLOR_BLUE = {0, 0, 255};
const ColorRGB ASCII_WORD_COLOR_PURPLE = {128, 0, 255};
const ColorRGB ASCII_WORD_COLOR_MAGENTA = {255, 0, 255};
const ColorRGB ASCII_WORD_COLOR_PURPLE_RED = {255, 0, 128};

const ColorRGB ASCII_WORD_COLOR_GREY = {128, 128, 128};
const ColorRGB ASCII_WORD_COLOR_BLACK = {0, 0, 0};
const ColorRGB ASCII_WORD_COLOR_WHITE = {255, 255, 255};

/////////////////////////////////////////////////////////////////

// 设置字体颜色
void setWordColor(ColorRGB color);
// 设置背景颜色
void setBackgroundColor(ColorRGB color);

// 根据两个坐标的斜率获得一次函数的值
double getY(Coordinate2D coord1, Coordinate2D coord2,
            double x); /*建议写成lambda表达式*/

using Point2D = Coordinate2D;            // 2维点坐标
using TrprData = std::vector<bool>;      // 透明数据
using ColorData = std::vector<ColorRGB>; // 颜色数据