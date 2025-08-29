#pragma once

#include "at_basic.h"
#include <format>
#include <iostream>
#include <source_location>

namespace AsciiTools {
// 基本错误
enum BasicException {
  Default,             // 默认情况
  CustomException,     // 自定义异常
  FileNotExist,        // 文件不存在
  FileFormatException, // 文件格式异常
  ArrayOverflow,       // 数组溢出
  NotInitialized,      // 未初始化
  NullptrException     // 空指针
};

// 基本异常类
class AsciiBasicException : public std::exception {
public:
  // 构造基本异常
  AsciiBasicException() = default;
  AsciiBasicException(const std::string &where, const BasicException &exp_type)
      : exp_type(exp_type), exp_description("See exp_type"), where(where),
        std::exception("exp_type exception!") {}
  AsciiBasicException(const std::string &where, const std::string &description)
      : exp_type(Default), exp_description(description), where(where),
        std::exception(description.c_str()) {}
  AsciiBasicException(
      const std::string &description,
      const std::source_location location = std::source_location::current())
      : exp_type(Default), exp_description(description), where(""),
        location(location), std::exception(description.c_str()) {}
  AsciiBasicException(
      const BasicException &exp_type,
      const std::source_location location = std::source_location::current())
      : exp_type(exp_type), exp_description("See exp_type"), where(""),
        location(location), std::exception(exp_description.c_str()) {}

  // 获取异常说明
  const char *what() const noexcept override;

private:
  std::string where;             // 哪里异常(old)
  std::string exp_description;   // 异常说明
  BasicException exp_type;       // 异常类型
  std::source_location location; // 哪里异常(new)
};
} // namespace AsciiTools