#pragma once

#include "logger.h"

class cloudLogger : public logger {
private:
  cloudLogger() = default;

public:
  void print(const std::string &) override;
  static cloudLogger &getInstance();
};