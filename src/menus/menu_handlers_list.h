#pragma once
#include "../file_list.h"
#include "../helpers/logger.h"
#include "../rooms.h"
#include "../users.h"
#include <stdio.h>

#include "./login_page.h"

#define LINE_MAX 256

void role_selection_display();
void role_selection_action_handler(int action);

/// admin related menus
void admin_view_display();
void admin_view_action_handler(int action);

void admin_user_register_display();
void admin_user_register_handler(int action);

void admin_manage_user_display();
void admin_manage_user_action_handler(int action);
/// admin related menus

/// staff related menus
void staff_view_display();
void staff_view_action_handler(int action);

/*void staff_manage_room_display();*/
/*void staff_manage_room_action_handler(int action);*/
/**/
/*void staff_manage_reservation_display();*/
/*void staff_manage_reservation_handler(int action);*/
/**/
/*void staff_check_in_guest_display();*/
/*void staff_check_in_guest_action_handler(int action);*/
/**/
/*void staff_room_display();*/
/*void staff_room_action_handler();*/
/// staff related menus

/// customer related menus
void customer_view_display();
void customer_view_action_handler(int action);

/*void customer_manage_reservation_display();*/
/*void customer_manage_reservation_handler(int action);*/
/**/
/*void customer_check_in_guest_display();*/
/*void customer_check_in_guest_action_handler(int action);*/
/**/
/*void customer_room_display();*/
/*void customer_room_action_handler();*/
/// customer related menus

void guest_view_display();
void guest_view_action_handler(int action);
