#pragma once

#include "at_BasicChar.h"

namespace AsciiTools {
// �����ַ�����
class AsciiBasicString : public AsciiBasicObject {
public:
  using Text = std::vector<AsciiBasicChar>;
  using pText = std::unique_ptr<Text>;

  // ��������ַ���
  AsciiBasicString();
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
  AsciiBasicString(const AsciiBasicString &str);
  AsciiBasicString(AsciiBasicString &&str) noexcept;

  // �����Ϣ
  void info() const override;
  // AsciiBasicStringת��Ϊstd::string
  std::string toString() const override;

  // ��ȡͷβ��ַ�ĺ���(Ϊ���ܹ�ʹ��c++11��������)
  auto begin() const { return text->begin(); }
  auto end() const { return text->end(); }

  // ���������
  bool operator==(const AsciiBasicString &str) const;

  bool operator!=(const AsciiBasicString &str) const;

  AsciiBasicString &operator+=(const AsciiBasicString &str);
  AsciiBasicString &operator+=(AsciiBasicString &&str) noexcept;

  AsciiBasicString &operator+=(const AsciiBasicChar &chr);

  AsciiBasicString operator+(const AsciiBasicString &str) const;
  AsciiBasicString operator+(const AsciiBasicChar &chr) const;

  AsciiBasicChar &operator[](int index);
  const AsciiBasicChar &operator[](int index) const;

  AsciiBasicString &operator=(const AsciiBasicString &str);
  AsciiBasicString &operator=(AsciiBasicString &&str) noexcept;

  /////////////////////////////////////////////////////////////

  // ��ָ��λ�ò����ַ�/�ַ���
  // void insert(int index, const AsciiBasicString &str);
  // void insert(int index, const AsciiBasicChar &chr);

  // ɾ���ַ���ָ��λ�õ��ַ�
  void del(int index);
  // ���ַ�����ĩβ����ַ�
  void append(const AsciiBasicChar &chr);
  void append(AsciiBasicChar &&chr) noexcept;

  void append(const AsciiBasicString &str);
  void append(AsciiBasicString &&str) noexcept;

  // ����ַ���
  void clear();

  // ��ȡ�ַ�����С
  int size() const { return static_cast<int>(text->size()); }

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
  std::string getSerializeStr() const override;
  void loadSerializeStr(const std::string &str) override;

private:
  pText text; // �ַ�����
};

const AsciiBasicString TRPRSTR = {
    "  ", true, {ASCII_COLOR_GREY, ASCII_COLOR_BLACK}};

// ��ȡ����Ӧ�ַ���
AsciiBasicString getAdaptiveStr(const AsciiBasicChar &chr);

// �����ַ���(��ȡindexλ�ü�֮ǰ���ַ���)
AsciiBasicString cutText(const AsciiBasicString &str, int index);

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
AsciiBasicString overlapText(const AsciiBasicString &str_a,
                             const AsciiBasicString &str_b, int psotion = 0,
                             bool is_limit = false);
} // namespace AsciiTools