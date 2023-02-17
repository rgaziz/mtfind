// config_reader.h   21/08/2022
/* ========================================================================== */
#pragma once

/* ========================================================================== */
#include <fstream>
#include <map>
#include "logger.h"
#include "settings.h"

/* ========================================================================== */
class ConfigReader {
 public:
  ConfigReader() {}
  ~ConfigReader() {}

 public:
  bool read(const std::string &path_);

  int32_t get_log_level() const;
  int32_t get_thread_count() const;
  std::string get_search_key() const;
  std::string get_data_file_path() const;

 private:
  Logger log_;

  Level log_level_{low};
  int32_t thread_count_{1};

  std::string search_key_;
  std::string data_file_path_;
};
/* ========================================================================== */
