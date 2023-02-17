// daemon.cc 21/08/2022
/* ========================================================================== */
#include "daemon.h"
#include <unistd.h>
#include <csignal>
#include <iostream>

/* ========================================================================== */
static bool stop_signal = false;

/* ========================================================================== */
void handle_signal(int signal) {
  std::cout << "Signal: " << signal << std::endl;
  stop_signal = true;
}

/* ========================================================================== */
bool print_help() {
  std::cerr << "\nStart example:       ./Module -n conf_file_name.conf \n\n";
  std::cerr << "[-h]                  Display this help and exit \n";
  std::cerr << "[-n]                  Start without demonize this program \n";

  return false;
}

/* ========================================================================== */
bool Daemonizer::parse_arguments(const int argc, const char **argv) {
  log_.info("Parse arguments ...");

  int opt = 0;

  while ((opt = ::getopt(argc, const_cast<char **>(argv), "n")) not_eq -1) {
    if (opt == 'n') {
      is_demonize_ = false;
      continue;
    }

    return print_help();
  }

  if (optind >= argc) {
    return print_help();
  }

  config_file_path_ = argv[optind];

  log_.info("Parse arguments OK");
  return true;
}

/* ========================================================================== */
Daemonizer::Daemonizer(const int argc, const char **argv) {
  if (not parse_arguments(argc, argv)) {
    std::exit(EXIT_FAILURE);
  }

  if (not config_.read(config_file_path_)) {
    std::exit(EXIT_FAILURE);
  }

  log_.set_level(config_.get_log_level());
}

/* ========================================================================== */
Daemonizer::~Daemonizer() { stop_services(); }

/* ========================================================================== */
void Daemonizer::add_service(const std::shared_ptr<Service> &service) {
  services_.emplace_back(service);
}

/* ========================================================================== */
void Daemonizer::register_signals() {
  log_.info("Register signals ...");

  struct sigaction sig_action;
  sig_action.sa_handler = handle_signal;
  ::sigemptyset(&sig_action.sa_mask);
  sig_action.sa_flags = SA_RESTART;

  if (::sigaction(SIGINT, &sig_action, nullptr) < 0) {
    std::exit(EXIT_FAILURE);
  }

  if (::sigaction(SIGTERM, &sig_action, nullptr) < 0) {
    std::exit(EXIT_FAILURE);
  }

  if (::sigaction(SIGABRT, &sig_action, nullptr) < 0) {
    std::exit(EXIT_FAILURE);
  }

  log_.info("Register signals OK");
}

/* ========================================================================== */
bool Daemonizer::start_services() {
  log_.info("Start services ...");

  if (services_.empty()) {
    return false;
  }

  for (const auto &service : services_) {
    service->start();
  }

  log_.info("Start services OK");
  return true;
}

/* ========================================================================== */
bool Daemonizer::stop_services() {
  log_.info("Stop services ...");

  if (services_.empty()) {
    return false;
  }

  for (const auto &service : services_) {
    service->stop();
  }

  log_.info("Start services OK");
  return true;
}

/* ========================================================================== */
bool Daemonizer::run() {
  if (is_demonize_) {
    if (not daemon(0, 0)) {
      log_.error("Demonize failed!");
      return false;
    }
  }

  if (not initialize()) {
    log_.error("Initialise failed!");
    return false;
  }

  register_signals();

  if (not start_services()) {
    log_.error("Start services failed!");
    return false;
  }

  while (not stop_signal) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }

  if (not stop_services()) {
    log_.error("Stop services failed!");
    return false;
  }

  log_.info("Done");
  return true;
}

/* ========================================================================== */
