#include "AsciiBasicError.h"

AsciiBasicError::AsciiBasicError() { where = "\0"; }

AsciiBasicError::AsciiBasicError(const std::string &where,
                                 const BasicError &error) {
  this->where = where;
  this->error = error;
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
    std::cout << "系统错误!";
    break;
  }
  std::cout << std::endl;
}
