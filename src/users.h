#pragma once
#include <stdbool.h>

enum E_user_role { Admin = 1, Staff, Customer, Guest, None };

enum E_user_fields { f_name = 1, l_name, role, usr_name, pwd };

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

void get_user_field_name(char *o_buff, enum E_user_fields field);
void get_user_role_name(char *o_buff, enum E_user_role role);
void user_data_print_all_fields();
void user_data_modify_field(S_user_data *data_to_modify,
                            enum E_user_fields field);

S_user_data prompt_user_details();
S_user_data get_user_data(const char *username);

void print_user_data(const S_user_data *data);
void print_all_user_data();

/// modify user data with old user name as user_name
bool modify_user_data(const S_user_data *new_data, const char *user_name);

void register_user_data(const S_user_data *data);
