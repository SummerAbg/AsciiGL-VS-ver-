#pragma once

#include "AsciiBasic.h"

// �ָ��ַ���
std::vector<std::string> split(const std::string &str, char chr);

// string->int
int stringToInt(const std::string &str);
// char->int
int charToInt(char chr);
// char->bool
bool charToBool(char chr);
// int->bool
bool intToBool(int number);

// ��ȡ�ַ�������
int getStringLineCount(const std::string &str);
// ���н�ȡ�ַ���(line1-line2)
std::string interceptString(const std::string &str, int line1, int line2);