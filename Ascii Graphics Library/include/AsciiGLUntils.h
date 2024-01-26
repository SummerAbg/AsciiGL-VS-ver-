#pragma once

#include "AsciiBasic.h"

// 分割字符串
std::vector<std::string> split(const std::string &str, char chr);

// string->int
int stringToInt(const std::string &str);
// char->int
int charToInt(char chr);
// char->bool
bool charToBool(char chr);
// int->bool
bool intToBool(int number);

// 获取字符串行数
int getStringLineCount(const std::string &str);
// 按行截取字符串(line1-line2)
std::string interceptString(const std::string &str, int line1, int line2);