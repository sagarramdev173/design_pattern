#include "logger_singleton.h"
#include <cstdio>

using namespace std;
logger::logger() : m_logFileStream(fopen("dummy_log.txt", "w+")) {
#ifdef DEBUG
  cout << "Constructor called\n" << endl;
#endif
}

logger::~logger() {
#ifdef DEBUG
  cout << "Destructor called\n" << endl;
#endif
  fclose(m_logFileStream);
}

void logger::append_log(const char *pMessage) {
#ifdef DEBUG
  cout << "append_log called\n" << endl;
#endif
  fprintf(m_logFileStream, "[%s] %s\n", tag.c_str(), pMessage);
  fflush(m_logFileStream);
}

void logger::add_tag(const char *pTag) {
#ifdef DEBUG
  cout << "add_tag called\n" << endl;
#endif
  tag = pTag;
}

void logger::display_log() {
  fflush(m_logFileStream);
  rewind(m_logFileStream);
  char line[256];
  while (fgets(line, sizeof(line), m_logFileStream)) {
    cout << line;
  }
}
