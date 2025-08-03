﻿/**
 *
 *  @file      agl_BasicCanvas.h
 *  @brief     包括基本字符串画布类的实现
 *  @details   ~
 *  @author    0xZed_
 *  @date      19.07.2024
 *  @copyright © 0xZed_, 2024. All right reserved.
 *
 */
#pragma once

#include "agl_AbstractImage.h"
#include "agl_Basic.h"

using AsciiTools::AsciiBasicString;

namespace AsciiGL {
/**
 *
 *  @class   AsciiBasicCanvas
 *  @brief   基本字符串画布类
 *  @details
 * ~实现了对字符串画布的基本操作，如操作指定坐标的数据、获取画布信息、基本运算符的重载
 *  @date    19.07.2024
 *
 */
class AsciiAPI AsciiBasicCanvas : public AsciiBasicObject {
public:
  using CanvasData = Matrix2d<AsciiBasicString>;
  using pCanvasData = std::unique_ptr<CanvasData>;

  /**
   *  @brief AsciiBasicCanvas object constructor
   */
  AsciiBasicCanvas();

  /**
   *  @brief AsciiBasicCanvas object constructor
   *  @param length - 画布长度
   *  @param width  - 画布宽度
   *  @param str    - 填充字符串，默认是TRPRSTR（透明字符串）
   */
  AsciiBasicCanvas(int length, int width,
                   const AsciiBasicString &str = TRPRSTR);

  /**
   *  @brief AsciiBasicCanvas object constructor
   *  @param path - 文件路径
   */
  AsciiBasicCanvas(const std::string &path);

  /**
   *  @brief AsciiBasicCanvas object constructor
   *  @param canvas - 画布
   */
  AsciiBasicCanvas(const AsciiBasicCanvas &canvas);

  /**
   *  @brief AsciiBasicCanvas object constructor
   *  @param canvas - 画布
   */
  AsciiBasicCanvas(AsciiBasicCanvas &&canvas) noexcept;

  /**
   *  @brief  Return iterator to beginning
   *  @retval  - iterator to beginning
   */
  auto begin() const { return datas->begin(); }

  /**
   *  @brief  Return iterator to end
   *  @retval  - iterator to end
   */
  auto end() const { return datas->end(); }

  /**
   *  @brief 输出画布信息
   */
  virtual void info() const;

  AsciiBasicString &operator[](const Coord2d &coord);
  const AsciiBasicString &operator[](const Coord2d &coord) const;

  const AsciiBasicString &operator()(int x, int y) const;

  /**
   *  @brief 设置画布中指定坐标的数据
   *  @brief 对于画布(x, y)坐标中原有的数据，
   *  @brief 如apple，若被
   为age，则最终数据为agele
   *  @param coord - 指定坐标
   *  @param str   - 指定字符串
   */
  void setCanvas(const Coord2d &coord, const AsciiBasicString &str);

  /**
   *  @brief  获取指定坐标的画布数据(失败时抛出异常)
   *  @param  coord - 指定坐标
   *  @retval       - 指定坐标的画布数据
   */
  AsciiBasicString getCanvas(const Coord2d &coord) const;

  /**
   *  @brief  获取整个画布数据
   *  @retval  - 画布数据（画布字符串集合）
   */
  CanvasData getCanvas() const { return *datas; }

  /**
   *  @brief  获取画布组成的字符串
   *  @retval  - 字符串
   */
  std::string toString() const;

  /**
   *  @brief  获取画布组成的AsciiBasicString字符串
   *  @retval  - 由画布数据组成的AsciiBasicString字符串
   */
  AsciiBasicString toAsciiBasicString() const;

  /**
   *  @brief  获取画布长度
   *  @retval  - 返回画布长度
   */
  int getLength() const { return datas->getLength(); }

  /**
   *  @brief  获取画布宽度
   *  @retval  - 返回画布宽度
   */
  int getWidth() const { return datas->getWidth(); }

  /**
   *  @brief  获取块长度
   *  @retval  - 返回块长度
   */
  int getBlockLength() const { return block_length; }

  /**
   *  @brief  获取背景字符串
   *  @retval  - 返回背景字符串
   */
  AsciiBasicString getBackgroundStr() const {
    return datas->getBackgroundElement();
  }

  /**
   *  @brief 以文件的形式（.asc2）保存画布
   *  @param path - 带有.asc2后缀的文件路径
   */
  void save(const std::string &path) const;

  /**
   *  @brief 以文件的形式（.asc2）加载画布
   *  @param path - 带有.asc2后缀的文件路径
   */
  void load(const std::string &path);

  /**
   *  @brief 清空画布数据
   */
  void clear();

  /**
   *  @brief 展示画布
   */
  void show() const;

  /**
   *  @brief  判断指定坐标是否合法
   *  @param  coord - 指定坐标
   *  @retval       - 返回指定坐标是否合法的布尔值
   */
  bool isCoordinate(const Coord2d &coord) const;

  /**
   *  @brief  画布指定坐标转换为控制台坐标
   *  @param  coord - 指定坐标
   *  @retval       - 返回控制台坐标
   */
  COORD toConsoleCoord(const Coord2d &coord) const;

  bool operator==(const AsciiBasicCanvas &canvas) const;
  bool operator!=(const AsciiBasicCanvas &canvas) const;

  AsciiBasicCanvas &operator=(const AsciiBasicCanvas &canvas);
  AsciiBasicCanvas &operator=(AsciiBasicCanvas &&canvas) noexcept;

private:
  /**
   *  @brief  返回对象序列化字符串
   *  @retval  - 对象序列化字符串
   */
  std::string getSerializeStr() const;

  /**
   *  @brief 加载对象序列化字符串
   *  @param str - 对象序列化字符串
   */
  void loadSerializeStr(const std::string &str);

protected:
  int block_length; // 块长度(基本长度单元)

  pCanvasData datas; // 画布块数据
};
} // namespace AsciiGL