#pragma once
#include "student.hpp"
#include "storage_room.hpp"
#include "locker.hpp"

/// Task 1: Add new student to student management
int add_student(StudentManagement& student_management);

/// Task 2: Add new locker to room management
void add_locker_for_room(RoomManagement& room_management, int room_id, int locker_size=100);

/// Task 3: Remove student from student management
void management_remove_student(StudentManagement& all_students, int student_id);

/// Task 4: Store an item for a student
bool store_item_for_student(StudentManagement& student_management, RoomManagement& room_management, int student_id, int item_id, int size);

/// Task 5: Remove an item for a student
bool remove_item_for_student(StudentManagement& student_management, RoomManagement& room_management, int student_id, int item_id);

/// Task 6: Defragment all items for a student
bool defragment_for_student(StudentManagement& student_management, RoomManagement& room_management, int student_id);

/// Task 7: Defragment all items for a student
void remove_student(StudentManagement& student_management, RoomManagement& room_management, int student_id);

/// Task 8: Clean up all items for a room
void cleanup_for_room(StudentManagement& student_management, RoomManagement& room_management, int room_id);






