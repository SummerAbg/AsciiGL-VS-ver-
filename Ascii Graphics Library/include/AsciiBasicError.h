#pragma once

#include "AsciiGLUntils.h"

// 基本错误
enum BasicError {
  FileNotExist,    // 文件不存在
  FileFormatError, // 文件格式错误
  ArrayOverflow,   // 数组溢出
  NotInitialized   // 未初始化
};

// 基本错误类
class AsciiBasicError {
public:
  // 构造基本错误
  AsciiBasicError();
  AsciiBasicError(const std::string &where, const BasicError &error);
  AsciiBasicError(const std::string &where, const std::string &error_str);

  // 输出错误
  void printError() const;

private:
  std::string where;     // 哪里出错
  BasicError error;      // 错误类型
  std::string error_str; // 错误字符串
};