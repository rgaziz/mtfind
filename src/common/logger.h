// logger.h   21/08/2022
/* ========================================================================== */
#pragma once

/* ========================================================================== */
#include <iostream>
#include <mutex>
#include <thread>

/* ========================================================================== */
enum Level { low = 10, middle = 50, high = 100 };

/* ========================================================================== */
class Logger {
 public:
  Logger() {}
  ~Logger() {}

 public:
  void info(const char* msg);
  void error(const char* msg);
  void debug(const int& level, const char* msg);

  void set_level(const int level);

 private:
  std::mutex log_mutex_;
  int log_level_{Level::low};
};
/* ========================================================================== */
