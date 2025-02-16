#include "role_selection_menu.h"
#include "../file_list.h"
#include "../helpers/logger.h"
#include "../users.h"
#include <stdio.h>

#define LINE_MAX 256

void role_selection_display() {
  FILE *sel_menu_file = fopen(FILE_SELECTION_PAGE, "r");
  if (!sel_menu_file) {
    error("UserSelection", "File opening failed!");
  }

  char line[LINE_MAX] = {'\0'};

  while (fgets(line, LINE_MAX, sel_menu_file)) {
    printf("%s", line);
  };
}

void role_selection_action_handler(int action) {
  switch (action) {
  case Guest:
    /*display_guest_menu();*/
    break;
  case Customer:
    puts("Welcome Customer!");
    break;
  case Staff:
    puts("Welcome Staff!");
    break;
  case Admin:
    puts("Welcome Admin!");
    break;
  case None:
    puts("Exiting!");
    break;
  default:
    warn("UserSelection", "Bad User Type");
    break;
  }
}
