#pragma once

#include "at_Basic.h"
#include "at_Exception.h"

namespace AsciiTools {
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
// string->double
double stringToDouble(const std::string &str);
// string->short
short stringToShort(const std::string &str);
// vector->string
template <typename T> std::string vectorToString(const std::vector<T> &vec);

// ��Ҫ���һ��string->vector�Ĺ��ܺ���

// ����װ����
template <typename TargetType, typename ConvertedType> class TypeDecorator {
public:
  TypeDecorator() = default;
  TypeDecorator(const ConvertedType &obj) : obj(obj) {}

  void init(const ConvertedType &obj) { this->obj = obj; }

  TargetType toTargetType() const;

private:
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
                         ConvertedType>) // AsciiBasicObject��������
    return obj.toString();
  else if constexpr (std::is_same_v<ConvertedType,
                                    const char *>) // const char*
    return std::string(obj);
  else if constexpr (std::is_same_v<ConvertedType, std::vector<std::string>>)
    return vectorToString(obj);
  else
    throw AsciiBasicException(__FUNC__, std::string("��ȷ��������!�޷�ת����") +
                                            typeid(ConvertedType).name());
}

template <typename TargetType, typename ConvertedType>
inline TargetType
TypeDecorator<TargetType, ConvertedType>::toTargetType() const {
  const std::string str = this->toString();

  if constexpr (std::is_same_v<TargetType, bool>)
    return stringToBool(str);
  else if constexpr (std::is_same_v<TargetType, int>)
    return stringToInt(str);
  else if constexpr (std::is_same_v<TargetType, double>)
    return stringToDouble(str);
  else if constexpr (std::is_same_v<TargetType, short>)
    return stringToShort(str);
  else if constexpr (std::is_same_v<TargetType, char>)
    return str[0];
  else if constexpr (std::is_same_v<TargetType, std::string>)
    return str;
  else
    throw AsciiBasicException(__FUNC__, std::string("��ȷ��������!�޷�ת����") +
                                            typeid(ConvertedType).name());
}
template <typename T> std::string vectorToString(const std::vector<T> &vec) {
  std::string ret;

  const TypeDecorator<std::string, T> decorator;
  for (const auto &index : vec) {
    decorator.init(index);
    ret += decorator.toTargetType() += " ";
  }
  return ret;
}
} // namespace AsciiTools