#include "./guest_menu.h"

#include "../file_list.h"
#include "../helpers/logger.h"
#include <stdio.h>
#include <stdlib.h>

#define LINE_MAX 256

void guest_menu_display() {
  FILE *guest_menu_file = fopen(FILE_GUEST_PAGE, "r");
  if (!guest_menu_file) {
    error("UserSelection", "File opening failed!");
  }

  char line[LINE_MAX] = {'\0'};

  system("clear");
  while (fgets(line, LINE_MAX, guest_menu_file)) {
    printf("%s", line);
  };
}
