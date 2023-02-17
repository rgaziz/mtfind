// read_worker.h 21/08/2022
/* ========================================================================== */
#pragma once

/* ========================================================================== */
#include "service.h"

/* ========================================================================== */
class ReadWorker : public Service {
 public:
  ReadWorker(Logger &log, QueuePull &queue, std::string &file_path)
      : log_(log), queue_(queue), file_path_(file_path) {
    log_.debug(middle, "Read worker created OK");
  }

  ~ReadWorker() {}

 public:
  bool run() override;

 private:
  Logger &log_;
  QueuePull &queue_;
  std::string file_path_;
};
/* ========================================================================== */
