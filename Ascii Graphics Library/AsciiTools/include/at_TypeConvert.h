#pragma once

#include "at_basic.h"
#include "at_basicobject.h"
#include "at_exception.h"

namespace AsciiTools {
// 辅助模板：检测是否存在 element_type 和 operator*
template <typename T, typename = void>
struct is_smart_ptr_impl : std::false_type {};

// 偏特化：当 T 包含 element_type 且可解引用时为 true
template <typename T>
struct is_smart_ptr_impl<T, std::void_t<typename T::element_type,
                                        decltype(std::declval<T>().operator*()),
                                        decltype(std::declval<T>().get())>>
    : std::true_type {};

// 检测是不是智能指针（只能是std::shared_ptr,std::unique_ptr）
template <typename T>
struct is_smart_ptr : std::conditional_t<std::is_pointer_v<T>, std::false_type,
                                         is_smart_ptr_impl<T>> {};

/* template <typename T>
struct is_shared_ptr
    : std::conditional_t<(is_smart_ptr<T>::value &&
                          std::is_base_of_v<T, std::_Ptr_base<T>>),
                         std::true_type, std::false_type>;*/
// string->int
int stringToInt(const std::string &str);
// char->int
int charToInt(char chr);
// char->bool
bool charToBool(char chr);
// string->bool
bool stringToBool(const std::string &str);
// int->bool
bool intToBool(int number);
// int->const char*
const char *intToCString(int number);
// string->double
double stringToDouble(const std::string &str);
// string->short
short stringToShort(const std::string &str);
// vector->string
template <typename T> std::string vectorToString(const std::vector<T> &vec);

// 需要添加一个string->vector的功能函数

// 类型装饰器
template <typename TargetType, typename ConvertedType> class TypeDecorator {
public:
  TypeDecorator() = default;
  TypeDecorator(const ConvertedType &obj) : obj(obj) {}

  void init(const ConvertedType &obj) noexcept { this->obj = obj; }

  TargetType toTargetType() const;

private:
  // template <typename TargetType, typename ConvertedType>
  std::string toString() const;

private:
  ConvertedType obj;
};

template <typename T> std::string spliceString(const T &arg) {
  const TypeDecorator<std::string, T> decorator(arg);
  return decorator.toTargetType();
}

template <typename T>
std::string spliceString(const std::string &str, const T &arg) {
  const TypeDecorator<std::string, T> decorator(arg);
  return decorator.toTargetType();
}

template <typename T, typename... Args>
std::string spliceString(const std::string &str, const T &arg,
                         const Args &...args) {
  const TypeDecorator<std::string, T> decorator(arg);
  const std::string ret =
      decorator.toTargetType() + str + spliceString(str, args...);
  return ret;
}

template <typename TargetType, typename ConvertedType>
inline std::string TypeDecorator<TargetType, ConvertedType>::toString() const {
  if constexpr (std::is_same_v<ConvertedType, bool>) // bool
    return obj ? "true" : "false";
  else if constexpr (std::is_same_v<ConvertedType, char>) // char
    return std::string(1, obj);
  else if constexpr (std::is_same_v<ConvertedType, int>) // int
    return std::to_string(obj);
  else if constexpr (std::is_floating_point_v<ConvertedType>) // double or
                                                              // float
    return std::to_string(obj);
  else if constexpr (std::is_same_v<ConvertedType,
                                    std::string>) // std::string
    return obj;
  else if constexpr (std::is_base_of_v<
                         AsciiBasicObject,
                         ConvertedType>) // AsciiBasicObject的派生类
    // return obj.toString();
    return serialize(obj);
  else if constexpr (std::is_same_v<ConvertedType,
                                    const char *>) // const char*
    return std::string(obj);
  else if constexpr (std::is_same_v<
                         ConvertedType,
                         std::vector<std::shared_ptr<AsciiBasicObject>>>)
    return vectorToString(obj);
  else if constexpr (is_smart_ptr<ConvertedType>::value) {
    auto transform = [&]<typename T>(const T &obj) -> std::string {
      TypeDecorator<std::string, T> type_decorator(obj);
      return type_decorator.toTargetType();
    };
    return transform(*obj);
  } else
    throw AsciiBasicException(std::string("不确定的类型!无法转换！") +
                              typeid(ConvertedType).name());
}

template <typename TargetType, typename ConvertedType>
inline TargetType
TypeDecorator<TargetType, ConvertedType>::toTargetType() const {
  const std::string content = this->toString();

  if constexpr (std::is_same_v<TargetType, bool>)
    return stringToBool(content);
  else if constexpr (std::is_same_v<TargetType, int>)
    return stringToInt(content);
  else if constexpr (std::is_same_v<TargetType, double>)
    return stringToDouble(content);
  else if constexpr (std::is_same_v<TargetType, short>)
    return stringToShort(content);
  else if constexpr (std::is_same_v<TargetType, char>)
    return content[0];
  else if constexpr (std::is_base_of_v<ConvertedType, AsciiBasicObject> &&
                     std::is_same_v<TargetType, std::string>) {
    ConvertedType ret;
    deserializeType(ret, content);
    return ret.toString();
  } else if constexpr (std::is_same_v<TargetType, std::string>)
    return content;
  else if constexpr (std::is_same_v<ConvertedType, std::string> &&
                     std::is_base_of_v<TargetType, AsciiBasicObject>) {
    TargetType ret;
    deserializeType(ret, content);
    return ret;
  } else
    throw AsciiBasicException(std::string("不确定的类型!无法转换！") +
                              typeid(ConvertedType).name());
}
template <typename T> std::string vectorToString(const std::vector<T> &vec) {
  std::string ret;

  TypeDecorator<std::string, T> decorator;
  for (const auto &index : vec) {
    decorator.init(index);
    ret += decorator.toTargetType() += " ";
  }
  return ret;
}
} // namespace AsciiTools