#pragma once

#include "AsciiBasicCanvas.h"

// 字符基本图层类
class AsciiBasicLayer : public AsciiBasicCanvas {
public:
  // 构造字符基本图层
  AsciiBasicLayer();
  AsciiBasicLayer(const AsciiBasicCanvas &canvas, Coordinate2D coord);
  AsciiBasicLayer(const AsciiBasicCanvas &canvas, Coordinate2D coord,
                  const std::string &name);

  // 设置图层中画布的坐标
  void setCoordinate(Coordinate2D coord) { this->coord = coord; }
  // 获取图层中画布的坐标
  Coordinate2D getCoordinate() const { return coord; }

  // 设置名称
  void setName(const std::string &name) { this->name = name; }
  // 获取名称
  std::string getName() const { return name; }

private:
  Coordinate2D coord; // 坐标
  std::string name;   // 名称
};