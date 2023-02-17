// application.cc 21/08/2022
/* ========================================================================== */
#include "application.h"
#include <algorithm>

/* ========================================================================== */
bool Application::initialize() {
  try {
    int32_t thread_count = config_.get_thread_count();
    log_.debug(middle, std::to_string(thread_count).c_str());

    std::string search_key = config_.get_search_key();
    log_.debug(middle, std::string("Search key: " + search_key).c_str());

    if (search_key.size() > MAX_SEARCH_KEY_SIZE) {
      log_.error("Invalid search key");
      return false;
    }

    std::replace(search_key.begin(), search_key.end(), '?', '.');

    std::string file_path = config_.get_data_file_path();
    log_.debug(middle, std::string("File path: " + file_path).c_str());

    auto reader = std::make_shared<ReadWorker>(log_, queue_, file_path);
    add_service(reader);

    auto writer = std::make_shared<WriteWorker>(log_, queue_);
    add_service(writer);

    for (int32_t i = 0; i < thread_count; ++i) {
      auto parser = std::make_shared<ParseWorker>(log_, queue_, search_key);
      add_service(parser);
    }

    return true;

  } catch (std::exception &ex) {
    log_.error(ex.what());

  } catch (...) {
    log_.error("Initialize failed!");
  }

  return false;
}

/* ========================================================================== */
