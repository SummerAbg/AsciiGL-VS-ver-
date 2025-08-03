#pragma once

#include "at_BasicString.h"
#include <iostream>
#include <thread>
#include <windows.h>

namespace AsciiTools {
void debug_log(const std::string &str);

// Ч�ʵ���
class EfficiencyDebug {
public:
  EfficiencyDebug() { start_time = GetTickCount64(); }
  ~EfficiencyDebug() {
    end_time = GetTickCount64();
    debug_log("����Ϊ" + std::to_string(end_time - start_time) + "ms");
  }

private:
  ULONGLONG start_time;
  ULONGLONG end_time;
};

void WinAPIText(COORD coord, const std::string &str);
} // namespace AsciiTools