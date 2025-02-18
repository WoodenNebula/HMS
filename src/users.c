#include "./users.h"
#include "file_list.h"
#include "helpers/logger.h"
#include <stdio.h>
#include <string.h>

void get_user_role_name(char *o_buff, enum E_user_role role) {
  switch (role) {
  case Admin:
    strcpy(o_buff, "Admin");
    break;
  case Staff:
    strcpy(o_buff, "Staff");
    break;
  case Customer:
    strcpy(o_buff, "Customer");
    break;
  case Guest:
    strcpy(o_buff, "Guest");
    break;
  case None:
  default:
    o_buff = NULL;
    break;
  }
}

S_user_data prompt_user_details() {
  S_user_data data = {0};

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

bool modify_user_data(const S_user_data *new_data, const char *user_name) {
  FILE *data_file = fopen(FILE_DATA_USERS, "r");
  if (!data_file) {
    error("UserDataRetrieval", "File opening failed!");
  }

  char *copy_file_path = "./copy.txt";
  FILE *copy = fopen(copy_file_path, "w");
  if (!copy) {
    error("UserDataRetrieval", "File opening failed!");
  }

  S_user_data old_data;
  bool success = false;
  while (fread(&old_data, sizeof(S_user_data), 1, data_file)) {

    if (strcmp(old_data.creds.user_name, user_name) == 0) {
      fwrite(new_data, sizeof(S_user_data), 1, copy);
      success = true;
      // skip copying for modified data
      continue;
    }
    // copy contents to new copy file
    fwrite(&old_data, sizeof(S_user_data), 1, copy);
  }

  fclose(copy);
  fclose(data_file);

  if (success) {
    remove(FILE_DATA_USERS);
    rename(copy_file_path, FILE_DATA_USERS);
  } else {
    remove(copy_file_path);
  }

  return success;
}

S_user_data get_user_details(const char *username) {
  FILE *data_file = fopen(FILE_DATA_USERS, "r");
  if (!data_file) {
    error("UserDataRetrieval", "File opening failed!");
  }

  S_user_data data;
  while (fread(&data, sizeof(S_user_data), 1, data_file)) {
    if (strcmp(data.creds.user_name, username) == 0) {
      fclose(data_file);
      return data;
    }
  }

  notify("UserDataRetrieval", "NO USER WITH THAT USERNAME FOUND");
  data.role = -1;
  fclose(data_file);
  return data;
}

void print_user_data(const S_user_data *data) {
  if (data == NULL) {
    error("UsrRegister", "NULL DATA SENT");
  }

  printf("1. First name: %s\n", data->first_name);
  printf("2. Last name: %s\n", data->last_name);
  char role_name[32];
  get_user_role_name(role_name, data->role);
  printf("3. Role: %s\n", role_name);
  printf("4. Username: %s\n", data->creds.user_name);
  printf("5. Password: %s\n", data->creds.password);
}

void print_all_user_data() {
  FILE *data_file = fopen(FILE_DATA_USERS, "r");
  if (!data_file) {
    error("UserDataRetrieval", "File opening failed!");
  }

  S_user_data data;
  while (fread(&data, sizeof(S_user_data), 1, data_file)) {
    print_user_data(&data);
    puts("----");
  }
  fclose(data_file);
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
  fclose(data_file);
}
