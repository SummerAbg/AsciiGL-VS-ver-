#pragma once

#include "at_basicobject.h"
#include "at_coordinate.h"
#include "at_deserialization.h"
#include "at_exception.h"
#include "at_ptrvector.h"
#include "at_serialization.h"
#include "at_typeconvert.h"
#include <vector>

namespace AsciiTools {
const int paramCount_matrix2d_element = 2;
const int paramCount_matrix2d = 4;

template <typename ElementType>
struct Matrix2dElement : public AsciiBasicObject {
public:
  Coord2d coord;
  ElementType element;

  Matrix2dElement() = default;
  Matrix2dElement(const Coord2d &coord, const ElementType &element);
  Matrix2dElement(const Matrix2dElement &element);
  Matrix2dElement(Matrix2dElement &&element) noexcept;

  bool operator==(const Matrix2dElement<ElementType> &element) const noexcept;
  bool operator!=(const Matrix2dElement<ElementType> &element) const noexcept;

  Matrix2dElement<ElementType> &
  operator=(const Matrix2dElement<ElementType> &element);
  Matrix2dElement<ElementType> &
  operator=(Matrix2dElement<ElementType> &&element) noexcept;

  void info() const override;
  std::string toString() const override;

private:
  std::string getSerializeStr() const override;
  void loadSerializeStr(const std::string &str) override;
};

// 目前Matrix2d的序列化和对象实例化逻辑是根据background_element作为大背景，
// 然后elements就负责存储与大背景不同的元素
// 这样能够在矩阵数据不太复杂（指元素大多相等）的情况下能够节省一定内存空间，但是会造成一定运行开销

// 基于以上逻辑，当AsciiBasicCanvas使用image->canvas时，不但不会进行大背景的抽象，而且还会将所有的canvas数据进行存储
// 所以这也是为什么当AsciiBasicCanvas加载并操作asc2文件（特别是image->canvas的asc2文件）时会有巨大开销的原因
// 解决方案：①优化image->canvas算法 ②重构Matrix2d加载逻辑

// 目前该类占CPU时间最多的是getElement(const Coord &coord)
// 当前有一种设想：让Matrix2d存储存储指针的容器（非nullptr时访问），这样也许能够线性遍历，降低getElement的时间复杂度(现已实现)
template <typename ElementType> class Matrix2d : public AsciiBasicObject {
public:
  using Element = Matrix2dElement<ElementType>; // 带有坐标的元素
  // using Elements = std::vector<Element>;        // 存储元素的容器
  using Elements = PtrVector<Element>;         // 存储元素的容器
  using pElements = std::unique_ptr<Elements>; // 容器指针

  Matrix2d();
  Matrix2d(int length, int width, const ElementType &element);
  Matrix2d(const Matrix2d<ElementType> &matrix);
  Matrix2d(Matrix2d<ElementType> &&matrix) noexcept;
  // virtual ~Matrix2d() {}

  auto begin() const noexcept { return elements->begin(); }
  auto end() const noexcept { return elements->end(); }

  int getLength() const noexcept { return length; }
  int getWidth() const noexcept { return width; }

  // 只适用于使用了Matrix2d()的情况下
  void setLength(int length) noexcept { this->length = length; }
  void setWidth(int width) noexcept { this->width = width; }

  size_t size() const noexcept { return this->elements->size(); }

  ElementType &operator[](const Coord2d &coord);
  ElementType &operator()(int x, int y);

  ElementType getElement(const Coord2d &coord) const;
  ElementType getElement(int x, int y) const;

  const ElementType &operator[](const Coord2d &coord) const;
  const ElementType &operator()(int x, int y) const;

  Elements getElements() const noexcept { return *elements; }
  ElementType getBackgroundElement() const noexcept {
    return background_element;
  }

  void append(const Element &element) { this->elements->push_back(element); }

  Matrix2d<ElementType> &operator=(const Matrix2d<ElementType> &matrix);
  Matrix2d<ElementType> &operator=(Matrix2d<ElementType> &&matrix) noexcept;

  bool operator==(const Matrix2d<ElementType> &matrix) const;
  bool operator!=(const Matrix2d<ElementType> &matrix) const;

  bool isCoordinate(const Coord2d &coord) const noexcept;
  bool isCoordinate(int x, int y) const noexcept;

  void clear() noexcept { this->elements->clear(); }
  void show() const noexcept;

  void info() const noexcept override;
  std::string toString() const override;

private:
  std::string getSerializeStr() const override;
  void loadSerializeStr(const std::string &str) override;

protected:
  int length;
  int width;
  pElements elements;
  ElementType background_element;
};

template <typename Element> inline Matrix2d<Element>::Matrix2d() {
  this->length = 0;
  this->width = 0;
  this->elements = std::make_unique<Elements>();
}

template <typename ElementType>
inline Matrix2d<ElementType>::Matrix2d(int length, int width,
                                       const ElementType &element) {
  this->length = length;
  this->width = width;
  this->background_element = element;
  // 默认填充nullptr
  size_t size = length * width;
  this->elements = std::make_unique<Elements>(size, true);
  // this->elements = std::make_unique<Elements>();
}

template <typename ElementType>
inline Matrix2d<ElementType>::Matrix2d(const Matrix2d<ElementType> &matrix) {
  this->length = matrix.length;
  this->width = matrix.width;
  this->background_element = matrix.background_element;
  this->elements = std::make_unique<Elements>(*matrix.elements);
}

template <typename ElementType>
inline Matrix2d<ElementType>::Matrix2d(
    Matrix2d<ElementType> &&matrix) noexcept {
  this->length = matrix.length;
  this->width = matrix.width;
  this->background_element = std::move(matrix.background_element);
  this->elements = std::move(matrix.elements);

  matrix.elements = nullptr;
}

template <typename ElementType>
inline ElementType &Matrix2d<ElementType>::operator[](const Coord2d &coord) {
  if (!isCoordinate(coord))
    throw AsciiBasicException("coord非法!");

  /* for (auto &index : *elements) {
    if (coord == index->coord)
      return index->element;
  }*/
  /* for (auto &index : *elements) {
    if (coord == index.coord)
      return index.element;
  }*/
  /* elements->emplace_back(Matrix2dElement(coord, background_element));
  return (*elements)[elements->size() - 1].element;*/

  const size_t index = coord.y * length + coord.x;
  if (elements->isNullptr(index))
    elements->init(index, Matrix2dElement(coord, background_element));
  return (*elements)[index].element;
}

template <typename ElementType>
inline ElementType &Matrix2d<ElementType>::operator()(int x, int y) {
  if (!isCoordinate(x, y))
    throw AsciiBasicException("coord非法!");

  return (*this)[Vec2d(x, y)];
}

/**************开销重灾区！！！占CPU时间最多的函数****************/
template <typename ElementType>
inline ElementType
Matrix2d<ElementType>::getElement(const Coord2d &coord) const {
  if (!isCoordinate(coord))
    throw AsciiBasicException("coord非法!");

  /* for (const auto &index : *elements) {
    if (coord == index->coord)
      return index->element;
  }*/
  /* for (const auto &index : *elements) {
    if (coord == index.coord)
      return index.element;
  }
  return this->background_element;*/
  const size_t index = coord.y * length + coord.x;

  if (this->elements->isFlow(index) || this->elements->isNullptr(index))
    return background_element;
  else
    return (*elements)[index].element;
}

template <typename ElementType>
inline ElementType Matrix2d<ElementType>::getElement(int x, int y) const {
  if (!isCoordinate(x, y))
    throw AsciiBasicException("coord非法!");

  return this->getElement(Vec2d(x, y));
}

template <typename ElementType>
inline const ElementType &
Matrix2d<ElementType>::operator[](const Coord2d &coord) const {
  if (!isCoordinate(coord))
    throw AsciiBasicException("coord非法!");

  return this->getElement(coord);
}

template <typename ElementType>
inline const ElementType &Matrix2d<ElementType>::operator()(int x,
                                                            int y) const {
  if (!isCoordinate(x, y))
    throw AsciiBasicException("coord非法!");

  return this->getElement(x, y);
}

template <typename ElementType>
inline Matrix2d<ElementType> &
Matrix2d<ElementType>::operator=(const Matrix2d<ElementType> &matrix) {
  this->length = matrix.length;
  this->width = matrix.width;
  this->background_element = matrix.background_element;
  *this->elements = *matrix.elements;

  return *this;
}

template <typename ElementType>
inline Matrix2d<ElementType> &
Matrix2d<ElementType>::operator=(Matrix2d<ElementType> &&matrix) noexcept {
  this->length = matrix.length;
  this->width = matrix.width;
  this->background_element = std::move(matrix.background_element);
  this->elements = std::move(matrix.elements);
  matrix.elements = nullptr;

  return *this;
}

template <typename ElementType>
inline bool
Matrix2d<ElementType>::operator==(const Matrix2d<ElementType> &matrix) const {
  return (this->length == matrix.length && this->width == matrix.width &&
          this->background_element == matrix.background_element &&
          *this->elements == *matrix.elements);
}

template <typename ElementType>
inline bool
Matrix2d<ElementType>::operator!=(const Matrix2d<ElementType> &matrix) const {
  return !(*this == matrix);
}

template <typename ElementType>
inline bool
Matrix2d<ElementType>::isCoordinate(const Coord2d &coord) const noexcept {
  return (coord.x >= 0 && coord.x < length && coord.y >= 0 && coord.y < width)
             ? true
             : false;
}

template <typename ElementType>
inline bool Matrix2d<ElementType>::isCoordinate(int x, int y) const noexcept {
  return (x >= 0 && x < length && y >= 0 && y < width) ? true : false;
}

template <typename ElementType>
inline void Matrix2d<ElementType>::show() const noexcept {
  std::cout << this->toString();
}

template <typename ElementType>
inline void Matrix2d<ElementType>::info() const noexcept {
  std::cout << "Matrix2d<" << typeid(ElementType).name() << ">对象"
            << std::endl;
  std::cout << "length:" << length << std::endl;
  std::cout << "width:" << width << std::endl;
  std::cout << "background_element:" << background_element << std::endl;
  this->show();
}

template <typename ElementType>
inline std::string Matrix2d<ElementType>::toString() const {
  std::string ret;
  TypeDecorator<std::string, ElementType> decorator;

  for (int i = 0; i < width; i++) {
    for (int j = 0; j < length; j++) {
      decorator.init(this->getElement(j, i));

      ret += decorator.toTargetType();
      ret += "\t";
    }
    ret += "\n";
  }
  return ret;
}

template <typename ElementType>
inline std::string Matrix2d<ElementType>::getSerializeStr() const {
  const std::string str_elements = serializeType(*elements);

  /* for (const auto index : *elements) {
    str_elements += serializeType(*index);
  }*/
  return serializeType(length, width, str_elements, background_element);
}

template <typename ElementType>
inline void Matrix2d<ElementType>::loadSerializeStr(const std::string &str) {
  const auto tokens = bracketMatch(str);

  if (tokens.size() != paramCount_matrix2d) {
    throw AsciiBasicException(
        __FUNC__, "str->matrix2d时发现字符串读取错误(tokens.size()!=" +
                      std::to_string(paramCount_matrix2d) + ")");
  }

  deserializeType(length, tokens[0]);
  deserializeType(width, tokens[1]);

  const auto tokens_elements = bracketMatch(tokens[2]);
  const size_t size_matrix = length * width;
  // 初始化size_matrix个nullptr
  this->elements = std::make_unique<Elements>(size_matrix, true);

  for (const auto &index : tokens_elements) {
    Matrix2dElement<ElementType> element;
    deserializeType(element, index);

    const size_t index_element = element.coord.y * length + element.coord.x;
    (*this->elements).init(index_element, std::move(element));
  }

  deserializeType(background_element, tokens[3]);
}

template <typename ElementType>
inline Matrix2dElement<ElementType>::Matrix2dElement(
    const Coord2d &coord, const ElementType &element) {
  this->coord = coord;
  this->element = element;
}

template <typename ElementType>
inline Matrix2dElement<ElementType>::Matrix2dElement(
    const Matrix2dElement &element) {
  this->coord = element.coord;
  this->element = element.element;
}

template <typename ElementType>
inline Matrix2dElement<ElementType>::Matrix2dElement(
    Matrix2dElement &&element) noexcept {
  this->coord = element.coord;
  this->element = std::move(element.element);
}

template <typename ElementType>
inline bool Matrix2dElement<ElementType>::operator==(
    const Matrix2dElement<ElementType> &element) const noexcept {
  return (this->coord == element.coord && this->element == element.element);
}

template <typename ElementType>
inline bool Matrix2dElement<ElementType>::operator!=(
    const Matrix2dElement<ElementType> &element) const noexcept {
  return !(*this == element);
}

template <typename ElementType>
inline Matrix2dElement<ElementType> &Matrix2dElement<ElementType>::operator=(
    const Matrix2dElement<ElementType> &element) {
  this->coord = element.coord;
  this->element = element.element;
  return *this;
}

template <typename ElementType>
inline Matrix2dElement<ElementType> &Matrix2dElement<ElementType>::operator=(
    Matrix2dElement<ElementType> &&element) noexcept {
  this->coord = element.coord;
  this->element = std::move(element.element);
  return *this;
}

template <typename ElementType>
inline void Matrix2dElement<ElementType>::info() const {
  std::cout << "Matrix2dElement<" << typeid(ElementType).name() << ">对象"
            << std::endl;
  std::cout << "coord:" << coord.toString() << std::endl;
  std::cout << "element:" << element << std::endl;
}

template <typename ElementType>
inline std::string Matrix2dElement<ElementType>::toString() const {
  return spliceString(",", coord, element);
}

template <typename ElementType>
inline std::string Matrix2dElement<ElementType>::getSerializeStr() const {
  return serializeType(coord, element);
}

template <typename ElementType>
inline void
Matrix2dElement<ElementType>::loadSerializeStr(const std::string &str) {
  const auto tokens = bracketMatch(str);
  if (tokens.size() != 2) {
    throw AsciiBasicException(
        __FUNC__, "str->Matrix2dElement时发现字符串读取错误(tokens.size()!=" +
                      std::to_string(paramCount_matrix2d_element) + ")");
  }
  deserializeType(coord, tokens[0]);
  deserializeType(element, tokens[1]);
}
} // namespace AsciiTools