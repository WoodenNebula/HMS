#include "./menu.h"
#include "./menu_handlers_list.h"

void guest_view_display() { display_file_content(FILE_GUEST_VIEW); }
void guest_view_action_handler(int action) {
  switch (action) {
  default:
    change_current_menu(selection);
    break;
  }
}
