#include "logger.h"
#include "cloud_logger.h"
#include "local_logger.h"
#include <stdexcept>
#include <string>

logger &logger::getInstance(const std::string &key) {
  if (key == "cloud") {
    return cloudLogger::getInstance();
  } else if (key == "local") {
    return localLogger::getInstance();
  }

  throw std::invalid_argument("unkown logger type");
}