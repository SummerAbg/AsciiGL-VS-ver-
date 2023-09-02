#pragma once

#include "AsciiGLUntils.h"

// ��������
enum BasicError {
  FileNotExist,    // �ļ�������
  FileFormatError, // �ļ���ʽ����
  ArrayOverflow,   // �������
  NotInitialized   // δ��ʼ��
};

// ����������
class AsciiBasicError {
public:
  // �����������
  AsciiBasicError();
  AsciiBasicError(const std::string &where, const BasicError &error);

  // �������
  void printError() const;

private:
  std::string where; // �������
  BasicError error;  // ��������
};