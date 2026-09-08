#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>

class logger {

  FILE *m_logFileStream;
  std::string tag;

public:
  logger();
  ~logger();
  void add_tag(const char *);
  void append_log(const char *);
  void display_log();
};