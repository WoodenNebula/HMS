#pragma once

#include "menus/menu.h"
#include <stdbool.h>

#define LINE_MAX 256

typedef struct {
  int num;
  int price;
  bool is_available;
  char detail[LINE_MAX];
} S_room_data;

void print_all_available_rooms();
void print_room_data(const S_room_data *data);
void print_all_room_data();

S_room_data prompt_room_details();
S_room_data get_room_data(int room_num);

bool modify_room_data(const S_room_data *new_data, int room_num);
void register_room_data(const S_room_data *data);
