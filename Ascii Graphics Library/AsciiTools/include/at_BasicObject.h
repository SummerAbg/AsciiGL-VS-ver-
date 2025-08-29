#pragma once

#include "at_basic.h"
#include "at_exception.h"

namespace AsciiTools {
// 基本对象抽象类
class AsciiBasicObject {
public:
  virtual ~AsciiBasicObject() {}
  // 输出信息
  virtual void info() const = 0;
  // 获取字符串
  virtual std::string toString() const = 0;

  // 序列化对象
  friend std::string serialize(const AsciiBasicObject &obj) {
    return obj.getSerializeStr();
  }
  // 反序列化对象
  friend void deserialize(AsciiBasicObject &obj, const std::string &str) {
    obj.loadSerializeStr(str);
  }

protected:
  // 获取序列化字符串
  virtual std::string getSerializeStr() const = 0;
  // 加载序列化字符串
  virtual void loadSerializeStr(const std::string &str) = 0;
};
} // namespace AsciiTools