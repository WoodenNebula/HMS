#include "./menu.h"
#include "./menu_handlers_list.h"

void role_selection_display() { display_file_content(FILE_SELECTION_PAGE); }

void role_selection_action_handler(int action) {
  switch (action) {
  case Guest:
    change_current_menu(guest_view);
    break;
  case Customer:
    change_current_menu(customer_view);
    break;
  case Staff:
    change_current_menu(staff_view);
    break;
  case Admin:
    change_current_menu(admin_view);
    break;
  case None:
    puts("Exiting!");
    break;
  default:
    warn("UserSelection", "Bad User Type");
    break;
  }
}
