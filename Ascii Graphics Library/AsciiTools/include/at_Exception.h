#pragma once

#include "at_Basic.h"
#include <iostream>

namespace AsciiTools {
// ��������
enum BasicException {
  CustomError,     // �Զ������
  FileNotExist,    // �ļ�������
  FileFormatError, // �ļ���ʽ����
  ArrayOverflow,   // �������
  NotInitialized   // δ��ʼ��
};

// ����������
class AsciiBasicException {
public:
  // �����������
  AsciiBasicException() = default;
  AsciiBasicException(const std::string &where, const BasicException &error);
  AsciiBasicException(const std::string &where, const std::string &error_str);

  // ��ȡ����
  std::string what() const;

private:
  std::string where;     // �������
  BasicException error;  // ��������
  std::string error_str; // �����ַ���
};
} // namespace AsciiTools