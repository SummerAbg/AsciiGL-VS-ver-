#pragma once

#include "AsciiBasicChar.h"

// �����ַ�����
class AsciiBasicString : public AsciiBasicObject {
public:
  using TrprData = std::vector<bool>;
  using DataType = std::vector<AsciiBasicChar>;

  // ��������ַ���
  AsciiBasicString() {}
  AsciiBasicString(const char *str, const TrprData &trprData);
  AsciiBasicString(const char *str, bool isTrpr = false);
  AsciiBasicString(const std::string &str, const TrprData &trprData);
  AsciiBasicString(const std::string &str, bool isTrpr = false);
  AsciiBasicString(const AsciiBasicChar &chr);
  // �����Ϣ
  void info() const;

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
  void add(const AsciiBasicChar &chr) { text.push_back(chr); }

  // AsciiBasicStringת��Ϊstd::string
  std::string toString() const;

  // ��ȡ�ַ�����С
  int size() const { return text.size(); }

  // ��ȡ͸������
  TrprData getTrprData() const;

  // ������������
  friend std::ostream &operator<<(std::ostream &output,
                                  const AsciiBasicString &str);
  // �������������
  friend std::istream &operator>>(std::istream &input, AsciiBasicString &str);

private:
  std::string getSerializeStr() const;
  void loadSerializeStr(const std::string &str);

private:
  DataType text; // �ַ�����
};

const AsciiBasicString TRPRSTR = {"  ", true};