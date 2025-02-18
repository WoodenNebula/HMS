
#include "./menu.h"
#include "menu_handlers_list.h"
#include <stdbool.h>

void handle_staff_book() {
  clear_menu();

  // chose room to book
  puts("Chose a room to book:");
  print_all_available_rooms(true);
  int room_num;
  printf("RoomNo.: ");
  scanf("%d", &room_num);
  S_room_data room_data = get_room_data(room_num);
  if (room_data.num == -1) {
    warn("StaffBooking", "Invalid Room No.");
    pause();
    return;
  }

  clear_menu();

  // chose user to book for
  puts("Chose a user to book the room for:");
  print_all_user_data();
  char user_name[LINE_MAX];
  printf("User: ");
  scanf(" %s", user_name);
  S_user_data user_data = get_user_data(user_name);
  if (user_data.role == -1) {
    warn("StaffBooking", "Invalid user name");
    pause();
    return;
  }

  clear_menu();

  bool success = reserve_room(room_data.num, user_name);
  if (success) {
    notify("StaffBooking", "Success");
  } else {
    notify("StaffBooking", "Failed");
  }
  pause();
}

void handle_staff_unbook() {
  clear_menu();

  // chose room to book
  puts("Chose a room to unbook:");
  print_all_room_data(true);
  int room_num;
  printf("RoomNo.: ");
  scanf("%d", &room_num);
  S_room_data room_data = get_room_data(room_num);
  if (room_data.num == -1) {
    warn("StaffBooking", "Invalid Room No.");
    pause();
    return;
  }

  clear_menu();

  bool success = unreserve_room(room_data.num, room_data.booked_by);
  if (success) {
    notify("StaffUnBooking", "Success");
  } else {
    notify("StaffUnBooking", "Failed");
  }
  pause();
}

void handle_staff_view_room() {
  clear_menu();
  print_all_room_data(true);
  pause();
}

void handle_view_booking_history() {
  clear_menu();
  FILE *data_file = fopen(FILE_BOOKING_HISTORY, "r");
  if (!data_file) {
    error("StaffView", "History file open failed");
  }

  puts("---- Booking History ----");
  char line[LINE_MAX];
  while (fgets(line, LINE_MAX, data_file)) {
    puts(line);
  }
  puts("---- ----");
  fclose(data_file);

  pause();
}

enum E_staff_choices {
  book = 1,
  unbook,
  check_in,
  check_out,
  view_rooms,
  view_booking_history
};
void staff_view_display() { display_file_content(FILE_STAFF_VIEW); }
void staff_view_action_handler(int action) {
  switch (action) {
  case book:
    handle_staff_book();
    refresh_menu();
    break;
  case unbook:
    handle_staff_unbook();
    refresh_menu();
    break;
  case view_rooms:
    handle_staff_view_room();
    refresh_menu();
    break;
  case view_booking_history:
    handle_view_booking_history();
    refresh_menu();
    break;
  default:
    change_current_menu(selection);
    break;
  }
}
