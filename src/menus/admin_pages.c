#include "./menu.h"
#include "menu_handlers_list.h"

// the order should strictly match as what occurs in the file
enum E_admin_menu_choices {
  register_user = 1,
  manage_user,
  register_room,
  manage_room
};

void handle_register_user() {
  clear_menu();
  printf("registering user\n");
  S_user_data data = prompt_user_details();
  register_user_data(&data);
}

enum E_manage_user_fields { f_name = 1, l_name, role, usr_name, pwd };
void handle_manage_user() {
  clear_menu();
  print_all_user_data();

  char user_name[32];
  printf("Enter user_name to change detail for: ");
  scanf("%s", user_name);
  S_user_data data = get_user_details(user_name);

  // no data for the given user
  if (data.role == -1) {
    return;
  }

  clear_menu();
  puts("Chose which field to manage for the data:\n");
  print_user_data(&data);
  int action = input_action();
  S_user_data new_data = data;

  switch (action) {
  case f_name:
    printf("Enter new first name: ");
    scanf("%s", new_data.first_name);
    break;

  case l_name:
    printf("Enter new last name: ");
    scanf("%s", new_data.last_name);
    break;

  case role:
    printf("Select new user role\n");
    puts("1. Admin");
    puts("2. Staff");
    puts("3. Customer");
    int role = 3;
    scanf("%d", &role);

    if (role == Admin || role == Staff || role == Customer) {
      new_data.role = role;
    } else {
      warn("UsrRegister", "Invalid Role, defaulting to customer");
      new_data.role = Customer;
    }
    break;

  case usr_name:
    printf("Enter new username: ");
    scanf("%s", new_data.creds.user_name);
    break;

  case pwd:
    printf("Enter new password: ");
    scanf("%s", new_data.creds.password);
    break;
  }

  bool success = modify_user_data(&new_data, data.creds.user_name);
  if (success) {
    notify("UserDataModification", "Success");
  } else {
    notify("UserDataModification", "Failed");
  }
}

void handle_register_room() {
  clear_menu();
  S_room_data data = prompt_room_details();
  register_room_data(&data);
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
    refresh_menu();
    break;
  case manage_user:
    handle_manage_user();
    refresh_menu();
    break;
  case register_room:
    handle_register_room();
    refresh_menu();
    break;
  case manage_room:
    handle_manage_room();
    refresh_menu();
    break;
  default:
    change_current_menu(selection);
    break;
  }
}
