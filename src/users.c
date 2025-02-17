#include "./users.h"
#include "file_list.h"
#include "helpers/logger.h"
#include <stdio.h>
#include <string.h>

S_user_data prompt_user_details() {
  S_user_data data;

  printf("Enter first name: ");
  scanf("%s", data.first_name);

  printf("Enter last name: ");
  scanf("%s", data.last_name);

  printf("Select user role\n");
  puts("1. Admin");
  puts("2. Staff");
  puts("3. Customer");
  int role = 3;
  scanf("%d", &role);

  if (role == Admin || role == Staff || role == Customer) {
    data.role = role;
  } else {
    warn("UsrRegister", "Invalid Role, defaulting to customer");
    data.role = Customer;
  }

  printf("Enter username: ");
  scanf("%s", data.creds.user_name);
  printf("Enter password: ");
  scanf("%s", data.creds.password);

  return data;
}

S_user_data get_user_details(const char *username) {
  FILE *data_file = fopen(FILE_DATA_USERS, "r");
  if (!data_file) {
    error("UserDataRetrieval", "File opening failed!");
  }

  S_user_data data;
  while (fread(&data, sizeof(S_user_data), 1, data_file)) {
    if (strcmp(data.creds.user_name, username) == 0) {
      return data;
    }
  }

  notify("UserDataRetrieval", "NO USER WITH THAT USERNAME FOUND");
  data.role = -1;
  return data;
}

void print_user_data(const S_user_data *data) {
  if (data == NULL) {
    error("UsrRegister", "NULL DATA SENT");
  }

  printf("First name: %s\n", data->first_name);
  printf("Last name: %s\n", data->last_name);

  switch (data->role) {
  case Admin:
    puts("Role: Admin");
    break;
  case Staff:
    puts("Role: Staff");
    break;
  case Customer:
    puts("Role: Customer");
    break;
  default:
    break;
  }

  printf("Username: %s\n", data->creds.user_name);
  printf("Password: %s\n", data->creds.password);
}

void register_user_data(const S_user_data *user_data) {
  if (user_data == NULL) {
    error("UsrRegister", "NULL DATA SENT");
  }
  FILE *data_file = fopen(FILE_DATA_USERS, "a");
  if (!data_file) {
    error("UsrRegister", "File opening failed!");
  }
  fwrite(user_data, sizeof *user_data, 1, data_file);

  puts("Successfully registered user");
}
