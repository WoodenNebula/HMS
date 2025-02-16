
#include "./menu.h"
#include "menu_handlers_list.h"

void staff_view_display() { display_file_content(FILE_STAFF_VIEW); }
void staff_view_action_handler(int action) {
  switch (action) {
  default:
    change_current_menu(selection);
    break;
  }
}
