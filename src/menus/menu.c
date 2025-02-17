#include "./menu.h"
#include "../helpers/logger.h"
#include "./menu_handlers_list.h"
#include <stdio.h>
#include <stdlib.h>

Menu *g_current_menu;
Menu g_menu_list[10] = {0};

void refresh_menu() {
  system("clear");
  get_current_menu()->display_handler();
  int sel = input_action();
  get_current_menu()->action_handler(sel);
}

void change_current_menu(enum E_menu_type new_menu_type) {
  Menu *to = get_menu(new_menu_type);
  if (to == NULL || to->display_handler == NULL) {
    error("MenuChange", "Target menu doesnt exist");
  }

  g_current_menu = to;
  refresh_menu();
}

void clear_menu() { system("clear"); }

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
  Menu admin = {admin_view, &admin_view_display, &admin_view_action_handler};
  add_menu_entry(&admin);
  Menu staff = {staff_view, &staff_view_display, &staff_view_action_handler};
  add_menu_entry(&staff);
  Menu customer = {customer_view, &customer_view_display,
                   &customer_view_action_handler};
  add_menu_entry(&customer);
  Menu guest = {guest_view, &guest_view_display, &guest_view_action_handler};
  add_menu_entry(&guest);

  g_current_menu = get_menu(sel.type);
}

void display_file_content(const char *path) {
  FILE *file = fopen(path, "r");
  if (!file) {
    error("FileDisplay", "File opening failed!");
  }

  char line[LINE_MAX] = {'\0'};

  while (fgets(line, LINE_MAX, file)) {
    printf("%s", line);
  };
}
