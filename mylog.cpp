/*
http://www.boost.org/doc/libs/1_56_0/libs/log/example/doc/tutorial_file.cpp
http://lists.boost.org/boost-users/att-79396/test_logging.cpp
https://github.com/boostorg/log/blob/develop/example/advanced_usage/main.cpp
https://github.com/boostorg/log/blob/develop/example/rotating_file/main.cpp
https://github.com/boostorg/log/blob/develop/example/doc/tutorial_fmt_stream_manual.cpp
*/

/*
CPPFLAGS = -MMD -MP -DNDEBUG -I../boost_1_73_0 -DBOOST_ALL_DYN_LINK
LDFLAGS  = -L../boost_1_73_0/stage/lib
LDLIBS   = -lpthread -lboost_system -lboost_log -lboost_log_setup -lboost_thread -lboost_chrono -lboost_atomic -lboost_atomic -lboost_date_time -lboost_filesystem -lboost_regex
*/

#include <boost/log/attributes.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/trivial.hpp>
namespace attrs = boost::log::attributes;
namespace expr = boost::log::expressions;
namespace keywords = boost::log::keywords;
namespace logging = boost::log;
namespace sinks = boost::log::sinks;
namespace src = boost::log::sources;
using namespace logging::trivial;
using boost::shared_ptr;
#include "mylog.h"

src::severity_logger< severity_level > mylog;

int init_log(std::string &dir, std::string &name)
{
    try
    {
        // Create a text file sink
        typedef sinks::synchronous_sink< sinks::text_file_backend > file_sink;
        shared_ptr< file_sink > sink(new file_sink(
            keywords::file_name = dir + "/" + name + "_%Y%m%d_%H%M%S_%5N.log", // file name pattern
            keywords::auto_flush = true,
            keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0), //at midnight
            keywords::rotation_size = 16 * 1024                     // rotation size, in characters
            ));

        // Set up where the rotated files will be stored
        sink->locked_backend()->set_file_collector(sinks::file::make_collector(
            keywords::target = dir //,                             // where to store rotated files
            //keywords::max_size = 16 * 1024 * 1024,              // maximum total size of the stored files, in bytes
            //keywords::min_free_space = 100 * 1024 * 1024,       // minimum free space on the drive, in bytes
            //keywords::max_files = 512                           // maximum number of stored files
            ));

        // Upon restart, scan the target directory for files matching the file_name pattern
        sink->locked_backend()->scan_for_files();

        sink->set_formatter(expr::format("%1%: %2% %3% %4%")
            % expr::attr< unsigned int >("RecordID")
            % expr::format_date_time< boost::posix_time::ptime >("TimeStamp", "%Y%m%d %H%M%S.%f")
            % logging::trivial::severity
            % expr::smessage
            );

        // Add it to the core
        logging::core::get()->add_sink(sink);

        // Add some attributes too
        logging::core::get()->add_global_attribute("RecordID", attrs::counter< unsigned int >());
        logging::core::get()->add_global_attribute("TimeStamp", attrs::local_clock());

        return 0;
    }
    catch (std::exception& e)
    {
        std::cout << "exception: " << e.what() << std::endl;
        return 1;
    }
}
