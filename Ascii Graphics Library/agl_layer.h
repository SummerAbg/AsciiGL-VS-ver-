/**
 *
 *  @file      agl_layer.h
 *  @brief     包括基本字符串图层类的实现
 *  @details   ~
 *  @author    0xZed_
 *  @date      19.07.2024
 *  @copyright © 0xZed_, 2024. All right reserved.
 *
 */
#pragma once

#include "agl_canvas.h"
#include "at_entity.h"

namespace AsciiGL {
/**
 *
 *  @class   AsciiBasicLayer
 *  @brief   基本字符串图层
 *  @details
 * ~继承了基本字符串图层类，并添加了对图层坐标、中心坐标、图层名字、显示状态的操作
 *  @date    19.07.2024
 *
 */
class AsciiAPI AsciiBasicLayer : public Entity<AsciiBasicCanvas> {
public:
  /**
   *  @brief AsciiBasicLayer object constructor
   */
  AsciiBasicLayer();

  AsciiBasicLayer(const std::string label,
                  const AsciiBasicCanvas &canvas = AsciiBasicCanvas())
      : AsciiBasicLayer(canvas, Vec2d(0, 0), label) {}

  AsciiBasicLayer(std::string &&label, AsciiBasicCanvas &&canvas)
      : AsciiBasicLayer(std::move(canvas), Vec2d(0, 0), std::move(label)) {}

  AsciiBasicLayer(std::string &&label, const AsciiBasicCanvas &canvas);

  /**
   *  @brief AsciiBasicLayer object constructor
   *  @param canvas - 指定画布
   *  @param coord  - 图层坐标
   */
  AsciiBasicLayer(const AsciiBasicCanvas &canvas, const Coord2d &coord);

  /**
   *  @brief AsciiBasicLayer object constructor
   *  @param canvas - 指定画布
   *  @param coord  - 图层坐标
   */
  AsciiBasicLayer(AsciiBasicCanvas &&canvas, const Coord2d &coord);

  /**
   *  @brief AsciiBasicLayer object constructor
   *  @param canvas       - 指定画布
   *  @param coord        - 图层坐标
   *  @param label         - 图层名称
   *  @param display_state - 显示状态
   */
  AsciiBasicLayer(const AsciiBasicCanvas &canvas, const Coord2d &coord,
                  const std::string &label, bool display_state = true);

  /**
   *  @brief AsciiBasicLayer object constructor
   *  @param canvas       - 指定画布
   *  @param coord        - 图层坐标
   *  @param label         - 图层名称
   *  @param display_state - 显示状态
   */
  AsciiBasicLayer(AsciiBasicCanvas &&canvas, const Coord2d &coord,
                  std::string &&label, bool display_state = true);

  /**
   *  @brief AsciiBasicLayer object constructor
   *  @param label - 图层名称
   */
  // AsciiBasicLayer(const std::string &label);

  /**
   *  @brief AsciiBasicLayer object constructor
   *  @param layer - 图层
   */
  AsciiBasicLayer(const AsciiBasicLayer &layer);

  /**
   *  @brief AsciiBasicLayer object constructor
   *  @param layer - 图层
   */
  AsciiBasicLayer(AsciiBasicLayer &&layer) noexcept;

  /**
   *  @brief 设置图层中画布的坐标
   *  @param coord - 指定坐标
   */
  void setCoordinate(const Coord2d &coord) noexcept { this->coord = coord; }

  /**
   *  @brief  获取图层中画布的坐标
   *  @retval  - 图层坐标
   */
  Coord2d getCoordinate() const noexcept { return this->coord; }

  /**
   *  @brief 设置图层中画布的中心坐标
   *  @param coord - 指定坐标
   */
  void setCenterCoordinate(const Coord2d &coord) noexcept {
    this->center_coord = coord;
  }

  /**
   *  @brief  获取图层中画布的中心坐标
   *  @retval  - 中心坐标
   */
  Coord2d getCenterCoordinate() const noexcept { return this->center_coord; }

  /**
   *  @brief 设置图层名称
   *  @param label - 指定名称
   */
  void setLabel(const std::string &label) noexcept { this->label = label; }

  /**
   *  @brief  获取图层名称
   *  @retval  - 图层名称
   */
  std::string getLabel() const noexcept { return this->label; }

  /**
   *  @brief 设置图层的显示状态
   *  @param display_state - 显示状态的布尔值
   */
  void setDisplayState(bool display_state) noexcept {
    this->display_state = display_state;
  }

  /**
   *  @brief  获取图层的显示状态
   *  @retval  - 显示状态的布尔值
   */
  bool isDisplay() const noexcept { return this->display_state; }

  virtual bool operator==(const AsciiBasicLayer &layer) const noexcept;
  virtual bool operator!=(const AsciiBasicLayer &layer) const noexcept;

  virtual AsciiBasicLayer &operator=(const AsciiBasicLayer &layer);
  virtual AsciiBasicLayer &operator=(AsciiBasicLayer &&layer) noexcept;

  /**
   *  @brief 输出图层信息
   */
  virtual void info() const override;

protected:
  // 获取序列化字符串
  virtual std::string getSerializeStr() const override;
  // 加载序列化字符串
  virtual void loadSerializeStr(const std::string &str) override;

private:
  Coord2d coord; // 坐标
  // std::string label;    // 标签
  Coord2d center_coord; // 中心坐标(相对于画布左上角为原点的相对坐标)
  bool display_state;   // 显示状态
};
} // namespace AsciiGL