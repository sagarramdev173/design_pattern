#include <cstdio>
#include <fstream>
#include <iostream>
#include <memory>
#include <mutex>
#include <string>

class logger {

  FILE *m_logFileStream;
  static std::mutex mtx;
  std::string tag;
  logger();
  /*
    lazy instance
  */
  static logger *m_instance;
  /*
    to solve the destructor problem
  */
  // inline static std::unique_ptr<logger> m_instance;
  /*
    assignemnet operator and copy construtor
    needs to be also private
  */
  logger &operator=(logger &) = delete;
  logger(logger &) = delete;

public:
  ~logger();
  static logger &getInstance();
  void add_tag(const char *);
  void append_log(const char *);
  void display_log();
};
