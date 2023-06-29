#include <cstdio>
#include <string>
#include <ctime>

// 1. print log

#define LOG(fmt, ...) \
do { \
  char str[26]; \
  time_t now = time(NULL); \
  strftime(str, sizeof(str), "%Y-%m-%d %H:%M:%S %z", \
    localtime(&now)); \
  fprintf(stdout, "%s  %s:%d]  " fmt "\n", \
    str, __FILE__, __LINE__, ##__VA_ARGS__); \
} while (0)

/*
auto main() -> int {

  for(;;){
    LOG("stdout %d %f", 123, 3.14);
    LOG("hello");
    LOG("");
    LOG();
  }

  return 0;

}
*/


//
// 2. redirection
//
// $ ( cd /home/ljh/src/build/main/; ./main      | tee -a foo.log )
// $ ( cd /home/ljh/src/build/main/; ./main 2>&1 | tee -a foo.log )
// $ tail -f foo.log
// 2023-06-29 08:45:59 -0400  main.cpp:53]  123 3.140000
// 2023-06-29 08:45:59 -0400  main.cpp:54]  hello
// 2023-06-29 08:45:59 -0400  main.cpp:56]
// $

// 3. logrotate
//
// $ sudo vi /etc/logrotate.d/mylogrotate.conf
//   /home/ljh/src/build/main/foo.log {
//     size 100M
//     rotate 7
//     dateext
//     create root root
// }
// $
// $ sudo logrotate -d /etc/logrotate.d/mylogrotate.conf


// 4. systemd timer (instead of crontab)

// 5. systemd service (start service at reboot)
//
