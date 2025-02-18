#include "./menu.h"
#include "./menu_handlers_list.h"
#include "login_page.h"
#include <stdlib.h>

void role_selection_display() { display_file_content(FILE_SELECTION_PAGE); }

void role_selection_action_handler(int user_role) {
  char role_name[128];
  switch (user_role) {
  case Guest:
    change_current_menu(guest_view);
    break;
  case Customer:
  case Staff:
  case Admin:
    set_logging_user_type(user_role);
    login_display();
    break;
  case None:
    puts("Exiting!");
    exit(EXIT_SUCCESS);
    break;
  default:
    warn("UserSelection", "Bad User Type");
    exit(EXIT_SUCCESS);
    break;
  }
}
