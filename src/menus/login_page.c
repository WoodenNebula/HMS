#include "login_page.h"
#include "../helpers/logger.h"
#include "menu.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

enum E_user_role g_logging_user_type = None;

void set_logging_user_type(enum E_user_role user_type) {
  g_logging_user_type = user_type;
}

bool validate_user_creds(enum E_user_role user_role, S_user_creds creds) {
  if (true) {
    notify("CredsValidation", "Validation success!");
    return true;
  } else {
    notify("CredsValidation", "Validation failed!");
    return false;
  }
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
    menu_to_display_on_success = admin_view;
    break;
  case None:
  default:
    warn("LoginPage", "Bad User Type");
    break;
  }

  system("clear");
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
