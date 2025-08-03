#pragma once

#include "at_Basic.h"
#include "at_Exception.h"

namespace AsciiTools {
// �������������
class AsciiBasicObject {
public:
  // �����Ϣ
  virtual void info() const = 0;
  // ��ȡ�ַ���
  virtual std::string toString() const = 0;

  // ���л�����
  friend std::string serialize(const AsciiBasicObject *obj);
  // �����л�����
  friend void deserialize(AsciiBasicObject *obj, const std::string &str);

protected:
  // ��ȡ���л��ַ���
  virtual std::string getSerializeStr() const = 0;
  // �������л��ַ���
  virtual void loadSerializeStr(const std::string &str) = 0;
};
} // namespace AsciiTools