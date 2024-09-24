#ifndef log_h
#define log_h

#include <boost/log/trivial.hpp>

// log macro
#define LOG(severity)                                                          \
  BOOST_LOG_TRIVIAL(severity) << __FILE__ << ":" << __LINE__ << ": "

void initLogging(const std::string &log_dir, const std::string &name);

#endif
