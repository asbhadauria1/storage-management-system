#include "student.hpp"
#include <cstring>
#include <iostream>

bool students_is_valid(const StudentManagement& all_students, int student_id) {
    return student_id >= 0 && student_id < all_students.size && all_students.students[student_id].id != -1;
}

Student* get_student(StudentManagement& all_students, int student_id) {
    if (!students_is_valid(all_students, student_id)) return nullptr;
    return &all_students.students[student_id];
}

void print_student_status(const StudentManagement& all_students, int student_id) {
    std::cout << "Total students: " << all_students.size << " Actual students: " << all_students.actual_students << "\n";
    if (student_id == -1) {
        for (int i = 0; i < all_students.size; ++i) {
            const Student& student = all_students.students[i];
            if (student.id == -1) continue;
            std::cout << "Student " << student.id << ": " << student.items_count << " items\n";
            for (int j = 0; j < student.items_count; ++j) {
                const Item* item = student.items[j];
                std::cout << "  Item " << item->id << ": size " << item->size << "\n";
            }
        }
    } else {
        for (int i = 0; i < all_students.size; ++i) {
            if (student_id == all_students.students[i].id) {
                const Student& student = all_students.students[i];
                std::cout << "Student " << student.id << ": " << student.items_count << " items\n";
                for (int j = 0; j < student.items_count; ++j) {
                    const Item* item = student.items[j];
                    std::cout << "  Item " << item->id << ": size " << item->size << "\n";
                }
            }
        }
    }
    return;
}