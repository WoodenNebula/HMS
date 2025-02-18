#include "../rooms.h"
#include "./menu.h"
#include "./menu_handlers_list.h"
#include <stdio.h>

void guest_view_display() { display_file_content(FILE_GUEST_VIEW); }
void guest_view_action_handler(int action) {
  if (action == 1) {
    clear_menu();
    print_all_room_data(false);
    puts("\nPress any key to go back");
    // one getchar consumes the previous \n char and another normal input
    getchar();
    getchar();
    refresh_menu();
  } else if (action == 2) {
    clear_menu();
    print_all_available_rooms(false);
    puts("\nPress any key to go back");
    // one getchar consumes the previous \n char and another normal input
    getchar();
    getchar();
    refresh_menu();
  }

  change_current_menu(selection);
}
