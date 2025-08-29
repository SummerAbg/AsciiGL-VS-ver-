#pragma once

#include "at_debug.h"
#include <atomic>
#include <functional>
#include <string>
#include <thread>
#include <vector>

namespace AsciiTools {
class Work {
public:
  std::string label;
  std::unique_ptr<std::function<void()>> work;
  std::atomic<double> delta_t = 0.0;
  int frequence = 0;

  Work() { this->work = std::make_unique<std::function<void()>>(); }
  Work(const std::string &label, const std::function<void()> &callback,
       int freq)
      : label(label), frequence(freq) {
    this->work = std::make_unique<std::function<void()>>(callback);
  }

  Work(const Work &work) {
    this->label = work.label;
    this->frequence = work.frequence;
    this->work = std::make_unique<std::function<void()>>();
    *this->work = *work.work;
  }
};

struct Task {
  std::string label;
  std::shared_ptr<std::thread> task;

  Task(const std::string &label, const std::shared_ptr<std::thread> &task)
      : label(label), task(task) {}

  Task(const Task &task) : label(label), task(task.task) {}

  Task(Task &&task) noexcept {
    this->label = task.label;
    this->task = std::move(task.task);
    task.task = nullptr;
  }
};

// 用于检测线程状态
class ThreadDetector {
public:
  using Works = std::vector<Work>;
  using pWorks = std::shared_ptr<Works>;
  using Tasks = std::vector<Task>;
  using pTasks = std::shared_ptr<Tasks>;
  using Function = std::function<void()>;

  ThreadDetector() {
    this->tasks = std::make_shared<Tasks>();
    this->works = std::make_shared<Works>();
  }

  void append(const Work &work) { this->works->push_back(work); }
  void append(Work &&work) noexcept { this->works->emplace_back(work); }
  void append(const std::string &label, const Function &callback, int freq) {
    this->works->emplace_back(label, callback, freq);
  }

  void execute() {
    for (auto &index : *works) {
      Task task(index.label, std::make_shared<std::thread>([&]() {
                  update(*index.work, index.delta_t, index.frequence);
                }));
      tasks->emplace_back(std::move(task));
    }
  }

  void join() {
    for (auto &index : *tasks) {
      index.task->join();
    }
  }

  const pTasks &getTasks() const { return tasks; }
  const pWorks &getWorks() const { return works; }

private:
  void update(const Function &behavior, std::atomic<double> &delta_t,
              int freq) {
    std::atomic<double> logic_time;
    while (1) {
      TimeMeasurer get_delta_time(&delta_t);
      {
        TimeMeasurer timer(&logic_time);
        behavior();
      }
      dynamicDelay(logic_time.load(), freq);
    }
  }

  void dynamicDelay(double delta_t, int fps_target) const {
    if (fps_target == 0)
      return;

    const double delta_t_target = static_cast<double>(1.0 / fps_target);
    const double delta_t_sleep =
        (delta_t >= delta_t_target) ? 0.0 : delta_t_target - delta_t;
    std::this_thread::sleep_for(std::chrono::duration<double>(delta_t_sleep));
  }

private:
  pTasks tasks;
  pWorks works;
};
} // namespace AsciiTools