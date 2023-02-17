// application.h 21/08/2022
/* ========================================================================== */
#pragma once

/* ========================================================================== */
#include "daemon.h"
#include "parse_worker.h"
#include "read_worker.h"
#include "write_worker.h"

/* ========================================================================== */
class Application : public Daemonizer {
 public:
  Application(const int argc, const char** argv) : Daemonizer(argc, argv) {}
  ~Application() {}

 private:
  bool initialize() override;

 private:
  QueuePull queue_;
};
/* ========================================================================== */
