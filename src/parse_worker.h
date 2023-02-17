// parse_worker.h 21/08/2022
/* ========================================================================== */
#pragma once

/* ========================================================================== */
#include "service.h"

/* ========================================================================== */
class ParseWorker : public Service {
 public:
  ParseWorker(Logger &log, QueuePull &queue, std::string &search_key)
      : log_(log), queue_(queue), search_key_(search_key) {
    log_.debug(middle, "Parse worker created OK");
  }

  ~ParseWorker() {}

 public:
  bool run() override;

 private:
  Logger &log_;
  QueuePull &queue_;
  std::string search_key_;
};
/* ========================================================================== */
