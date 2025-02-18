#pragma once

#include "menus/menu.h"
#include "users.h"
#include <stdbool.h>
#include <string.h>

#define LINE_MAX 256

enum E_room_fields {
  room_num = 1,
  room_price,
  room_status,
  room_booked_by,
  room_details
};

typedef struct {
  int num;
  int price;
  bool is_available;
  char booked_by[LINE_MAX];
  char detail[LINE_MAX];
} S_room_data;

void get_room_field_name(char *o_buff, enum E_room_fields role);
void room_data_print_all_fields();
void room_data_modify_field(S_room_data *data_to_modify,
                            enum E_room_fields field);

void print_all_available_rooms(bool hasBookingViewAuthority);
void print_room_data(const S_room_data *data, bool hasBookingViewAuthority);
void print_all_room_data(bool hasBookingViewAuthority);

S_room_data prompt_room_details();
S_room_data get_room_data(int room_num);
S_room_data find_room_booked_by(const char *usr_name);

bool reserve_room(int room_num, const char *reserver_usrname);
bool unreserve_room(int room_num, const char *unreserver_usrname);

bool modify_room_data(const S_room_data *new_data, int room_num);
void register_room_data(const S_room_data *data);

void update_booking_history(int room_num, bool isBooked, const char *booked_by);
