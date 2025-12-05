#include "storage_room.hpp"
#include <cstring>
#include <iostream>

void add_empty_rooms(RoomManagement& room_management, int room_count) {
    room_management.rooms = new Room[room_count];
    for (int i = 0; i < room_count; ++i) {
        room_management.rooms[i] = Room{
            .room_id = i,
            .locker_count = 0,
            .locker_list = nullptr
        };
    }
    room_management.room_count = room_count;
    return;
}

Locker* search_empty_locker(RoomManagement& room_management) {
    for (int i = 0; i < room_management.room_count; ++i) {
        Room& room = room_management.rooms[i];
        if (room.locker_list != nullptr && room.locker_list->locker->avaliable_space == room.locker_list->locker->capacity) {
            return room.locker_list->locker;
        }
    }
    return nullptr;
}

void print_room_status(const RoomManagement& room_management, int room_id) {
    for (int i = 0; i < room_management.room_count; ++i) {
        if (room_id != -1 && room_id != room_management.rooms[i].room_id) {
            continue;
        }
        const Room& room = room_management.rooms[i];
        std::cout << "Room " << room.room_id << ": " << room.locker_count << " lockers\n";
        std::cout << "Lockers: ";
        LockerView* current = room.locker_list;
        while (current != nullptr) {
            std::cout << "[" << current->locker->locker_id << ": " << current->locker->avaliable_space << "/" << current->locker->capacity << "]";
            if (current->locker->item_count > 0) {
                std::cout << " (Items: ";
                ItemView* item_current = current->locker->item_list;
                while (item_current != nullptr) {
                    std::cout << "Item " << item_current->item->id << " student " << item_current->item->belonged_student->id << " size "<< item_current->item->size;
                    if (item_current->next != nullptr) {
                        std::cout << ", ";
                    }
                    item_current = item_current->next;
                }
                std::cout << ")";
            }
            if (current->next != nullptr) {
                std::cout << " -> ";
            }
            current = current->next;
        }
        std::cout << '\n';
    }
}