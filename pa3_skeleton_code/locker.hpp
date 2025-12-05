#pragma once
#include "item.hpp"
#include "student.hpp"

struct ItemView {
    Item* item;
    ItemView* prev; /// NULL if not exist
    ItemView* next; /// NULL if not exist
};

struct Locker {
    ItemView* item_list; /// linked list of boxes, invalid if owners_size == 0
    struct Room* belonged_room; /// pointer to the room the locker belongs to
    int locker_id;
    int item_count;
    int capacity; /// always valid
    int avaliable_space;
};


