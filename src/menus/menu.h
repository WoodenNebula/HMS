#pragma once
#include <stdbool.h>

enum E_menu_type { selection, login };

typedef struct {
  enum E_menu_type type;
  void (*display_handler)();
  void (*action_handler)(int);
} Menu;

// functions that may be called by user
void menu_init();
void refresh_menu();

// internal implementations
Menu *get_current_menu();
Menu *get_menu(enum E_menu_type type);

bool add_menu_entry(Menu *menu);

int input_action();
