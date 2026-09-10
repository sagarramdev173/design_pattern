#pragma once

#include <iostream>

class logger {

protected:
  logger() = default;

public:
  logger(const logger &) = delete;
  logger &operator=(const logger &) = delete;
  virtual ~logger() = default;
  virtual void print(const std::string &data) = 0;
  static logger &getInstance(const std::string &key);
};