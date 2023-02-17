// settings.cc 23/08/2022
/* ========================================================================== */
#pragma once

/* ========================================================================== */
#include "safe_queue.h"

/* ========================================================================== */
const int32_t MAX_SEARCH_KEY_SIZE = 100;

/* ========================================================================== */
static const std::string kLogLevel = "log_level";
static const std::string kSearchKey = "search_key";
static const std::string kThreadCount = "thread_count";
static const std::string kDataFilePath = "data_file_path";

/* ========================================================================== */
static const std::string output_file = "output.txt";

/* ========================================================================== */
struct QueuePull {
  SafeQueue<std::pair<int, std::string>> input_;
  SafeQueue<std::string> output_;

  bool is_done_{false};
};

/* ========================================================================== */
