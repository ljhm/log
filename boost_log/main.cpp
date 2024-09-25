#include "log.h"
#include <string>

int main() {
  const std::string log_dir = "logs"; // get executable directory
  const std::string name = "foo";
  init_logging(log_dir, name);

  for (;;) { // test rotation
    LOG(trace) << "This is a trace message.";
    LOG(debug) << "This is a debug message.";
    LOG(info) << "This is an info message.";
    LOG(warning) << "This is a warning message.";
    LOG(error) << "This is an error message.";
    LOG(fatal) << "This is a fatal message.";
  }
  return 0;
}
