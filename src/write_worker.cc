// write_worker.cc 21/08/2022
/* ========================================================================== */
#include "write_worker.h"
#include <fstream>

/* ========================================================================== */
bool WriteWorker::run() {
  std::ofstream file(output_file);
  uint64_t total_count{0};

  if (file.is_open()) {
    log_.debug(high, "Output data file open OK");

    file << std::endl << std::endl;

    while (is_running()) {
      if (queue_.is_done_ and queue_.input_.is_empty() and
          queue_.output_.is_empty()) {
        break;
      }

      auto result = queue_.output_.pop();
      if (result == std::nullopt) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        continue;

      } else {
        ++total_count;
        file << *result << std::endl;
      }
    }

  } else {
    log_.error("Output file write failed!");
    return false;
  }

  file.seekp(0);
  file << total_count << std::endl;

  file.close();

  log_.debug(high, "Output data written OK");
  shutdown_application();
  return true;
}

/* ========================================================================== */
