#include "logger.h"
#include <thread>

using namespace std;

void worker_thread() {
  logger &worker_logger = logger::getInstance("cloud");
  worker_logger.print("cloud worker started");
}

void application_thread() {
  logger &application_logger = logger::getInstance("local");
  application_logger.print("Application started");
}

int main() {
  logger &main_logger = logger::getInstance("cloud");
  thread t1(worker_thread);
  thread t2(application_thread);
  t1.join();
  t2.join();
  main_logger.print("Done with threads");
  return 0;
}
