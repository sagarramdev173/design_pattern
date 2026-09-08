#include <cstdio>
#include <fstream>
#include <iostream>
#include <mutex>
#include <string>

class logger {

  FILE *m_logFileStream;
  static std::mutex mtx;
  std::string tag;
  logger();
  /*
    Eager instance
    static logger m_instace;
   */

  /*
    lazy instance
  */
  static logger *m_instace;
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
