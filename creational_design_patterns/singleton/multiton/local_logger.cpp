#include "local_logger.h"

void localLogger::print(const std::string &data) {
  std::cout << "[local-logger]" << data << std::endl;
}

localLogger &localLogger::getInstance() {
  static localLogger instance;
  return instance;
}
