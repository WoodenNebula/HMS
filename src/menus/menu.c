#include "menu.h"
#include "../helpers/logger.h"
#include "./role_selection_menu.h"
#include <stdio.h>

Menu *g_current_menu;
Menu g_menu_list[10] = {0};

void refresh_menu() {
  get_current_menu()->display_handler();
  int sel = input_action();
  get_current_menu()->action_handler(sel);
}

Menu *get_current_menu() {
  if (g_current_menu == NULL || g_current_menu->display_handler == NULL) {
    error("MenuRetrival", "Empty current menu");
  }
  return g_current_menu;
}

Menu *get_menu(enum E_menu_type type) {
  if (type >= 10) {
    error("MenuRetrival", "Trying to retrieve menu outside bounds");
    return NULL;
  }
  return &g_menu_list[type];
}

bool add_menu_entry(Menu *menu) {
  if (menu == NULL) {
    warn("MenuEntry", "Empty entry");
    return false;
  }

  if (get_menu(menu->type)->display_handler != NULL) {
    warn("MenuEntry", "Entry already exists");
    return false;
  }

  g_menu_list[menu->type] = *menu;
  notify("MenuEntry", "Successfully added menu");
  return true;
}

int input_action() {
  int sel = -1;
  scanf("%d", &sel);
  return sel;
}

void menu_init() {
  Menu sel = {selection, &role_selection_display,
              &role_selection_action_handler};
  add_menu_entry(&sel);
  g_current_menu = get_menu(sel.type);
}
