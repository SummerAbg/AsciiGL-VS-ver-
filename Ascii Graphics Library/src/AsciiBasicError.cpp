#include "AsciiBasicError.h"

AsciiBasicError::AsciiBasicError() { where = "\0"; }

AsciiBasicError::AsciiBasicError(const std::string &where,
                                 const BasicError &error) {
  this->where = where;
  this->error = error;
}

void AsciiBasicError::printError() const {
  std::cout << "�� " << where << " �г���������� ";

  switch (error) {
  case FileNotExist:
    std::cout << "�ļ�������!";
    break;

  case FileFormatError:
    std::cout << "�ļ���ʽ����!";
    break;

  case ArrayOverflow:
    std::cout << "�������!";
    break;

  case NotInitialized:
    std::cout << "δ��ʼ��!";
    break;

  default:
    std::cout << "ϵͳ����!";
    break;
  }
  std::cout << std::endl;
}
