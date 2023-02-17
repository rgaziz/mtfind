// service.h 21/08/2022
/* ========================================================================== */
#pragma once

/* ========================================================================== */
#include <atomic>
#include <mutex>
#include <thread>
#include "logger.h"
#include "settings.h"

/* ========================================================================== */
class Service {
 public:
  explicit Service() : is_running_(false) {}
  virtual ~Service() {}

  Service(const Service &) = delete;
  Service &operator=(const Service &) = delete;

 public:
  void detach();
  void start();
  void stop();
  void join();
  void shutdown_application();

 protected:
  bool is_running() const;
  virtual bool run() = 0;

 private:
  std::thread th_;
  std::mutex mutex_;
  std::atomic_bool is_running_;
};

/* ========================================================================== */
