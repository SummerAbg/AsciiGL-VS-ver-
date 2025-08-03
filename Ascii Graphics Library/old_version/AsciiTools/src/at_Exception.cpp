#include "at_Exception.h"

namespace AsciiTools {
AsciiBasicException::AsciiBasicException(const std::string &where,
                                         const BasicException &error) {
  this->where = where;
  this->error = error;
  this->error_str = std::string("No describe");
}

AsciiBasicException::AsciiBasicException(const std::string &where,
                                         const std::string &error_str) {
  this->where = where;
  this->error = BasicException();
  this->error_str = error_str;
}

std::string AsciiBasicException::what() const {
  std::string ret;
  ret += "�� " + where + " �г���������� ";

  switch (error) {
  case CustomError:
    ret += error_str;
    break;

  case FileNotExist:
    ret += "�ļ�������!";
    break;

  case FileFormatError:
    ret += "�ļ���ʽ����!";
    break;

  case ArrayOverflow:
    ret += "�������!";
    break;

  case NotInitialized:
    ret += "δ��ʼ��!";
    break;

  default:
    ret += "BUG!";
    break;
  }
  ret += "\n";
  return ret;
}
} // namespace AsciiTools