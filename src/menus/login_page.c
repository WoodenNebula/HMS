#include "login_page.h"
#include "../file_list.h"
#include "../helpers/logger.h"
#include "menu.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum E_user_role g_logging_user_type = None;

void set_logging_user_type(enum E_user_role user_type) {
  g_logging_user_type = user_type;
}

bool validate_user_creds(enum E_user_role user_role, S_user_creds creds) {
  FILE *data_file = fopen(FILE_DATA_USERS, "r");
  if (!data_file) {
    error("UserCredValidation", "File opening failed!");
  }

  S_user_data data;
  while (fread(&data, sizeof(S_user_data), 1, data_file)) {
    if (data.role != user_role) {
      // keep searching if role hasnt matched
      continue;
    }
    // role matched, check for username
    if (strcmp(data.creds.user_name, creds.user_name) == 0) {
      // username matched, check password
      if (strcmp(data.creds.password, creds.password) == 0) {
        notify("CredsValidation", "Validation success!");
        set_logged_in_user(data.creds.user_name);
        return true;
      }
      // password didnt match so stop looping and return
      fclose(data_file);
      notify("CredsValidation",
             "Validation failed! Usrname or Password invalid");
      return false;
    }
    // username didnt match, keep searching
  }

  // eof reached, not validated
  fclose(data_file);
  notify("CredsValidation", "Validation failed! Usrname or Password invalid");
  set_logged_in_user(NULL);
  return false;
}

bool prompt_credentials() {
  S_user_creds creds;
  printf("Username: ");
  scanf("%s", creds.user_name);
  printf("Password: ");
  scanf("%s", creds.password);
  return validate_user_creds(g_logging_user_type, creds);
}

void login_display() {
  char *name = "\0";
  enum E_menu_type menu_to_display_on_success = selection;
  switch (g_logging_user_type) {
  case Customer:
    name = "Customer\0";
    menu_to_display_on_success = customer_view;
    break;
  case Staff:
    name = "Staff\0";
    menu_to_display_on_success = staff_view;
    break;
  case Admin:
    name = "Admin\0";
    S_user_data default_admin = get_user_data("admin");
    if (default_admin.role == -1) {
      strcpy(default_admin.first_name, "admin");
      strcpy(default_admin.last_name, "admin");
      default_admin.role = Admin;
      strcpy(default_admin.creds.user_name, "admin");
      strcpy(default_admin.creds.password, "admin");

      register_user_data(&default_admin);
    } else if (strcmp(default_admin.creds.user_name, "admin") != 0 ||
               strcmp(default_admin.creds.password, "admin") != 0 ||
               default_admin.role != Admin) {
      S_user_data admin = default_admin;
      strcpy(admin.first_name, "admin");
      strcpy(admin.last_name, "admin");
      admin.role = Admin;
      strcpy(admin.creds.user_name, "admin");
      strcpy(admin.creds.password, "admin");

      modify_user_data(&admin, default_admin.creds.user_name);
    }
    menu_to_display_on_success = admin_view;
    break;
  case None:
  default:
    warn("LoginPage", "Bad User Type");
    break;
  }

  clear_menu();
  printf("---- Login (%s) ----\n", name);
  bool validation_success = prompt_credentials();

  while (!validation_success) {
    printf("\nInvalid username or password!\n");
    printf("Press 1 to retry or anything else to go back\n");
    int action;
    scanf("%d", &action);

    if (action != 1) {
      g_logging_user_type = None;
      change_current_menu(selection);
    }

    validation_success = prompt_credentials();
  }

  change_current_menu(menu_to_display_on_success);
}
