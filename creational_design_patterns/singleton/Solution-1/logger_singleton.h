#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>

class logger {

  FILE *m_logFileStream;
  std::string tag;
  logger();
  static logger m_instace;
  /*
    assignemnet operator and copy construtor
    needs to be also private
  */
  logger &operator=(logger &) = default;
  logger(logger &) = default;

public:
  ~logger();
  static logger &getInstance();
  void add_tag(const char *);
  void append_log(const char *);
  void display_log();
};