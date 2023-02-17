// parse_worker.cc 21/08/2022
/* ========================================================================== */
#include "parse_worker.h"
#include <regex>

/* ========================================================================== */
bool ParseWorker::run() {
  while (is_running()) {
    if (queue_.is_done_ and queue_.input_.is_empty() and
        queue_.output_.is_empty()) {
      break;
    }

    auto result = queue_.input_.pop();
    if (result == std::nullopt) {
      std::this_thread::sleep_for(std::chrono::seconds(1));
      continue;

    } else {
      if (search_key_.empty()) {
        log_.error("Invalid search key");
        return false;
      }

      auto[line_number, str] = *result;
      log_.debug(high, str.c_str());

      if (std::smatch smatch;
          std::regex_search(str, smatch, std::regex(search_key_))) {
        std::stringstream ss;
        log_.debug(high, smatch[0].str().c_str());

        ss << line_number << " " << smatch.prefix().length() << " "
           << smatch[0];

        queue_.output_.push(ss.str());
      }
    }
  }

  log_.debug(high, "Parse process finished");
  return true;
}

/* ========================================================================== */
