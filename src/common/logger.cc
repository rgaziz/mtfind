// logger.cc   21/08/2022
/* ========================================================================== */
#include "logger.h"

/* ========================================================================== */
void Logger::info(const char* msg) {
  std::lock_guard<std::mutex> guard(log_mutex_);
  std::cout << "[INF]"
            << "(" << std::this_thread::get_id() << "): " << msg << std::endl;
}

/* ========================================================================== */
void Logger::error(const char* msg) {
  std::lock_guard<std::mutex> guard(log_mutex_);
  std::cerr << "[ERR]"
            << "(" << std::this_thread::get_id() << "): " << msg << std::endl;
}

/* ========================================================================== */
void Logger::debug(const int& level, const char* msg) {
  if (level <= log_level_) {
    std::lock_guard<std::mutex> guard(log_mutex_);
    std::cout << "[DEB]"
              << "(" << std::this_thread::get_id() << "): " << msg << std::endl;
  }
}

/* ========================================================================== */
void Logger::set_level(const int level) { log_level_ = level; }

/* ========================================================================== */
