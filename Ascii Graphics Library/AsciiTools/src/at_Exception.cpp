#include "at_exception.h"

namespace AsciiTools {
const char *AsciiBasicException::what() const noexcept {
  static std::string ret;
  if (where == "") {
    ret = std::format(
        "文件: {}\n函数: {}\n行号: {}\n异常说明: ", location.file_name(),
        location.function_name(), location.line());
  } else {
    ret = std::format("在 {} 中出现了意外的 ", where);
  }

  switch (exp_type) {
  case Default:
    ret += this->exp_description;
    break;

  case CustomException:
    ret += this->exp_description;
    break;

  case FileNotExist:
    ret += "文件不存在!";
    break;

  case FileFormatException:
    ret += "文件格式错误!";
    break;

  case ArrayOverflow:
    ret += "数组溢出!";
    break;

  case NotInitialized:
    ret += "未初始化!";
    break;

  case NullptrException:
    ret += "空指针!";
    break;

  default:
    ret += "AsciiTools::AsciiBasicException类出现异常!";
    break;
  }
  return ret.c_str();
}
} // namespace AsciiTools