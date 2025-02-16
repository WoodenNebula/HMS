#include "./logger.h"
#include "./ANSI_color_codes.h"
#include <stdio.h>

void error(const char *error_from_module, const char *error_msg) {
  printf("%s[ERROR]-(%s): %s%s\n", BHRED, error_from_module, error_msg, CRESET);
  // crash incase of error
#ifdef DEBUG
  printf("%d", 5 / 0);
#endif /* ifdef DEBUG */
}

void warn(const char *warn_from_module, const char *warn_msg) {
  printf("%s[WARN]-(%s): %s%s\n", BHYEL, warn_from_module, warn_msg, CRESET);
}

void notify(const char *notify_from_module, const char *msg) {
  printf("%s[NOTIFY]-(%s): %s%s\n", HWHT, notify_from_module, msg, CRESET);
}
