#include "logger_singleton.h"
#include <thread>

using namespace std;

void worker_thread() {
  logger &worker_logger = logger::getInstance();
  worker_logger.add_tag("worker");
  worker_logger.append_log("worker started");
}

void application_thread() {
  logger &application_logger = logger::getInstance();
  application_logger.add_tag("app");
  application_logger.append_log("Application started");
  application_logger.display_log();
}

int main() {
  logger &main_logger = logger::getInstance();
  /*
    to fail the assigment opetor this case
    logger test_logger = main_logger;
  */
  main_logger.add_tag("MAIN");
  main_logger.append_log("starting threads");
  thread t1(worker_thread);
  thread t2(application_thread);
  t1.join();
  t2.join();
  main_logger.append_log("Done with threads");
  main_logger.display_log();
  return 0;
}
