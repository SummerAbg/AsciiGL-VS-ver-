#pragma once

#include "AsciiBasicLayerMngr.h"

// 获取指定区域的画布(失败时返回一个空的基本字符串画布)
AsciiBasicCanvas getCanvas(const AsciiBasicCanvas &canvas, Coordinate2D coord1,
                           Coordinate2D coord2);

// 重叠两个画布
// 会将canvas重叠在target的(x,y)上，最终画布大小以target为标准
AsciiBasicCanvas overlapCanvas(const AsciiBasicCanvas &canvas,
                               const AsciiBasicCanvas &target,
                               Coordinate2D coord);

// 设置文本
void setText(AsciiBasicCanvas &canvas, Coordinate2D coord,
             const AsciiBasicString &text);

// 设置画布边框
void setBorder(AsciiBasicCanvas &canvas, const AsciiBasicString &str);

// 比较target与canvas的不同，并返回在target范围中不同处的Point2D  <Warning>
std::vector<Point2D> compareCanvas(const AsciiBasicCanvas &target,
                                   const AsciiBasicCanvas &canvas);

// 绘制线条(废用)
void setLine(AsciiBasicCanvas &canvas, Coordinate2D coord1, Coordinate2D coord2,
             const AsciiBasicString &str);

// 利用WinAPI输出画布(可大大提高性能)
void WinAPIDraw(const AsciiBasicCanvas &canvas);