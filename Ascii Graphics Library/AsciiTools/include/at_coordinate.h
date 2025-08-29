#pragma once

#include "at_basic.h"
#include "at_exception.h"
#include "at_serialization.h"
#include "at_typeconvert.h"
#include <type_traits>

namespace AsciiTools {
// 2D坐标
template <typename Type> struct Coordinate2d : AsciiBasicObject {
public:
  static_assert(std::is_same_v<Type, int> || std::is_same_v<Type, double> ||
                    std::is_same_v<Type, short>,
                "Type必须是int,double或short类型");

  Type x;
  Type y;

  Coordinate2d();
  Coordinate2d(const Coordinate2d &coord);
  explicit Coordinate2d(Type x, Type y);

  bool operator==(const Coordinate2d &coord) const noexcept;
  bool operator!=(const Coordinate2d &coord) const noexcept;

  Coordinate2d<Type> operator+(const Coordinate2d &coord) const noexcept;
  Coordinate2d<Type> operator-(const Coordinate2d &coord) const noexcept;
  Coordinate2d<Type> operator*(const Coordinate2d &coord) const noexcept;
  Coordinate2d<Type> operator/(const Coordinate2d &coord) const noexcept;

  Coordinate2d<Type> operator+=(const Coordinate2d &coord) noexcept;
  Coordinate2d<Type> operator-=(const Coordinate2d &coord) noexcept;
  Coordinate2d<Type> operator*=(const Coordinate2d &coord) noexcept;
  Coordinate2d<Type> operator/=(const Coordinate2d &coord) noexcept;

  Coordinate2d<Type> &operator=(const Coordinate2d &coord) noexcept;
  // Coordinate2d<Type> &operator=(Coordinate2d &&coord) noexcept;

  Coordinate2d<Type> operator()(Type deltaX, Type deltaY) const noexcept;
  void set(Type x, Type y) noexcept;

  void info() const override;
  std::string toString() const override;

private:
  std::string getSerializeStr() const override;
  void loadSerializeStr(const std::string &str) override;
};

template <typename Type> inline Coordinate2d<Type>::Coordinate2d() {
  this->x = 0;
  this->y = 0;
}

template <typename Type>
inline Coordinate2d<Type>::Coordinate2d(const Coordinate2d &coord) {
  this->x = coord.x;
  this->y = coord.y;
}

template <typename Type> Coordinate2d<Type>::Coordinate2d(Type x, Type y) {
  this->x = x;
  this->y = y;
}

template <typename Type>
bool Coordinate2d<Type>::operator==(const Coordinate2d &coord) const noexcept {
  return (this->x == coord.x && this->y == coord.y);
}

template <typename Type>
bool Coordinate2d<Type>::operator!=(const Coordinate2d &coord) const noexcept {
  return !(*this == coord);
}

template <typename Type>
Coordinate2d<Type>
Coordinate2d<Type>::operator+(const Coordinate2d &coord) const noexcept {
  Coordinate2d ret;
  ret.x = this->x + coord.x;
  ret.y = this->y + coord.y;

  return ret;
}

template <typename Type>
Coordinate2d<Type>
Coordinate2d<Type>::operator-(const Coordinate2d &coord) const noexcept {
  Coordinate2d ret;
  ret.x = this->x - coord.x;
  ret.y = this->y - coord.y;

  return ret;
}

template <typename Type>
Coordinate2d<Type>
Coordinate2d<Type>::operator*(const Coordinate2d &coord) const noexcept {
  Coordinate2d ret;
  ret.x = this->x * coord.x;
  ret.y = this->y * coord.y;

  return ret;
}

template <typename Type>
Coordinate2d<Type>
Coordinate2d<Type>::operator/(const Coordinate2d &coord) const noexcept {
  Coordinate2d ret;
  ret.x = this->x / coord.x;
  ret.y = this->y / coord.y;

  return ret;
}

template <typename Type>
Coordinate2d<Type>
Coordinate2d<Type>::operator+=(const Coordinate2d &coord) noexcept {
  *this = *this + coord;
  return *this;
}

template <typename Type>
Coordinate2d<Type>
Coordinate2d<Type>::operator-=(const Coordinate2d &coord) noexcept {
  *this = *this - coord;
  return *this;
}

template <typename Type>
Coordinate2d<Type>
Coordinate2d<Type>::operator*=(const Coordinate2d &coord) noexcept {
  *this = *this * coord;
  return *this;
}

template <typename Type>
Coordinate2d<Type>
Coordinate2d<Type>::operator/=(const Coordinate2d &coord) noexcept {
  *this = *this / coord;
  return *this;
}

template <typename Type>
inline Coordinate2d<Type> &
Coordinate2d<Type>::operator=(const Coordinate2d &coord) noexcept {
  this->x = coord.x;
  this->y = coord.y;
  return *this;
}

/* template <typename Type>
inline Coordinate2d<Type> &
Coordinate2d<Type>::operator=(Coordinate2d &&coord) noexcept {
  this->x = coord.x;
  this->y = coord.y;
  return *this;
}*/

template <typename Type>
Coordinate2d<Type> Coordinate2d<Type>::operator()(Type deltaX,
                                                  Type deltaY) const noexcept {
  Coordinate2d coord = *this;
  coord.x += deltaX;
  coord.y += deltaY;

  return coord;
}

template <typename Type>
inline void Coordinate2d<Type>::set(Type x, Type y) noexcept {
  this->x = x;
  this->y = y;
}

template <typename Type> inline void Coordinate2d<Type>::info() const {
  std::cout << "Coordinate2d<" << typeid(Type).name() << ">对象" << std::endl;
  std::cout << this->toString() << std::endl;
}

template <typename Type>
inline std::string Coordinate2d<Type>::toString() const {
  std::string ret = spliceString(",", x, y);
  return ret;
}

template <typename Type>
inline std::string Coordinate2d<Type>::getSerializeStr() const {
  return serializeType(x, y);
}

template <typename Type>
inline void Coordinate2d<Type>::loadSerializeStr(const std::string &str) {
  const auto tokens = bracketMatch(str);

  if (tokens.size() < 2)
    throw AsciiBasicException("参数过少!至少为两个!(x,y)");

  const std::string str_x = tokens[0];
  const std::string str_y = tokens[1];

  if constexpr (std::is_same_v<Type, int>)
    *this = Coordinate2d<int>(stringToInt(str_x), stringToInt(str_y));
  else if constexpr (std::is_same_v<Type, short>)
    *this = Coordinate2d<short>(stringToShort(str_x), stringToShort(str_y));
  else if constexpr (std::is_same_v<Type, double>)
    *this = Coordinate2d<double>(stringToDouble(str_x), stringToDouble(str_y));
  else
    throw AsciiBasicException("类型异常！(不是int，short或double)");
}
} // namespace AsciiTools