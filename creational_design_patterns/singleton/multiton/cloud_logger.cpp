#include "cloud_logger.h"

void cloudLogger::print(const std::string &data) {
  std::cout << "[cloud-logger]" << data << std::endl;
}

cloudLogger &cloudLogger::getInstance() {
  static cloudLogger instance;
  return instance;
}
