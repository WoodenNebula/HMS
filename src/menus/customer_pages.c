#include "../rooms.h"
#include "./menu.h"
#include "menu_handlers_list.h"
#include <stdio.h>

void handle_book() {
  char user_name[LINE_MAX];
  get_logged_in_user(user_name);
  int room;
  clear_menu();
  puts("Chose a room to book: ");
  print_all_available_rooms(false);
  printf("RoomNo. to book: ");
  scanf("%d", &room);
  bool success = reserve_room(room, user_name);
  if (success) {
    notify("CustomerBooking", "Booking success");
  } else {
    notify("CustomerBooking", "Booking failed");
  }

  puts("\nPress any key to continue");
  // one getchar consumes the previous \n char and another normal input
  getchar();
  getchar();
}

void handle_unbook() {
  char user_name[LINE_MAX];
  get_logged_in_user(user_name);

  clear_menu();
  S_room_data room = find_room_booked_by(user_name);
  if (room.num == -1) {
    puts("You haven't reserved any room!");
  }

  bool success = unreserve_room(room.num, user_name);
  if (success) {
    notify("CustomerBooking", "Unbooking success");
  } else {
    notify("CustomerBooking", "Unbooking failed");
  }

  puts("\nPress any key to continue");
  // one getchar consumes the previous \n char and another normal input
  getchar();
  getchar();
}

void handle_view_room() {
  char user_name[LINE_MAX];
  get_logged_in_user(user_name);

  clear_menu();
  S_room_data room = find_room_booked_by(user_name);
  if (room.num == -1) {
    puts("You haven't reserved any room!");
  } else {
    print_room_data(&room, true);
  }
  puts("\nPress any key to continue");
  // one getchar consumes the previous \n char and another normal input
  getchar();
  getchar();
}
enum E_customer_choices { book = 1, unbook, view_rooms };

void customer_view_display() { display_file_content(FILE_CUSTOMER_VIEW); }
void customer_view_action_handler(int action) {

  switch (action) {
  case book:
    handle_book();
    refresh_menu();
  case unbook:
    handle_unbook();
    refresh_menu();
  case view_rooms:
    handle_view_room();
    refresh_menu();
  default:
    change_current_menu(selection);
    break;
  }
}
