#include "AsciiBasicError.h"

AsciiBasicError::AsciiBasicError() { where = "\0"; }

AsciiBasicError::AsciiBasicError(const std::string &where,
                                 const BasicError &error) {
  this->where = where;
  this->error = error;
}

AsciiBasicError::AsciiBasicError(const std::string &where,
                                 const std::string &error_str) {
  this->where = where;
  this->error_str = error;
}

void AsciiBasicError::printError() const {
  std::cout << "在 " << where << " 中出现了意外的 ";

  switch (error) {
  case FileNotExist:
    std::cout << "文件不存在!";
    break;

  case FileFormatError:
    std::cout << "文件格式错误!";
    break;

  case ArrayOverflow:
    std::cout << "数组溢出!";
    break;

  case NotInitialized:
    std::cout << "未初始化!";
    break;

  default:
    std::cout << error_str;
    break;
  }
  std::cout << std::endl;
}
