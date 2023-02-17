// write_worker.h 21/08/2022
/* ========================================================================== */
#pragma once

/* ========================================================================== */
#include "service.h"

/* ========================================================================== */
class WriteWorker : public Service {
 public:
  WriteWorker(Logger &log, QueuePull &queue) : log_(log), queue_(queue) {
    log_.debug(middle, "Write worker created OK");
  }

  ~WriteWorker() {}

 public:
  bool run() override;

 private:
  Logger &log_;
  QueuePull &queue_;
};
/* ========================================================================== */
