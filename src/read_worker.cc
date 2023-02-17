// read_worker.cc 21/08/2022
/* ========================================================================== */
#include "read_worker.h"
#include <fstream>

/* ========================================================================== */
bool ReadWorker::run() {
  std::ifstream file(file_path_);
  queue_.is_done_ = false;

  if (file.is_open()) {
    log_.debug(high, "Input data file open OK");
    uint64_t line_number{1};

    while (not file.eof()) {
      std::string line;
      std::getline(file, line);
      log_.debug(high, line.c_str());

      queue_.input_.push(std::make_pair(line_number, line));
      ++line_number;
    }
  } else {
    log_.error("Input file read failed!");
    return false;
  }

  file.close();
  queue_.is_done_ = true;

  log_.debug(high, "Input data readed from file OK");
  return true;
}

/* ========================================================================== */
