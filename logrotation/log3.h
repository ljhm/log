#include <cstdio>
#include <ctime>
#include <string>

// 1. print log

// ---

// log with printf, va args,

// ##__VA_ARGS__ is used to handle cases where __VA_ARGS__ might be empty.
// It ensures that if there are no arguments passed after fmt,
// the comma before __VA_ARGS__ is removed during macro expansion.

// LOG1,
// ##__VA_ARGS__ , is gnu extension

// LOG1("%s", ""); // print empty string
// LOG1(); // ok,

#define LOG1(fmt, ...)                                                         \
  do {                                                                         \
    fprintf(stdout, "%s:%d: " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__);    \
  } while (0)

// LOG2,
// __VA_ARGS__ , without ##, is more portable

// LOG2("%s", ""); // always with arguments, print empty string
// LOG2(); // no,

#define LOG2(fmt, ...)                                                         \
  do {                                                                         \
    fprintf(stdout, "%s:%d: " fmt "\n", __FILE__, __LINE__, __VA_ARGS__);      \
  } while (0)

int main() {
  LOG1("%s, %f", "abc", 3.14);
  LOG1("%s", ""); // print empty string
  LOG1();         // ok,

  LOG2("%s, %f", "abc", 3.14);
  LOG2("%s", ""); // always with arguments, print empty string
  // LOG2(); // no, because no ## before __VA_ARGS__ in LOG2, but this is more
  // portable

  return 0;
}

// ---

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
//      postscript
//          kill -HUP myapp
//      postscript
// }
// $
// $ sudo logrotate /etc/logrotate.d/mylogrotate.conf
//

// 4. in myapp, the handle the HUP signal:
//  // signal HUP handler:
//      reopen the file
//      fclose(fp);
//      fp=fopen(path)

// 5. systemd timer (instead of crontab)
//

// 6. systemd service (start service at reboot)
//
