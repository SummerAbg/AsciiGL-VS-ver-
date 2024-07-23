#pragma once

#include "at_BasicChar.h"

namespace AsciiTools {
// �����ַ�����
class AsciiBasicString : public AsciiBasicObject {
public:
  using Text = std::vector<AsciiBasicChar>;

  // ��������ַ���
  AsciiBasicString() = default;
  AsciiBasicString(
      const char *str, bool isTrpr = false,
      const AsciiTextColor clr = AsciiBasicChar::getDefaultColor());
  AsciiBasicString(
      const std::string &str, bool isTrpr = false,
      const AsciiTextColor clr = AsciiBasicChar::getDefaultColor());
  AsciiBasicString(const char *str, const AsciiTextColorData &clr,
                   const AsciiTrprData &trpr);
  AsciiBasicString(const std::string &str, const AsciiTextColorData &clr,
                   const AsciiTrprData &trpr);
  AsciiBasicString(const AsciiBasicChar &chr);

  // �����Ϣ
  void info() const;
  // AsciiBasicStringת��Ϊstd::string
  std::string toString() const;

  // ��ȡͷβ��ַ�ĺ���(Ϊ���ܹ�ʹ��c++11��������)
  auto begin() const { return text.begin(); }
  auto end() const { return text.end(); }

  // ���������
  bool operator==(const AsciiBasicString &str) const;
  bool operator!=(const AsciiBasicString &str) const;

  AsciiBasicString operator+=(const AsciiBasicString &str);
  AsciiBasicString operator+=(const AsciiBasicChar &chr);
  AsciiBasicString operator+(const AsciiBasicString &str) const;
  AsciiBasicString operator+(const AsciiBasicChar &chr) const;

  AsciiBasicChar &operator[](int index);
  const AsciiBasicChar &operator[](int index) const;

  /////////////////////////////////////////////////////////////

  // ��ָ��λ�ò����ַ�/�ַ���
  // void insert(int index, const AsciiBasicString &str);
  // void insert(int index, const AsciiBasicChar &chr);

  // ɾ���ַ���ָ��λ�õ��ַ�
  void del(int index);
  // ���ַ�����ĩβ����ַ�
  void append(const AsciiBasicChar &chr) { text.emplace_back(chr); }
  void append(const AsciiBasicString &str);
  // ����ַ���
  void clear();

  // ��ȡ�ַ�����С
  int size() const { return static_cast<int>(text.size()); }

  // ��ȡ͸������
  AsciiTrprData getTrprData() const;
  // ��ȡ��ɫ����
  AsciiTextColorData getTextColorData() const;

  // ������������
  friend std::ostream &operator<<(std::ostream &output,
                                  const AsciiBasicString &str);
  // �������������
  friend std::istream &operator>>(std::istream &input, AsciiBasicString &str);

private:
  std::string getSerializeStr() const;
  void loadSerializeStr(const std::string &str);

private:
  Text text; // �ַ�����
};

const AsciiBasicString TRPRSTR = {
    "  ", true, {ASCII_COLOR_GREY, ASCII_COLOR_BLACK}};

// ��ȡ����Ӧ�ַ���
AsciiBasicString getAdaptiveStr(const AsciiBasicChar &chr);

// �����ַ���(��ȡindexλ�ü�֮ǰ���ַ���)
AsciiBasicString cutString(const AsciiBasicString &str, int index);

// �ص��ַ���
// ��strB�ص���strA��position��λ����
// ��isLimitΪtrueʱ���õ����ַ�����С��strAΪ��׼
// ��:
//    �ٵ�strA�ĳ��ȴ���strB�ĳ����Ҵ��ڷ��޶�ģʽ��:
//      "egg"�ص���"apple"��0λ���ϣ��õ�"eggle"
//    �ڵ�strA�ĳ���С��strB�ĳ����Ҵ��ڷ��޶�ģʽ��:
//      "apple"�ص���"egg"��0λ���ϣ��õ�"apple"
//    �۵�strA�ĳ���С��strB�ĳ����Ҵ����޶�ģʽ��:
//      "apple"�ص���"egg"��0λ���ϣ��õ�"app"
AsciiBasicString overlapString(const AsciiBasicString &strA,
                               const AsciiBasicString &strB, int psotion = 0,
                               bool isLimit = false);
} // namespace AsciiTools