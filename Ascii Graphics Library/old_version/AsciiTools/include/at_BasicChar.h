#pragma once

#include "at_Basic.h"
#include "at_BasicObject.h"
#include "at_TextColor.h"

namespace AsciiTools {
// �����ַ���
class AsciiBasicChar : public AsciiBasicObject {
public:
  // ��������ַ�
  AsciiBasicChar() = default;
  AsciiBasicChar(char chr, bool trprState = false)
      : character(chr), color(getDefaultColor()), trprState(trprState) {}
  AsciiBasicChar(char chr, AsciiTextColor clr, bool trprState = false)
      : character(chr), color(clr), trprState(trprState) {}

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
  static void setDefaultColor(AsciiTextColor clr);
  // ��ȡĬ����ɫ
  static AsciiTextColor getDefaultColor();

  // ��ȡ�ַ�
  char getChr() const { return character; }
  // �����ַ�
  void setChr(char chr) { character = chr; }
  // ��ȡ͸��״̬
  bool isTrpr() const { return trprState; }
  // ����͸��
  void setTrpr(bool trprState) { this->trprState = trprState; }
  // ��ȡ��ɫ
  AsciiTextColor getColor() const { return color; }
  // ������ɫ
  void setColor(AsciiTextColor clr) { color = clr; }

private:
  std::string getSerializeStr() const;
  void loadSerializeStr(const std::string &str);

private:
  char character;       // �ַ�
  bool trprState;       // ͸��״̬
  AsciiTextColor color; // ��ɫ

  static char trprChr;               // ͸���ַ�(͸��ʱ�����ַ�)
  static AsciiTextColor default_clr; // Ĭ����ɫ
};
} // namespace AsciiTools