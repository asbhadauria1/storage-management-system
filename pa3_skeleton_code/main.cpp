#include "interface.hpp"
#include "pa3_task.hpp"
#include <unordered_map>
#include <iostream>
#include <string>
#include <limits>
#include <algorithm>
#include <unistd.h>

RoomManagement room_management;
StudentManagement student_management;

struct action {
    const char *args, *description;
    void (*func)();
};
void skip() { std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); }
std::unordered_map<std::string, action> actions = {
    {"add", {"", "adds a new student", []() {
        skip();
        std::cout << "Student " << add_student(student_management) << " added.\n";
    }}},
    {"remove", {"<id>", "removes student <id>", []() {
        int id;
        std::cin >> id;
        skip();
        remove_student(student_management, room_management, id);
    }}},
    {"store", {"<student_id> <item_id> <size> ", "store an item of <size> for student <id>", []() {
        int student_id, item_id, size;
        std::cin >> student_id >> item_id >> size;
        skip();
        if (!store_item_for_student(student_management, room_management, student_id, item_id, size)) {
            std::cout << "store failed: check id and size\n";
        }
    }}},
    {"take", {"<id> <itemid>", "remove an item for student <id>", []() {
        int student_id, item_id;
        std::cin >> student_id >> item_id;
        skip();
        if (!remove_item_for_student(student_management, room_management, student_id, item_id)) {
            std::cout << "take failed: check id \n";
        }
    }}},
    {"defra", {"<id>", "defra student <id>", []() {
        int student_id;
        std::cin >> student_id;
        skip();
        defragment_for_student(student_management, room_management, student_id);
    }}},
    {"clean", {"<room_id>", "clean up all items for room <room_id>", []() {
        int room_id;
        std::cin >> room_id;
        skip();
        cleanup_for_room(student_management, room_management, room_id);
    }}},
    {"infos", {"", "print information of the student", []() {
        int id;
        std::cin >> id;
        skip();
        print_student_status(student_management, id);
    }}},
    {"infor", {"", "print information of the storage room", []() {
        int id;
        std::cin >> id;
        skip();
        print_room_status(room_management, id);
    }}}
};

int main() {
    // redirect stderr to stdout for memory check test cases
    dup2(STDOUT_FILENO, STDERR_FILENO);
    init_room_management(room_management, 10);
    std::cout << " --- Welcome to the locker management system! --- \n";
    // print_room_status(room_management);
    std::string token;
    while (true) {
        std::cout.flush();
        // std::cout << ">> ";
        {
            std::cin >> token;
            if (token == "exit") return EXIT_SUCCESS;
            if (token == "help") {
                skip();
                std::cout << "Available commands:\n";
                std::size_t colw = 0;
                for (const auto& p : actions) {
                    colw = std::max(colw, p.first.size());
                }
                for (const auto& p : actions) {
                    const std::string& command = p.first;
                    const action& value = p.second;
                    std::cout << "  " << command;
                    for (std::size_t i = 0; i < colw - command.size() + 2; ++i) std::cout << ' ';
                    std::cout << value.args << '\n';
                    for (std::size_t i = 0; i < colw+4; ++i) std::cout << ' ';
                    std::cout << value.description << '\n';
                }
                continue;
            }
            const auto it = actions.find(token);
            if (it == actions.end()) {
                skip();
                std::cout << "Invalid command\n";
            } else {
                it->second.func();
            }
        }
    }
}