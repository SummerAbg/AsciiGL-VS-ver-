#pragma once

#include "AsciiBasicLayer.h"

// 字符基本图层管理器类
class AsciiBasicLayerMngr {
public:
  using DataType = std::vector<AsciiBasicLayer>;

  // 构造字符基本图层管理器
  AsciiBasicLayerMngr() {}
  AsciiBasicLayerMngr(const DataType &layers) { this->layers = layers; }
  AsciiBasicLayerMngr(int length, int width);

  // 获取头尾地址的函数(为了能够使用c++11的新特性)
  auto begin() const { return layers.begin(); }
  auto end() const { return layers.end(); }

  // 添加图层
  void addLayer(const AsciiBasicLayer &layer) { layers.push_back(layer); }
  void addLayer(const DataType &layers);

  // 删除图层
  void deleteLayer(const std::string &name);

  // 插入图层(失败时不实现插入功能)
  void insertLayer(int layerCnt, const AsciiBasicLayer &layer);
  void insertLayer(int layerCnt, const DataType &layers);

  // 获取多图层合并后生成的画布(失败时返回空画布)
  AsciiBasicCanvas getCanvas() const;
  AsciiBasicCanvas getCanvas(const std::string &name) const;

  // 下标运算符重载(获取/修改指定名称的图层)[失败时返回第一个图层]
  AsciiBasicLayer &operator[](const std::string &name);
  AsciiBasicLayer &operator[](int index);
  // 下标运算符重载(获取指定名称的图层)[失败时返回第一个图层]
  const AsciiBasicLayer &operator[](const std::string &name) const;
  const AsciiBasicLayer &operator[](int index) const;
  // 下标运算符重载(==)
  bool operator==(const AsciiBasicLayerMngr &mngr) const;
  bool operator!=(const AsciiBasicLayerMngr &mngr) const;

  // 获取管理器图层数
  int size() const { return static_cast<int>(layers.size()); }

  // 获取管理器的所有图层
  DataType getLayers() const;

  // 判断是否存在指定图层
  bool isExistLayer(const std::string &name) const;
  // 获取指定图层所在层数(失败时返回-1)
  int getLayerCount(const std::string &name) const;

private:
  DataType layers;
};