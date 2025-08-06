#pragma once

#include "at_Basic.h"
#include "at_TypeConvert.h"

namespace AsciiTools {
template <typename T> void deserializeType(T &obj, const std::string &str) {
  if constexpr (!std::is_base_of_v<AsciiBasicObject, T>) {
    if constexpr (std::is_same_v<T, char>) {
      obj = static_cast<char>(stringToInt(str));
      return;
    }
    const TypeDecorator<T, std::string> decorator(str);
    obj = decorator.toTargetType();
  } else {
    deserialize(&obj, str);
  }
}
} // namespace AsciiTools