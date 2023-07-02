#ifndef NDEBUG
#include <sanitizer/lsan_interface.h>
#endif
#include <signal.h>

// signal(SIGCONT, handlerCont); // kill -CONT 123 # pid
void handlerCont(int signum) {
  // printf("SIGCONT %d\n", signum);
#ifndef NDEBUG
  __lsan_do_recoverable_leak_check();
#endif
}

#include "foo.h"

#include <cstdio>
#include <string>
#include <ctime>

#define LOG2(fmt, ...) \
do { \
  char str[26]; \
  time_t now = time(nullptr); \
  strftime(str, sizeof(str), "%Y-%m-%d %H:%M:%S %z", \
    localtime(&now)); \
  fprintf(stdout, "%s  %s:%d]  " fmt "\n", \
    str, __FILE__, __LINE__, ##__VA_ARGS__); \
} while (0)


#include "log.h"

auto main() -> int {

  boost_log_init("logs", "foo");

  for (;;){

    LOG(trace) << "trace msg!";
    LOG(debug) << "debug msg!";
    LOG(info) << "info msg!";
    LOG(warning) << "warning msg!";
    LOG(error) << "error msg!";
    LOG(fatal) << "fatal msg!";
    LOG(info) << "---";
  }

  return 0;

}
