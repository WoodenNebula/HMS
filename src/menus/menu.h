#pragma once
#include <stdbool.h>

enum E_menu_type {
  selection,
  login,
  admin_view,
  staff_view,
  customer_view,
  guest_view,
};

typedef struct {
  enum E_menu_type type;
  void (*display_handler)();
  void (*action_handler)(int);
} Menu;

// functions that may be called by from outside
void menu_init();
void refresh_menu();
void change_current_menu(enum E_menu_type new_menu_type);

void display_file_content(const char *path);

// internal implementations
Menu *get_current_menu();
Menu *get_menu(enum E_menu_type type);

bool add_menu_entry(Menu *menu);

int input_action();
