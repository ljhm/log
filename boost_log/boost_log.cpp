// ../boost_1_82_0/libs/log/example/rotating_file/main.cpp

// $ export LD_LIBRARY_PATH=/home/ljh/Downloads/boost_1_82_0/stage/lib

// #define BOOST_LOG_DYN_LINK 1

#include <stdexcept>
#include <string>
#include <iostream>
#include <memory>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <boost/log/common.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/core/null_deleter.hpp>

#include <iomanip>
#include <boost/format.hpp>

#include "log.h"

namespace logging = boost::log;
namespace attrs = boost::log::attributes;
// namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace expr = boost::log::expressions;
namespace keywords = boost::log::keywords;

using boost::shared_ptr;

// enum { LOG_RECORDS_TO_WRITE = 10000 };

void boost_log_init(const std::string log_dir, const std::string name) {

    // auto format = expr::format("%1%: %2%")
    //     % expr::attr< boost::posix_time::ptime >("TimeStamp")
    //     % expr::smessage;

    auto format = expr::stream
        << expr::attr<boost::posix_time::ptime>("TimeStamp")
        << " [" << std::left << std::setw(7) << std::setfill(' ') << logging::trivial::severity << "] "
        << expr::smessage;

    // auto *facet = new boost::posix_time::time_facet("%Y%m%d %H%M%S"); //
    // std::locale::global(std::locale(std::locale(), facet)); //


    // Create a text file sink
    typedef sinks::synchronous_sink< sinks::text_file_backend > file_sink;
    auto pattern = "_%Y%m%d_%H%M%S_%5N.log";
    shared_ptr< file_sink > sink(new file_sink(
        keywords::file_name = log_dir + "/" + name + pattern,   // file name pattern
        keywords::target_file_name = name + pattern,            // file name pattern
        keywords::rotation_size = 30 * 1024                     // rotation size, in characters
        ));

    // Set up where the rotated files will be stored
    sink->locked_backend()->set_file_collector(sinks::file::make_collector(
        keywords::target = log_dir,                             // where to store rotated files
        keywords::max_size = 16 * 1024 * 1024,                  // maximum total size of the stored files, in bytes
        keywords::min_free_space = 100 * 1024 * 1024,           // minimum free space on the drive, in bytes
        keywords::max_files = 7                                 // maximum number of stored files
        ));

    // Upon restart, scan the target directory for files matching the file_name pattern
    sink->locked_backend()->scan_for_files();
    sink->set_formatter(format);

    // Add it to the core
    logging::core::get()->add_sink(sink);

    // Add a console sink
    typedef sinks::synchronous_sink< sinks::text_ostream_backend > console_sink;
    shared_ptr< console_sink > consoleSink(new console_sink());
    consoleSink->locked_backend()->add_stream(boost::shared_ptr<std::ostream>(&std::clog, boost::null_deleter()));
    consoleSink->set_formatter(format);

    consoleSink->set_filter(logging::trivial::severity >= logging::trivial::trace);
    logging::core::get()->add_sink(consoleSink);

    // Add some attributes too
    logging::core::get()->add_global_attribute("TimeStamp", attrs::local_clock());
}
