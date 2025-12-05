#pragma once
#include "item.hpp"

struct Student {
    int id; /// -1: deregistered
    /// dynamic array, invalid if id == -1 or if boxes_capacity == 0\n
    /// invariant: sorted by description in ascending lexographical order
    Item** items;
    /// invalid if id == -1
    int items_count, items_capacity;
};

struct StudentManagement {
    Student* students = nullptr; /// dynamic array of users, invalid if capacity == 0
    int size = 0, capacity = 0, actual_students = 0;
};

/// Return true if and only if user_id is within [0, size), and users[user_id].id != -1.
bool students_is_valid(const StudentManagement& all_students, int student_id);

Student* get_student(StudentManagement& all_students, int student_id);

void print_student_status(const StudentManagement& all_students, int student_id=-1);
