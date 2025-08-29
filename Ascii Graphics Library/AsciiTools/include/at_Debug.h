#pragma once

#include "at_string.h"
#include <chrono>
#include <iostream>
#include <thread>
#include <windows.h>

namespace AsciiTools {
void debug_log(const std::string &str);

// 效率调试
class EfficiencyDebug {
public:
  using TimePoint = std::chrono::steady_clock::time_point;

  EfficiencyDebug() { start_t = std::chrono::high_resolution_clock::now(); }
  ~EfficiencyDebug() {
    end_t = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> delta_t = end_t - start_t;
    debug_log("测速为" + std::to_string(delta_t.count()) + "ms");
  }

private:
  TimePoint start_t;
  TimePoint end_t;
};

// 时间测量类
class TimeMeasurer {
public:
  using Time_point = std::chrono::steady_clock::time_point;

  TimeMeasurer(std::atomic<double> *delta_time) {
    this->delta_time = delta_time;
    this->start_t = std::chrono::high_resolution_clock::now();
  }

  ~TimeMeasurer() {
    end_t = std::chrono::high_resolution_clock::now();
    const std::chrono::duration<double> delta_t = end_t - start_t;
    (*delta_time).store(delta_t.count());
  }

private:
  Time_point start_t;
  Time_point end_t;
  std::atomic<double> *delta_time;
};

void winApiText(const COORD &coord, const std::string &str);
} // namespace AsciiTools