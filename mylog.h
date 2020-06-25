// mylog.h
// log rotation with boost log
//

/*
BLOG(trace) << "A trace severity message";
BLOG(debug) << "A debug severity message";
BLOG(info) << "An informational severity message";
BLOG(warning) << "A warning severity message";
BLOG(error) << "An error severity message";
BLOG(fatal) << "A fatal severity message";
*/

/*
0: 20181203 175935.575196 trace a.cpp:128 (main) - A trace severity message
1: 20181203 175935.575450 debug a.cpp:129 (main) - A debug severity message
2: 20181203 175935.575466 info a.cpp:130 (main) - An informational severity message
3: 20181203 175935.575473 warning a.cpp:131 (main) - A warning severity message
4: 20181203 175935.575480 error a.cpp:132 (main) - An error severity message
5: 20181203 175935.575487 fatal a.cpp:133 (main) - A fatal severity message
*/

#ifndef mylog_h
#define mylog_h

#include <string>
#include <boost/log/trivial.hpp>
namespace src = boost::log::sources;
namespace logging = boost::log;
using namespace logging::trivial;

extern src::severity_logger< severity_level > mylog;
int init_log(std::string &dir, std::string &name);

#define LOG(severity) BOOST_LOG_SEV(mylog, severity) \
    << __FILE__ << ":" << __LINE__ << " (" << __func__ << ") - "

#endif
