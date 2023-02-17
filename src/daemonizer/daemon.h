// daemon.h 21/08/2022
/* ========================================================================== */
#pragma once

/* ========================================================================== */
#include <memory>
#include <vector>
#include "config_reader.h"
#include "logger.h"
#include "service.h"

/* ========================================================================== */
using Services = std::vector<std::shared_ptr<Service>>;

/* ========================================================================== */
class Daemonizer {
 public:
  Daemonizer(const int argc, const char** argv);
  virtual ~Daemonizer();

 public:
  void add_service(const std::shared_ptr<Service>& service);
  virtual bool initialize() = 0;
  bool run();

 private:
  bool parse_arguments(const int argc, const char** argv);
  void register_signals();
  bool start_services();
  bool stop_services();

 private:
  bool is_demonize_{true};
  std::string config_file_path_;

 protected:
  Logger log_;
  ConfigReader config_;

 private:
  Services services_;
};

/* ========================================================================== */
