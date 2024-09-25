// boost log
// ../boost_1_86_0/libs/log/example/basic_usage/main.cpp ,
// ../boost_1_86_0/libs/log/example/rotating_file/main.cpp ,
// ../boost_1_86_0/libs/log/example/doc/tutorial_fmt_stream.cpp ,

// makefile:
// CPPFLAGS  = -MMD -MP -I../boost_1_86_0 -DBOOST_LOG_DYN_LINK
// LDFLAGS   = -L../boost_1_86_0/stage/lib
// LDLIBS    = -lboost_log -lboost_log_setup -lboost_chrono -lboost_filesystem
//              -lboost_thread -lboost_atomic

// environment variable:
// $ LD_LIBRARY_PATH=../boost_1_82_0/stage/lib  ./a.out

#include "log.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/attributes/named_scope.hpp>
#include <boost/log/attributes/timer.hpp>
#include <boost/log/common.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <string>

namespace attrs = boost::log::attributes;
namespace expr = boost::log::expressions;
namespace keywords = boost::log::keywords;
namespace logging = boost::log;
namespace sinks = boost::log::sinks;
namespace src = boost::log::sources;

/*
$ cat foo_20240924_220112.711990_CST.log
2024-09-24 22:01:25.084288 CST [debug  ] main.cpp:11: This is a debug message.
2024-09-24 22:01:25.084423 CST [info   ] main.cpp:12: This is an info message.
2024-09-24 22:01:25.084539 CST [warning] main.cpp:13: This is a warning message.
2024-09-24 22:01:25.084628 CST [error  ] main.cpp:14: This is an error message.
2024-09-24 22:01:25.085912 CST [fatal  ] main.cpp:15: This is a fatal message.
2024-09-24 22:01:25.086041 CST [trace  ] main.cpp:10: This is a trace message.
$
*/

std::string timezone2() {
  char str[50];
  struct tm result;
  auto clock = time(nullptr);
  auto timeptr = localtime_r(&clock, &result);
  strftime(str, sizeof(str), "%Z", timeptr);
  return str;
}

void init_logging(const std::string &log_dir, const std::string &name) {
  const std::string pattern =
      std::string("_%Y%m%d_%H%M%S.%f_") + timezone2() + ".log";
  const size_t rotation_size = 1024 * 1024 * 1;
  const size_t max_files = 5;
  const size_t min_free_space = 1024ULL * 1024 * 1024 * 10;
  const size_t severity_len = std::strlen("warning");

  auto format = expr::stream
                << expr::format_date_time<boost::posix_time::ptime>(
                       "TimeStamp", "%Y-%m-%d %H:%M:%S.%f")
                << " " << expr::attr<std::string>("Timezone2") << " ["
                << std::left << std::setw(severity_len) << std::setfill(' ')
                << logging::trivial::severity << "] " << expr::smessage;

  auto fileSink = logging::add_file_log(
      keywords::file_name = log_dir + "/" + name + pattern,
      keywords::target_file_name = name + pattern,
      keywords::rotation_size = rotation_size, // in characters
      keywords::auto_flush = true, keywords::target = log_dir,
      keywords::max_size = rotation_size * max_files, // in bytes
      keywords::min_free_space = min_free_space,      // in bytes
      keywords::max_files = max_files,
      keywords::filter = logging::trivial::severity >= logging::trivial::trace,
      keywords::format = format);

  auto consoleSink = logging::add_console_log(
      std::clog,
      keywords::filter = logging::trivial::severity >= logging::trivial::trace,
      keywords::format = format);

  logging::core::get()->add_global_attribute(
      "Timezone2", logging::attributes::make_function<std::string>(&timezone2));

  // Add common attributes like TimeStamp
  logging::add_common_attributes();
}
