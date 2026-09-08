#include "logger_singleton.h"
#include <cstdio>
#include <cstdlib>

using namespace std;
logger *logger::m_instance = nullptr;
std::mutex logger::mtx;
logger &logger::getInstance() {
  
  // Double check locking pattern
  if (m_instance == nullptr) {
    mtx.lock();
    if (m_instance == nullptr) {
      // if unqiue pointer apprach has been used
      // m_instance.reset(new logger{});
      m_instance = new logger{};
    }
    mtx.unlock();
  }
  return *m_instance;
}
logger::logger() {
#ifdef DEBUG
  cout << "Constructor called\n" << endl;
#endif
  if (m_logFileStream == nullptr)
    m_logFileStream = fopen("dummy_log.txt", "w+");
  atexit([]() { delete m_instance; });
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
