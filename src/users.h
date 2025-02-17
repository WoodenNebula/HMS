#pragma once

enum E_user_role { Admin = 1, Staff, Customer, Guest, None };

typedef struct {
  char user_name[128];
  char password[32];
} S_user_creds;

typedef struct {
  char first_name[128];
  char last_name[128];
  enum E_user_role role;
  S_user_creds creds;
} S_user_data;

S_user_data prompt_user_details();
S_user_data get_user_details(const char *username);
void print_user_data(const S_user_data *data);

void register_user_data(const S_user_data *data);
