#pragma once

#include "AsciiBasicObject.h"

// �����ַ���
class AsciiBasicChar : public AsciiBasicObject {
public:
  // ��������ַ�
  AsciiBasicChar();
  AsciiBasicChar(char chr, bool isTrpr = false)
      : character(chr), m_isTrpr(isTrpr) {}

  // �����Ϣ
  void info() const;

  friend std::ostream &operator<<(std::ostream &output,
                                  const AsciiBasicChar &chr);

  friend std::istream &operator>>(std::istream &input, AsciiBasicChar &chr);

  // ����͸���ַ�
  static void setTrprChr(char chr);
  // ��ȡ͸���ַ�
  static char getTrprChr();

  // ��ȡ�ַ�
  char getChr() const { return character; }
  // �����ַ�
  void setChr(char chr) { character = chr; }
  // ��ȡ͸��״̬
  bool isTrpr() const { return m_isTrpr; }
  // ����͸��
  void setTrpr(bool isTrpr) { m_isTrpr = isTrpr; }

private:
  std::string getSerializeStr() const;
  void loadSerializeStr(const std::string &str);

private:
  char character;
  bool m_isTrpr;
  static char trprChr; // ͸���ַ�(͸��ʱ�����ַ�)
};