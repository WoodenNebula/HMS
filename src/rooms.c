#include "./rooms.h"
#include "./file_list.h"
#include "./helpers/logger.h"
#include <stdio.h>
#include <string.h>

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

S_room_data get_room_details(int room_num) {
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

  printf(" %d", data.num);
  printf("Enter price: ");
  scanf("%d", &data.price);

  data.is_available = true;

  printf("Enter room details: ");
  scanf(" %[^\n]s", data.detail);

  return data;
}

void print_room_data(const S_room_data *data) {
  if (data == NULL) {
    error("RoomDataPrint", "NULL DATA SENT");
  }

  const char *availability = data->is_available ? "Available" : "Booked";

  printf("No.: %d \t Status: %s \t Price: %d \t Details: %s\n", data->num,
         availability, data->price, data->detail);
}

void print_all_room_data() {
  FILE *data_file = fopen(FILE_DATA_ROOMS, "r");
  if (!data_file) {
    error("RoomDataRetrieval", "File opening failed!");
  }

  S_room_data data;
  while (fread(&data, sizeof(S_room_data), 1, data_file)) {
    print_room_data(&data);
    puts("----");
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
