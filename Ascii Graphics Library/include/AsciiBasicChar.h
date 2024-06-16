#pragma once

#include "AsciiBasicObject.h"

// �����ַ���
class AsciiBasicChar : public AsciiBasicObject {
public:
  // ��������ַ�
  AsciiBasicChar();
  AsciiBasicChar(char chr, bool isTrpr = false)
      : character(chr), colorVal(getDefaultColor()), m_isTrpr(isTrpr) {}
  AsciiBasicChar(char chr, ColorRGB clr, bool isTrpr = false)
      : character(chr), colorVal(clr), m_isTrpr(isTrpr) {}

  // �����Ϣ
  void info() const;
  // AsciiBasicCharת��Ϊstd::string
  std::string toString() const;

  bool operator==(const AsciiBasicChar &chr) const;
  bool operator!=(const AsciiBasicChar &chr) const;

  friend std::ostream &operator<<(std::ostream &output,
                                  const AsciiBasicChar &chr);

  friend std::istream &operator>>(std::istream &input, AsciiBasicChar &chr);

  // ����͸���ַ�
  static void setTrprChr(char chr);
  // ��ȡ͸���ַ�
  static char getTrprChr();
  // ����Ĭ����ɫ
  static void setDefaultColor(ColorRGB clr);
  // ��ȡĬ����ɫ
  static ColorRGB getDefaultColor();

  // ��ȡ�ַ�
  char getChr() const { return character; }
  // �����ַ�
  void setChr(char chr) { character = chr; }
  // ��ȡ͸��״̬
  bool isTrpr() const { return m_isTrpr; }
  // ����͸��
  void setTrpr(bool isTrpr) { m_isTrpr = isTrpr; }
  // ��ȡ��ɫֵ
  ColorRGB getColor() const { return colorVal; }
  // ������ɫֵ
  void setColor(ColorRGB clr) { colorVal = clr; }

private:
  std::string getSerializeStr() const;
  void loadSerializeStr(const std::string &str);

private:
  char character;    // �ַ�
  bool m_isTrpr;     // �Ƿ�͸��
  ColorRGB colorVal; // ��ɫֵ

  static char trprChr;         // ͸���ַ�(͸��ʱ�����ַ�)
  static ColorRGB default_clr; // Ĭ����ɫ
};

// �ַ���
/* class AsciiChar : public AsciiBasicChar {
public:
  using Color16 = unsigned short;

  AsciiChar() : AsciiBasicChar() { colorVal = 0; }
  AsciiChar(char chr, bool isTrpr, Color16 colorVal)
      : AsciiBasicChar(chr, isTrpr) {
    this->colorVal = colorVal;
  };

  // ��ȡ��ɫֵ
  Color16 getColor() const { return colorVal; }
  // ������ɫֵ
  void setColor(Color16 colorVal) { this->colorVal = colorVal; }

private:
  Color16 colorVal;
};*/