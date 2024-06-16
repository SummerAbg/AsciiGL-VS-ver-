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


// 设置文本(不添加图层,在原有画布进行修改)
void setText(AsciiBasicCanvas &canvas, Coordinate2D coord,
             const AsciiBasicString &text);

// 设置文本(不添加图层,在原有图层进行修改)
// 详细说明:当某图层被调用该函数时，图层原有的数据将被覆盖！
void setText(AsciiBasicLayer &layer, Coordinate2D coord,
             const AsciiBasicString &text);

// 设置文本(添加图层)
// 详细说明:当某重名图层被该函数调用时，不进行添加图层的操作
void setText(AsciiBasicLayerMngr &mngr, Coordinate2D coord,
             const AsciiBasicString &text,
             const std::string &layerName = "textLayer");


// 设置画布边框
void setBorder(AsciiBasicCanvas &canvas, const AsciiBasicString &str);

// 比较target与canvas的不同，并返回在target范围中不同处的Point2D  <Warning>
std::vector<Point2D> compareCanvas(const AsciiBasicCanvas &target,
                                   const AsciiBasicCanvas &canvas);

// 绘制线条(level为绘制精准度，越大越好，level不得小于-15)
void setLine(AsciiBasicCanvas &canvas, Coordinate2D coord1, Coordinate2D coord2,
             const AsciiBasicString &str, int level = 1);

// 倒映画布
void reflect(AsciiBasicCanvas &canvas);

#if defined(_WIN64) || defined(_WIN32)
// 利用WinAPI缓冲选择性输出画布(可大大提高性能)
// isClean为true时，清空缓冲区
void WinAPIDraw(const AsciiBasicCanvas &canvas, bool isClean = false);

// 隐藏光标
void hideCursor();

#endif