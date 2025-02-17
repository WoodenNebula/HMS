#include "./menu.h"
#include "menu_handlers_list.h"

enum E_admin_menu_choices { register_user = 1, manage_user, manage_room };

void handle_register_user() {
  clear_menu();
  printf("registering user\n");
  S_user_data data = prompt_user_details();
  register_user_data(&data);
}

void handle_manage_user() {
  clear_menu();
  char user_name[32];
  printf("Enter user_name to change detail for: ");
  scanf("%s", user_name);
  S_user_data data = get_user_details(user_name);

  if (data.role != -1) {
    print_user_data(&data);
  }
}

void handle_manage_room() {
  clear_menu();
  printf("Manage room");
}

void admin_view_display() { display_file_content(FILE_ADMIN_VIEW); }
void admin_view_action_handler(int choice) {
  switch (choice) {
  case register_user:
    handle_register_user();
    break;
  case manage_user:
    handle_manage_user();
    break;
  case manage_room:
    handle_manage_room();
    break;
  default:
    change_current_menu(selection);
    break;
  }
}
