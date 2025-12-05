#pragma once

struct Item {
    int id; /// Item Id
    int size;
    struct Locker* stored_locker; /// pointer to the locker the item belongs to
    struct Student* belonged_student; /// pointer to the student the item belongs to
};