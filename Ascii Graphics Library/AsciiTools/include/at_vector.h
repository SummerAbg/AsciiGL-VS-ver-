#pragma once

#include "at_basicobject.h"
#include "at_serialization.h"

namespace AsciiTools {
template <typename T>
class Vector : public AsciiBasicObject, public std::vector<T> {
public:
  Vector() : std::vector<T>() {}
  Vector(const std::initializer_list<T> &elements) : std::vector<T>(elements) {}

  virtual void info() const override;
  virtual std::string toString() const override;

protected:
  // 获取序列化字符串
  virtual std::string getSerializeStr() const override;
  // 加载序列化字符串
  virtual void loadSerializeStr(const std::string &str) override;
};

template <typename T>
class Vector<std::shared_ptr<T>> : public AsciiBasicObject,
                                   public std::vector<std::shared_ptr<T>> {
public:
  using ElementType = std::shared_ptr<T>;

  Vector() : std::vector<ElementType>() {}
  Vector(const std::initializer_list<ElementType> &elements)
      : std::vector<ElementType>(elements) {}

  virtual void info() const override;
  virtual std::string toString() const override;

  virtual bool operator==(const Vector<ElementType> &vec) const noexcept;
  virtual Vector<ElementType> &operator=(const Vector<ElementType> &vec);

protected:
  // 获取序列化字符串
  virtual std::string getSerializeStr() const override;
  // 加载序列化字符串
  virtual void loadSerializeStr(const std::string &str) override;
};

template <typename T> inline void Vector<T>::info() const {
  std::cout << "Vector对象" << std::endl;
  std::cout << "size:" << this->size() << std::endl;
  std::cout << "elements:" << std::endl;

  TypeDecorator<std::string, T> type_decorator;
  for (const auto &index : *this) {
    type_decorator.init(index);
    std::cout << type_decorator.toTargetType() << "\t";
  }
  std::cout << std::endl;
}

template <typename T> inline void Vector<std::shared_ptr<T>>::info() const {
  std::cout << "Vector对象" << std::endl;
  std::cout << "size:" << this->size() << std::endl;
  std::cout << "elements:" << std::endl;

  TypeDecorator<std::string, T> type_decorator;
  for (const auto &index : *this) {
    type_decorator.init(*index);
    std::cout << type_decorator.toTargetType() << "\t";
  }
  std::cout << std::endl;
}

template <typename T> inline std::string Vector<T>::toString() const {
  std::string ret;
  TypeDecorator<std::string, T> type_decorator;
  for (const auto &index : *this) {
    type_decorator.init(index);
    ret += type_decorator.toTargetType() + " ";
  }
  return ret;
}

template <typename T>
inline std::string Vector<std::shared_ptr<T>>::toString() const {
  std::string ret;
  TypeDecorator<std::string, T> type_decorator;
  for (const auto &index : *this) {
    type_decorator.init(*index);
    ret += type_decorator.toTargetType() + " ";
  }
  return ret;
}

template <typename T>
inline bool Vector<std::shared_ptr<T>>::operator==(
    const Vector<std::shared_ptr<T>> &vec) const noexcept {
  if (this->size() != vec.size())
    return false;

  // 此处是针对元素为智能指针的情况（特殊）
  for (auto it_vec = vec.begin(), it_this = this->begin(); it_vec != vec.end();
       ++it_vec, ++it_this) {
    // 迷惑操作：第一个解引用解的是std::shared_ptr的，第二个解引用解的是std::vector<T>::const_iterator的
    if (**it_vec != **it_this)
      return false;
  }

  return true;
}

template <typename T>
inline Vector<std::shared_ptr<T>> &
Vector<std::shared_ptr<T>>::operator=(const Vector<std::shared_ptr<T>> &vec) {
  // 此实现会导致程序运行初期内存波动较大，但后期比较平稳，而且运行比较高效
  this->clear();
  for (const auto &index : vec) {
    this->push_back(std::make_shared<T>(*index));
  }
  // 用下列实现可以保证程序运行初始内存波动较小，但不保证后期（而且有一定开销）
  /* if (vec.size() >= this->size()) {
    int index = 0;
    auto it_this = this->begin();
    for (auto it_vec = vec.begin(); it_vec != vec.end(); ++it_vec, ++it_this) {
      if (++index <= this->size())
        **it_this = **it_vec;
      else
        this->push_back(std::make_shared<T>(**it_vec));
    }
  } else {
    this->resize(vec.size());
    // this->shrink_to_fit();
    auto it_this = this->begin();
    for (auto it_vec = vec.begin(); it_vec != vec.end(); ++it_vec, ++it_this) {
      **it_this = **it_vec;
    }
  }*/
  return *this;
}

template <typename T> inline std::string Vector<T>::getSerializeStr() const {
  std::string ret;
  for (const auto &index : *this) {
    ret += serializeType(index);
  }
  return ret;
}

template <typename T>
inline std::string Vector<std::shared_ptr<T>>::getSerializeStr() const {
  std::string ret;
  for (const auto &index : *this) {
    ret += serializeType(*index);
  }
  return ret;
}

//**此函数可能有一些运行时的问题**
template <typename T>
inline void Vector<T>::loadSerializeStr(const std::string &str) {
  auto tokens = bracketMatch(str);
  // TypeDecorator<T, std::string> type_decorator;
  for (const auto &index : tokens) {
    // type_decorator.init(index);
    // this->push_back(type_decorator.toTargetType());
    T object;
    deserializeType(object, index);
    this->push_back(object);
  }
}

//**此函数可能有一些运行时的问题**
template <typename T>
inline void
Vector<std::shared_ptr<T>>::loadSerializeStr(const std::string &str) {
  auto tokens = bracketMatch(str);
  // TypeDecorator<T, std::string> type_decorator;
  for (const auto &index : tokens) {
    // type_decorator.init(index);
    // this->push_back(type_decorator.toTargetType());
    T object;
    deserializeType(object, index);
    this->push_back(std::make_shared<T>(object));
  }
}
} // namespace AsciiTools