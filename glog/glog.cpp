
/*
$ cd glog # google glog library
$ mkdir build && cd build
$ cmake ..
$ make
$ make install # no need to install


glog/docs/flags.md:

If the Google gflags is installed, you pass flags on the command line:

  $ ./your_application --logtostderr=1

If the Google gflags isn't installed, you set flags via environment variables,
prefixing the flag name with `GLOG_`:

  $ GLOG_logtostderr=1 ./your_application


Most commonly flags:

  `log_dir` (`string`, default="")


Modifying flags programmatically:

  FLAGS_log_dir = "/some/log/directory";
  google::InitGoogleLogging("glog");
  LOG(INFO) << "the same file";


Makefile:

  CXXFLAGS += -std=c++2a
  CPPFLAGS += -DGLOG_USE_GLOG_EXPORT
  CPPFLAGS += -I/path/glog/src
  CPPFLAGS += -I/path/glog/build
  LDFLAGS  += -L/path/glog/build
  LDLIBS   += -lglog


.vscode/settings.json:

  "clangd.fallbackFlags": [
    "-std=c++2a",
    "-I/path/glog/src",
    "-I/path/glog/build",
    "-DGLOG_USE_GLOG_EXPORT",
  ],


Test:

# provide log_dir using environment variable:
  $ LD_LIBRARY_PATH=/path/glog/build  GLOG_log_dir=/path/log_dir  ./hello


Error:

  <glog/logging.h> was not included correctly.
  Add this in Makefile: CPPFLAGS += -DGLOG_USE_GLOG_EXPORT

*/

#include <glog/logging.h>

int main() {

  // FLAGS_alsologtostderr = true; // all levels to stderr, default: ERROR
  FLAGS_colorlogtostderr = true;
  // FLAGS_log_dir = "./log"; // default: /tmp
  FLAGS_max_log_size = 5; // in MB, for test
  FLAGS_stop_logging_if_full_disk = true;
  google::InitGoogleLogging("glog");

  // for (;;) {
  LOG(INFO) << "INFO!";
  LOG(WARNING) << "WARNING!";
  LOG(ERROR) << "ERROR!";
  // LOG(FATAL) << "FATAL!"; // it will exit
  // }

  return 0;
}

// I0327 11:17:12.963464  4355 main.cpp:9] INFO!
// W0327 11:17:12.963878  4355 main.cpp:10] WARNING!
// E0327 11:17:12.964049  4355 main.cpp:11] ERROR!
// F0327 11:17:12.964191  4355 main.cpp:12] FATAL!

/*

glog.INFO -> glog.fedora.ljh.log.INFO.20240828-163951.18007
glog.WARNING -> glog.fedora.ljh.log.WARNING.20240828-163955.18007
glog.ERROR -> glog.fedora.ljh.log.ERROR.20240828-163942.18007

glog.fedora.ljh.log.INFO.20240828-163951.18007
glog.fedora.ljh.log.WARNING.20240828-163955.18007
glog.fedora.ljh.log.ERROR.20240828-163942.18007

*/

#include <glog/logging.h>

int f() {
  // std::cout << "test\n";
  return 0;
}
