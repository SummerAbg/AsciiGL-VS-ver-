#pragma once

#include "AsciiBasicString.h"
#include <iostream>
#include <thread>
#include <windows.h>

void debug_log(const std::string &str) {
  AsciiBasicString log({"debug:" + str}, false, ASCII_WORD_COLOR_MAGENTA);
  std::cout << log << std::endl;
}

// 效率调试
class EfficiencyDebug {
public:
  EfficiencyDebug() { start_time = GetTickCount64(); }
  ~EfficiencyDebug() {
    end_time = GetTickCount64();
    debug_log("测速为" + std::to_string(end_time - start_time) + "ms");
  }

private:
  ULONGLONG start_time;
  ULONGLONG end_time;
};

void WinAPIText(COORD coord, const std::string &str) {

  HANDLE hndl = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleCursorPosition(hndl, coord);

  std::cout << "                    ";

  SetConsoleCursorPosition(hndl, coord);
  std::cout << str;
}