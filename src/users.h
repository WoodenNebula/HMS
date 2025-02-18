#pragma once
#include <stdbool.h>

enum E_user_role { Admin = 1, Staff, Customer, Guest, None };

void get_user_role_name(char *o_buff, enum E_user_role role);

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
void print_all_user_data();

/// modify user data with old user name as user_name
bool modify_user_data(const S_user_data *new_data, const char *user_name);

void register_user_data(const S_user_data *data);
