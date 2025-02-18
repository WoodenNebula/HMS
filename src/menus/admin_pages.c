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

void handle_manage_user() {
  clear_menu();

  print_all_user_data();
  printf("\nEnter user_name to change detail for: ");
  char user_name[32];
  scanf("%s", user_name);

  S_user_data data = get_user_data(user_name);
  // no data for the given user
  if (data.role == -1) {
    return;
  }

  clear_menu();

  print_user_data(&data);

  puts("Chose which field to manage for the data:\n");
  user_data_print_all_fields();

  int action = input_action();
  S_user_data new_data = data;
  user_data_modify_field(&new_data, action);

  bool success = modify_user_data(&new_data, data.creds.user_name);
  if (success) {
    notify("UserDataModification", "Success");
  } else {
    notify("UserDataModification", "Failed");
  }
  pause();
}

void handle_register_room() {
  clear_menu();
  S_room_data data = prompt_room_details();
  register_room_data(&data);
}

void handle_manage_room() {
  clear_menu();

  print_all_room_data(true);
  int room_num;
  printf("Enter room_num to change detail for: ");
  scanf("%d", &room_num);

  S_room_data room_data = get_room_data(room_num);
  if (room_data.num == -1) {
    return;
  }

  clear_menu();

  print_room_data(&room_data, true);

  puts("Chose which field to manage for the data:\n");
  room_data_print_all_fields();

  int action = input_action();
  S_room_data new_data = room_data;
  room_data_modify_field(&new_data, action);

  bool success = modify_room_data(&new_data, room_num);
  if (success) {
    notify("RoomDataModification", "Success");
  } else {
    notify("RoomDataModification", "Failed");
  }
  pause();
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
