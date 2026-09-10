#include "Base_template.h"
#include <cstdio>
#include <fstream>
#include <iostream>
#include <memory>
#include <mutex>
#include <string>

class logger : public BaseSingleton<logger> {

  FILE *m_logFileStream;
  std::string tag;
  MAKESINGLETON(logger);

public:
  ~logger();
  void add_tag(const char *);
  void append_log(const char *);
  void display_log();
};
