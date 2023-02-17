// config_reader.cc   21/08/2022
/* ========================================================================== */
#include "config_reader.h"

/* ========================================================================== */
bool ConfigReader::read(const std::string &path) {
  log_.info("Config file read ...");

  std::ifstream file(path);
  std::string key, value;

  if (file.is_open()) {
    while (file >> key >> value) {
      if (key == kLogLevel) {
        log_level_ = static_cast<Level>(std::atoi(value.c_str()));
        log_.info("Log level readed");

      } else if (key == kThreadCount) {
        thread_count_ = static_cast<int32_t>(std::atoi(value.c_str()));
        log_.info("Thread count readed");

      } else if (key == kSearchKey) {
        search_key_ = value;
        log_.info("Search key readed");

      } else if (key == kDataFilePath) {
        data_file_path_ = value;
        log_.info("Data file path readed");
      }
    }

  } else {
    log_.error("Config file read failed!");
    return false;
  }

  file.close();
  log_.info("Config file read OK");
  return true;
}

/* ========================================================================== */
int32_t ConfigReader::get_log_level() const { return log_level_; }

/* ========================================================================== */
int32_t ConfigReader::get_thread_count() const { return thread_count_; }

/* ========================================================================== */
std::string ConfigReader::get_search_key() const { return search_key_; }

/* ========================================================================== */
std::string ConfigReader::get_data_file_path() const { return data_file_path_; }

/* ========================================================================== */
