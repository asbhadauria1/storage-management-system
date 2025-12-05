#pragma once
#include "locker.hpp"

#define FIXED_LOCKER_SIZE 100

struct RoomManagement {
    Room* rooms = nullptr;
    int room_count = 0;
};

struct LockerView {
    Locker* locker;
    LockerView* pre; /// NULL if not exist
    LockerView* next; /// NULL if not exist
};

struct Room {
    int room_id;
    int locker_count; /// number of available lockers
    LockerView* locker_list; /// head of linked list of free lockers, NULL if empty
};

/// 1. Set avail to storage_room_size.
/// 2. Add all lockers to free_list, in the same order as lockers.
/// 3. Initialize all lockers: set owners_size and owners_capacity to 0.
void add_empty_rooms(RoomManagement& room_management, int room_count);

Locker* search_empty_locker(RoomManagement& room_management);

void print_room_status(const RoomManagement& room_management, int room_id=-1);
