#include "interface.hpp"
#include "pa3_task.hpp"
#include <iostream>
void init_room_management(RoomManagement& room_management, int room_count) {
    add_empty_rooms(room_management, room_count);
    for (int i = 0; i < room_count; ++i) {
        for (int j = 0; j < 5; ++j) {
            add_locker_for_room(room_management, i);
        }
    }
}