#pragma once

#include "AsciiBasicString.h"

// 基本字符串画布类
class AsciiBasicCanvas : public AsciiBasicObject {
public:
  using BlockData = std::vector<AsciiBasicString>;

  // 构造基本字符串画布
  AsciiBasicCanvas();
  AsciiBasicCanvas(int length, int width,
                   const AsciiBasicString &fill = TRPRSTR);
  AsciiBasicCanvas(const std::string &canvasFilePath);

  // 获取头尾地址的函数(为了能够使用c++11的新特性)
  auto begin() const { return bDatas.begin(); }
  auto end() const { return bDatas.end(); }

  // 输出信息(DEBUG)
  void info() const;
  // 获取画布组成的字符串
  std::string toString() const;

  // 设置画布中指定坐标的数据
  void setAsciiBasicCanvasData(Coordinate2D coord,
                               const AsciiBasicString &fill);
  // 获取画布中指定坐标的数据(失败时返回空字符串)
  AsciiBasicString getAsciiBasicCanvasData(Coordinate2D coord) const;

  // 获取画布组成的AsciiBasicString字符串
  AsciiBasicString getAsciiBasicString() const;

  // 获取画布长度
  int getLength() const { return length; }
  // 获取画布宽度
  int getWidth() const { return width; }
  // 获取块长度
  int getBlockLength() const { return blockLength; }
  // 获取默认填充字符串
  AsciiBasicString getFill() const { return defaultFill; }

  // 以文件的形式保存画布
  void save(const std::string &canvasFilePath) const;
  // 以文件的形式加载画布
  void load(const std::string &canvasFilePath);

  // 清空画布数据(flag为真时,对象数据清空,flag为假时，对象恢复默认数据)
  void clear(bool flag = true);

  // 展示画布
  void show() const;

  // 判断坐标是否合法
  bool isCoordinateLegality(Coordinate2D coord) const;

  // 重载运算符
  virtual bool operator==(const AsciiBasicCanvas &canvas) const;
  virtual bool operator!=(const AsciiBasicCanvas &canvas) const;

private:
  std::string getSerializeStr() const;
  void loadSerializeStr(const std::string &str);

private:
  int length;      // 画布长度
  int width;       // 画布宽度
  int blockLength; // 块长度(基本长度单元)

  AsciiBasicString defaultFill; // 画布默认填充字符串

  BlockData bDatas; // 画布块数据
};