#ifndef log_h
#define log_h

#include <string>
#include <boost/log/trivial.hpp>

// Andrey Semashev, 2016
// https://stackoverflow.com/questions/35895199/boost-log-and-severity-local-attributes/35919119#35919119
// #define LOG(lg, sev) \
//     BOOST_LOG_SEV(lg, sev) << "[" << __FILE__ << ":" << __LINE__ << "]: "

#define LOG(severity) \
    BOOST_LOG_TRIVIAL(severity) << __FILE__ << ":" << __LINE__ << ": "

void boost_log_init(const std::string log_dir, const std::string name);

#endif
