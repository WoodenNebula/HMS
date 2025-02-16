#include "./menu.h"
#include "menu_handlers_list.h"

void admin_view_display() { display_file_content(FILE_ADMIN_VIEW); }
void admin_view_action_handler(int action) {
  switch (action) {
  default:
    change_current_menu(selection);
    break;
  }
}
