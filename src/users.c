#include "./users.h"
#include "file_list.h"
#include "helpers/logger.h"
#include <stdio.h>
#include <string.h>
#define LINE_MAX 256

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

void get_user_field_name(char *o_buff, enum E_user_fields field) {
  switch (field) {
  case f_name:
    strcpy(o_buff, "First Name");
    break;
  case l_name:
    strcpy(o_buff, "Last Name");
    break;
  case role:
    strcpy(o_buff, "Role");
    break;
  case usr_name:
    strcpy(o_buff, "UserName");
    break;
  case pwd:
    strcpy(o_buff, "Pwd");
    break;
  default:
    o_buff = NULL;
    break;
  }
}

void user_data_print_all_fields() {
  char field_name[LINE_MAX];
  for (int i = f_name; i <= pwd; i++) {
    get_user_field_name(field_name, i);
    printf("%d. %s \t ", i, field_name);
  }
  puts("");
}

void user_data_modify_field(S_user_data *data_to_modify,
                            enum E_user_fields field) {

  if (data_to_modify == NULL) {
    error("UserDataModify", "NULL DATA PASSED");
  }
  switch (field) {
  case f_name:
    printf("Enter new first name: ");
    scanf("%s", data_to_modify->first_name);
    break;

  case l_name:
    printf("Enter new last name: ");
    scanf("%s", data_to_modify->last_name);
    break;

  case role:
    printf("Select new user role\n");
    puts("1. Admin");
    puts("2. Staff");
    puts("3. Customer");
    int role = 3;
    scanf("%d", &role);

    if (role == Admin || role == Staff || role == Customer) {
      data_to_modify->role = role;
    } else {
      warn("UsrRegister", "Invalid Role, defaulting to customer");
      data_to_modify->role = Customer;
    }
    break;

  case usr_name:
    printf("Enter new username: ");
    scanf("%s", data_to_modify->creds.user_name);
    break;

  case pwd:
    printf("Enter new password: ");
    scanf("%s", data_to_modify->creds.password);
    break;
  default:
    error("UserDataModify", "BAD FIELD SELECTION");
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

S_user_data get_user_data(const char *username) {
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

  char role_name[32];
  get_user_role_name(role_name, data->role);
  printf("First name: %s \t ", data->first_name);
  printf("Last name: %s \t ", data->last_name);
  printf("Role: %s \t ", role_name);
  printf("Username: %s \t ", data->creds.user_name);
  printf("Password: %s \n ", data->creds.password);
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
