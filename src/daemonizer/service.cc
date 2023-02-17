// service.cc 21/08/2022
/* ========================================================================== */
#include "service.h"
#include <csignal>

/* ========================================================================== */
bool Service::is_running() const { return is_running_; }

/* ========================================================================== */
void Service::start() {
  std::lock_guard<std::mutex> lock(mutex_);

  if (th_.joinable()) {
    throw std::runtime_error("Service is already running");
  }

  th_ = std::thread(&Service::run, this);
  is_running_ = true;
}

/* ========================================================================== */
void Service::stop() {
  is_running_ = false;
  join();
}

/* ========================================================================== */
void Service::detach() {
  std::lock_guard<std::mutex> lock(mutex_);

  if (th_.joinable()) {
    th_.detach();
  }
}

/* ========================================================================== */
void Service::join() {
  std::lock_guard<std::mutex> lock(mutex_);

  if (th_.joinable()) {
    th_.join();
  }
}

/* ========================================================================== */
void Service::shutdown_application() {
  static std::once_flag flag;
  std::call_once(flag, []() { std::raise(SIGTERM); });
}

/* ========================================================================== */
