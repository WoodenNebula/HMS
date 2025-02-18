#include "./rooms.h"
#include "./file_list.h"
#include "./helpers/logger.h"
#include "users.h"
#include <stdio.h>
#include <string.h>
#include <strings.h>

void get_room_field_name(char *o_buff, enum E_room_fields role) {
  switch (role) {
  case room_num:
    strcpy(o_buff, "Room No.");
    break;
  case room_price:
    strcpy(o_buff, "Price");
    break;
  case room_status:
    strcpy(o_buff, "Status");
    break;
  case room_booked_by:
    strcpy(o_buff, "Booked by");
    break;
  case room_details:
    strcpy(o_buff, "Details");
    break;
  default:
    o_buff = NULL;
    break;
  }
}

void room_data_print_all_fields() {
  char field_name[LINE_MAX];
  for (int i = room_num; i <= room_details; i++) {
    get_room_field_name(field_name, i);
    printf("%d. %s \t ", i, field_name);
  }
  puts("");
}

void room_data_modify_field(S_room_data *data_to_modify,
                            enum E_room_fields field) {
  if (data_to_modify == NULL) {
    error("RoomDataModify", "NULL DATA PASSED");
  }

  switch (field) {
  case room_num:
    printf("Enter new Room Num: ");
    scanf("%d", &(data_to_modify->num));
    break;
  case room_price:
    printf("Enter new price: ");
    scanf("%d", &(data_to_modify->price));
    break;
  case room_status:
    printf(
        "Enter new availability status (0 for Not Available, anything else for "
        "Available): ");
    int status;
    scanf("%d", &status);
    if (status != 0) {
      data_to_modify->is_available = true;
      strncpy(data_to_modify->booked_by, "None", LINE_MAX);
      break;
    } else {
      data_to_modify->is_available = false;
    }
  case room_booked_by:
    printf("\nAvailable Users:\n");
    print_all_user_data();
    printf("Enter new booker's username:");
    char usr_name[LINE_MAX];
    scanf("%s", usr_name);

    // if new usr is none (to unset) then
    // try unset previous user's booking aka checkout if possible
    if (strcasecmp(usr_name, "None") == 0) {
      S_user_data usr_data = get_user_data(data_to_modify->booked_by);
      // if prev user is valid, check him out
      if (usr_data.role != -1) {
        puts("Checking out prev user");
        /*user_check_in(data_to_modify->booked_by, false);*/
      }

      data_to_modify->is_available = true;
      strncpy(data_to_modify->booked_by, "None", LINE_MAX);
    }
    // new user is some user which may or may not exist
    else {
      // validate the new user exists
      S_user_data usr_data = get_user_data(usr_name);
      if (usr_data.role == -1) {
        // new user doesnt exist, so set it to none
        data_to_modify->is_available = true;
        strncpy(data_to_modify->booked_by, "None", LINE_MAX);
        notify("RoomDataModify",
               "Bad New booking user, setting booker to none");
        break;
      }

      // new user does exist, reserve the room for him
      data_to_modify->is_available = false;
      strncpy(data_to_modify->booked_by, usr_name, LINE_MAX);
    }
    break;
  case room_details:
    printf("Enter new room details: ");
    scanf(" %[^\n]s", data_to_modify->detail);
    break;
  default:
    error("RoomDataModify", "BAD FIELD SELECTION");
  }
}

bool modify_room_data(const S_room_data *new_data, int room_num) {
  FILE *data_file = fopen(FILE_DATA_ROOMS, "r");
  if (!data_file) {
    error("roomDataRetrieval", "File opening failed!");
  }

  char *copy_file_path = "./copy.txt";
  FILE *copy = fopen(copy_file_path, "w");
  if (!copy) {
    error("roomDataRetrieval", "File opening failed!");
  }

  S_room_data old_data;
  bool success = false;
  while (fread(&old_data, sizeof(S_room_data), 1, data_file)) {

    if (old_data.num == room_num) {
      fwrite(new_data, sizeof(S_room_data), 1, copy);
      success = true;
      // skip copying for modified data
      continue;
    }
    // copy contents to new copy file
    fwrite(&old_data, sizeof(S_room_data), 1, copy);
  }

  fclose(copy);
  fclose(data_file);

  if (success) {
    remove(FILE_DATA_ROOMS);
    rename(copy_file_path, FILE_DATA_ROOMS);
  } else {
    remove(copy_file_path);
  }

  return success;
}

S_room_data get_room_data(int room_num) {
  FILE *data_file = fopen(FILE_DATA_ROOMS, "r");
  if (!data_file) {
    error("roomDataRetrieval", "File opening failed!");
  }

  S_room_data data;
  while (fread(&data, sizeof(S_room_data), 1, data_file)) {
    if (data.num == room_num) {
      fclose(data_file);
      return data;
    }
  }

  notify("RoomDataRetrieval", "NO ROOM WITH THAT ROOM_NUM FOUND");
  data.num = -1;
  fclose(data_file);
  return data;
}

S_room_data prompt_room_details() {
  S_room_data data;
  printf("Enter Room Num: ");
  scanf("%d", &data.num);

  printf("Enter price: ");
  scanf("%d", &data.price);

  data.is_available = true;
  memset(data.booked_by, '\0', sizeof(data.booked_by));
  strcpy(data.booked_by, "None");

  printf("Enter room details: ");
  scanf(" %[^\n]s", data.detail);

  return data;
}

bool internal_can_room_be_reserved(const S_room_data *room_data,
                                   const S_user_data *user_data) {
  if (room_data == NULL || room_data->num == -1) {
    notify("RoomReservation", "Room doesnt exist!");
    return false;
  }
  if (!room_data->is_available) {
    notify("RoomReservation", "Room is already booked!");
    return false;
  }

  if (user_data == NULL || user_data->role == -1) {
    notify("RoomReservation", "Reserving user doesnt exist");
    return false;
  }

  return true;
}

bool reserve_room(int room_num, const char *reserver_usrname) {
  S_room_data room = get_room_data(room_num);
  S_user_data user = get_user_data(reserver_usrname);

  bool can_reserve = internal_can_room_be_reserved(&room, &user);
  if (!can_reserve) {
    return false;
  }

  room.is_available = false;
  strncpy(room.booked_by, reserver_usrname, LINE_MAX);

  modify_room_data(&room, room.num);
  update_booking_history(room.num, true, user.creds.user_name);

  return true;
}
bool unreserve_room(int room_num, const char *unreserver_usrname) {
  S_room_data room = get_room_data(room_num);

  if (room.num == -1) {
    notify("RoomUnreservation", "Room doesnt exist!");
    return false;
  }
  if (room.is_available) {
    notify("RoomUnreservation", "Room is unreserved!");
    return false;
  }
  if (strcmp(room.booked_by, unreserver_usrname) != 0) {
    notify("RoomUnreservation", "Room is reserved by someone else!");
    return false;
  }

  room.is_available = true;
  strncpy(room.booked_by, "None", LINE_MAX);

  modify_room_data(&room, room.num);
  update_booking_history(room.num, false, unreserver_usrname);

  return true;
}

S_room_data find_room_booked_by(const char *usr_name) {
  FILE *data_file = fopen(FILE_DATA_ROOMS, "r");
  if (!data_file) {
    error("RoomDataRetrieval", "File opening failed!");
  }

  S_room_data data;
  while (fread(&data, sizeof(S_room_data), 1, data_file)) {
    // skip unbooked rooms
    if (data.is_available) {
      continue;
    }

    if (strcmp(data.booked_by, usr_name) == 0) {
      fclose(data_file);
      return data;
    }
  }
  fclose(data_file);
  data.num = -1;
  return data;
}

void update_booking_history(int room_num, bool isBooked,
                            const char *booked_by) {
  FILE *data_file = fopen(FILE_BOOKING_HISTORY, "a");
  if (!data_file) {
    error("RoomReservation", "File opening failed!");
  }

  fprintf(data_file, "Room: %d %s by %s\n", room_num,
          isBooked ? "booked" : "unbooked", booked_by);

  puts("Successfully Booked Room");
  fclose(data_file);
}

void print_room_data(const S_room_data *data, bool hasBookingViewAuthority) {
  if (data == NULL) {
    error("RoomDataPrint", "NULL DATA SENT");
  }

  char availability[LINE_MAX];
  if (data->is_available) {
    strncpy(availability, "Available", LINE_MAX);
  } else {
    strncpy(availability, "Booked ", LINE_MAX);
    if (hasBookingViewAuthority) {
      strncat(availability, "\tby: ", LINE_MAX);
      strncat(availability, data->booked_by, LINE_MAX);
    }
  }

  printf("No.: %d \t Price: %d \t Status: %s \t Details: %s\n", data->num,
         data->price, availability, data->detail);
}

void print_all_room_data(bool hasBookingViewAuthority) {
  FILE *data_file = fopen(FILE_DATA_ROOMS, "r");
  if (!data_file) {
    error("RoomDataRetrieval", "File opening failed!");
  }

  S_room_data data;
  while (fread(&data, sizeof(S_room_data), 1, data_file)) {
    print_room_data(&data, hasBookingViewAuthority);
    puts("----");
  }
  fclose(data_file);
}

void print_all_available_rooms(bool hasBookingViewAuthority) {
  FILE *data_file = fopen(FILE_DATA_ROOMS, "r");
  if (!data_file) {
    error("RoomDataRetrieval", "File opening failed!");
  }

  S_room_data data;
  while (fread(&data, sizeof(S_room_data), 1, data_file)) {
    if (data.is_available) {
      print_room_data(&data, hasBookingViewAuthority);
      puts("----");
    }
  }
  fclose(data_file);
}

void register_room_data(const S_room_data *room_data) {
  if (room_data == NULL) {
    error("RoomDataRegister", "NULL DATA SENT");
  }
  FILE *data_file = fopen(FILE_DATA_ROOMS, "a");
  if (!data_file) {
    error("RoomDataRegister", "File opening failed!");
  }
  fwrite(room_data, sizeof(S_room_data), 1, data_file);

  puts("Successfully registered room");
  fclose(data_file);
}
