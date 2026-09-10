#pragma once

#include "logger.h"

class localLogger : public logger {
private:
  localLogger() = default;

public:
  void print(const std::string &) override;
  static localLogger &getInstance();
};