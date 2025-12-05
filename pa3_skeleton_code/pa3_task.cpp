#include "pa3_task.hpp"

/// You can implement Tools functions here.
/// Please make sure all your implementation are included in this file.
/// We will test your code only based on this file.

/// Task 1: Add new student
int add_student(StudentManagement &student_management)
{
    // 1. check array capacity
    // When the student array reaches capacity
    // allocates a new array with size new_capacity = old_capacity * 2 + 1
    // copies all existing students to the new array
    // deallocates the old array.

    // 2. initialize new student and assign an ID equal to their position in the array (index-based ID assignment).

    // 3. update management information.

    // return new student's ID
    if (student_management.size == student_management.capacity)
    {
        student_management.capacity = student_management.capacity * 2 + 1;
        Student *old = student_management.students;
        student_management.students = new Student[student_management.capacity];
        for (int i = 0; i < student_management.size; i++)
        {
            // copy student struct fields (shallow copy for items pointer)
            student_management.students[i].id = old[i].id;
            student_management.students[i].items = old[i].items;
            student_management.students[i].items_count = old[i].items_count;
            student_management.students[i].items_capacity = old[i].items_capacity;
        }
        delete[] old;
        old = nullptr;
    }
    int id = student_management.size;
    student_management.students[student_management.size].id = student_management.size;
    student_management.students[student_management.size].items = nullptr;
    student_management.students[student_management.size].items_capacity = 0;
    student_management.students[student_management.size].items_count = 0;
    student_management.actual_students++;
    student_management.size++;
    return id;
}

/// Task 2: Add new locker to room management
void add_locker_for_room(RoomManagement &room_management, int room_id, int locker_size)
{
    bool found = false;
    Room *room = nullptr;
    for (int i = 0; i < room_management.room_count; i++)
    {
        if (room_id == room_management.rooms[i].room_id)
        {
            found = true;
            room = &room_management.rooms[i];
            break;
        }
    }
    if (!found)
    {
        return;
    }
    LockerView *newlocker = new LockerView;
    newlocker->locker = new Locker;
    newlocker->locker->capacity = locker_size;
    newlocker->locker->avaliable_space = locker_size;
    newlocker->locker->locker_id = room->locker_count;
    newlocker->locker->item_count = 0;
    newlocker->locker->item_list = nullptr;
    newlocker->locker->belonged_room = room;

    newlocker->next = nullptr;
    newlocker->pre = nullptr;

    if (room->locker_list == nullptr)
    {
        room->locker_list = newlocker;
        room->locker_count++;
        return;
    }

    LockerView *curr = room->locker_list;
    LockerView *prev = nullptr;

    while (curr != nullptr)
    {
        if (curr->locker->avaliable_space < newlocker->locker->avaliable_space)
        {
            break;
        }
        else if (curr->locker->avaliable_space == newlocker->locker->avaliable_space)
        {
            if (curr->locker->locker_id < newlocker->locker->locker_id)
            {
                break;
            }
        }
        prev = curr;
        curr = curr->next;
    }

    if (prev == nullptr)
    {
        newlocker->next = room->locker_list;
        room->locker_list->pre = newlocker;
        room->locker_list = newlocker;
    }
    else
    {
        newlocker->next = curr;
        newlocker->pre = prev;
        prev->next = newlocker;
        if (curr != nullptr)
        {
            curr->pre = newlocker;
        }
    }

    room->locker_count++;
    return;
}

/// Task 3: Remove student from student management
void management_remove_student(StudentManagement &all_students, int student_id)
{
    // 1. Validate student_id. If not valid, return.

    // 2. Mark student as deregistered with -1.

    // 3. Delete Students' items array.

    // 4. Update management information.
    if (student_id < 0 || student_id >= all_students.size)
        return;
    if (all_students.students[student_id].id == -1)
        return;
    if (all_students.students[student_id].items != nullptr)
    {
        delete[] all_students.students[student_id].items;
        all_students.students[student_id].items = nullptr;
    }
    all_students.students[student_id].id = -1;
    all_students.students[student_id].items_count = 0;
    all_students.students[student_id].items_capacity = 0;
    all_students.actual_students--;
}

/// Task 4: Store an item for a student
bool store_item_for_student(StudentManagement &student_management, RoomManagement &room_management, int student_id, int item_id, int size)
{
    // 1. Find student based on student_id. If student not found, return false.

    // 2. Find a locker with enough space based on Two-Phase Search Strategy.

    // 2.1 Iterates through the student’s items array in order
    // checking each item’s locker for sufficient space (avaliable_space >= item_size).
    // Selects the FIRST locker that can accommodate the new item.

    // 2.2 If no studented locker has space, searches all rooms in ascending order of room ID.
    // Within each room, traverses the locker linked list from head to tail to find an empty locker.
    // Returns the first empty locker found.

    // 2.3 If no such locker is found, the operation fails and returns false.

    // 3. Create new item.

    // 4. Store item in locker.
    // 4.1 Creates a new ItemView node and inserts it into the locker’s item_list linked list
    // 4.2 maintaining sorted order by size (ascending) and then by ID as tiebreaker

    // 5. Adjusts the locker’s position in the room’s locker list
    // sorted by available space (descending) and then by locker ID as a tiebreaker.

    // 6. Add item to student's item array.
    // When the item array reaches capacity.
    // allocates a new array with size new_capacity = old_capacity * 2 + 1
    // copies all existing items to the new array
    // deallocates the old array.
    // update new Item and Student information.

    // 7. Return true to indicate successful storage.
    bool found = false;
    Student *student = nullptr;
    for (int i = 0; i < student_management.size; i++)
    {
        if (student_management.students[i].id == student_id)
        {
            found = true;
            student = &student_management.students[i];
            break;
        }
    }
    if (!found)
        return false;

    Locker *locker = nullptr;
    Room *room = nullptr;
    LockerView *lockerpos = nullptr;

    for (int i = 0; i < student->items_count; i++)
    {
        if (student->items[i]->stored_locker->avaliable_space >= size)
        {
            locker = student->items[i]->stored_locker;
            room = locker->belonged_room;
            break;
        }
    }

    if (!locker)
    {
        for (int i = 0; i < room_management.room_count; i++)
        {
            LockerView *p = room_management.rooms[i].locker_list;
            for (; p; p = p->next)
            {
                if (p->locker->avaliable_space >= size)
                {
                    locker = p->locker;
                    room = &room_management.rooms[i];
                    lockerpos = p;
                    break;
                }
            }
            if (locker)
                break;
        }
    }

    if (!locker)
        return false;

    locker->item_count++;
    locker->avaliable_space -= size;

    ItemView *newnode = new ItemView;
    newnode->item = new Item;
    newnode->item->id = item_id;
    newnode->item->size = size;
    newnode->item->stored_locker = locker;
    newnode->item->belonged_student = student;
    newnode->prev = nullptr;
    newnode->next = nullptr;

    ItemView *p = locker->item_list;
    if (!p)
    {
        locker->item_list = newnode;
    }
    else
    {
        for (; p; p = p->next)
        {
            if (p->item->size > size || (p->item->size == size && p->item->id > item_id))
            {
                ItemView *temppre = p->prev;
                newnode->next = p;
                newnode->prev = temppre;
                p->prev = newnode;
                if (temppre)
                    temppre->next = newnode;
                else
                    locker->item_list = newnode;
                break;
            }
            if (!p->next)
            {
                p->next = newnode;
                newnode->prev = p;
                break;
            }
        }
    }

    if (!lockerpos)
    {
        LockerView *cur = room->locker_list;
        while (cur)
        {
            if (cur->locker == locker)
            {
                lockerpos = cur;
                break;
            }
            cur = cur->next;
        }
    }

    if (lockerpos)
    {
        LockerView *pre = lockerpos->pre;
        LockerView *next = lockerpos->next;
        if (pre)
            pre->next = next;
        else
            room->locker_list = next;
        if (next)
            next->pre = pre;

        LockerView *q = room->locker_list;
        for (; q; q = q->next)
        {
            if (q->locker->avaliable_space < locker->avaliable_space ||
                (q->locker->avaliable_space == locker->avaliable_space && q->locker->locker_id > locker->locker_id))
            {
                LockerView *temppre = q->pre;
                lockerpos->next = q;
                lockerpos->pre = temppre;
                q->pre = lockerpos;
                if (temppre)
                    temppre->next = lockerpos;
                else
                    room->locker_list = lockerpos;
                break;
            }
            if (!q->next)
            {
                q->next = lockerpos;
                lockerpos->pre = q;
                lockerpos->next = nullptr;
                break;
            }
        }
        if (!room->locker_list)
        {
            room->locker_list = lockerpos;
            lockerpos->pre = nullptr;
            lockerpos->next = nullptr;
        }
    }

    if (student->items_count >= student->items_capacity)
    {
        int newcap = student->items_capacity * 2 + 1;
        Item **old = student->items;
        student->items = new Item *[newcap];
        for (int i = 0; i < student->items_count; i++)
            student->items[i] = old[i];
        delete[] old;
        student->items_capacity = newcap;
    }

    student->items[student->items_count] = newnode->item;
    student->items_count++;

    return true;
}
/// Task 5: Remove an item for a student
bool remove_item_for_student(StudentManagement &student_management, RoomManagement &room_management, int student_id, int item_id)
{
    // 1. Find student based on student_id. If student not found, return false.

    // 2. Find item based on item_id in the student's item array. If item not found, return false.

    // 3. Find the locker and room the item is stored in.

    // 4. Remove item from locker.
    // 4.1 Removes the corresponding ItemView node from the locker’s item_list linked
    // 4.2 Updates the locker’s information.

    // 5. Adjusts the locker’s position in the room’s locker list
    // sorted by available space (descending) and then by locker ID as a tiebreaker.

    // 6. Remove item from student's item array.
    // 6.1 Finds the item in the student's item array.
    // 6.2 Shifts subsequent items to fill the gap.
    // 6.3 Updates the student's item count.

    // 7. Deallocates the item.

    // 8. Returns true to indicate successful removal.
    if (student_id == -1)
        return false;
    Student *student = nullptr;
    for (int i = 0; i < student_management.size; i++)
    {
        if (student_management.students[i].id == student_id)
        {
            student = &student_management.students[i];
            break;
        }
    }
    if (!student)
        return false;
    Item *item = nullptr;
    int idx = -1;
    for (int i = 0; i < student->items_count; i++)
    {
        if (student->items[i]->id == item_id)
        {
            item = student->items[i];
            idx = i;
            break;
        }
    }
    if (!item)
        return false;
    Locker *locker = item->stored_locker;
    Room *room = locker->belonged_room;
    ItemView *target = nullptr;
    for (ItemView *p = locker->item_list; p; p = p->next)
    {
        if (p->item == item)
        {
            target = p;
            break;
        }
    }
    if (!target)
        return false;
    if (target->prev)
        target->prev->next = target->next;
    else
        locker->item_list = target->next;
    if (target->next)
        target->next->prev = target->prev;
    locker->avaliable_space += item->size;
    locker->item_count--;
    LockerView *lockerpos = nullptr;
    for (LockerView *p = room->locker_list; p; p = p->next)
    {
        if (p->locker == locker)
        {
            lockerpos = p;
            break;
        }
    }
    if (lockerpos)
    {
        LockerView *pre = lockerpos->pre;
        LockerView *next = lockerpos->next;
        if (pre)
            pre->next = next;
        else
            room->locker_list = next;
        if (next)
            next->pre = pre;
        LockerView *q = room->locker_list;
        bool placed = false;
        for (; q; q = q->next)
        {
            if (q->locker->avaliable_space < locker->avaliable_space ||
                (q->locker->avaliable_space == locker->avaliable_space && q->locker->locker_id < locker->locker_id))
            {
                LockerView *temppre = q->pre;
                q->pre = lockerpos;
                lockerpos->pre = temppre;
                lockerpos->next = q;
                if (temppre)
                    temppre->next = lockerpos;
                else
                    room->locker_list = lockerpos;
                placed = true;
                break;
            }
            if (!q->next)
            {
                q->next = lockerpos;
                lockerpos->pre = q;
                lockerpos->next = nullptr;
                placed = true;
                break;
            }
        }
        if (!placed && !room->locker_list)
        {
            room->locker_list = lockerpos;
            lockerpos->pre = nullptr;
            lockerpos->next = nullptr;
        }
    }
    for (int j = idx; j < student->items_count - 1; j++)
        student->items[j] = student->items[j + 1];
    student->items[student->items_count - 1] = nullptr;
    student->items_count--;
    delete item;
    delete target;
    return true;
}

/// Task 6: Remove a student and clean up all their items
void remove_student(StudentManagement &student_management, RoomManagement &room_management, int student_id)
{

    // 1. Find student based on student_id.

    // 2. Remove all items belonging to the student.
    // For each item:
    // 2.1 Find the locker and room the item is stored in.
    // 2.2 Remove item from locker.
    // 2.3 Adjusts the locker’s position in the room’s locker list.
    // 2.4 Deallocates the item.

    // 3. Remove student from management.
    Student *student = nullptr;
    for (int i = 0; i < student_management.size; i++)
    {
        if (student_management.students[i].id == student_id)
        {
            student = &student_management.students[i];
            break;
        }
    }
    if (!student)
        return;
    while (student->items_count > 0)
    {
        int iid = student->items[0]->id;
        remove_item_for_student(student_management, room_management, student_id, iid);
    }
    management_remove_student(student_management, student_id);
}

/// Task 7: Defragment items for a student
bool defragment_for_student(StudentManagement &student_management, RoomManagement &room_management, int student_id)
{
    if (student_id == -1)
        return false;
    Student *student = nullptr;
    for (int i = 0; i < student_management.size; i++)
    {
        if (student_management.students[i].id == student_id)
        {
            student = &student_management.students[i];
            break;
        }
    }
    if (!student)
        return false;
    int total = student->items_count;
    if (total == 0)
        return true;
    Item **copy = new Item *[total];
    for (int i = 0; i < total; i++)
        copy[i] = student->items[i];
    for (int i = 0; i < total; i++)
    {
        Item *it = copy[i];
        if (!it)
            continue;
        Locker *locker = it->stored_locker;
        Room *room = locker->belonged_room;
        ItemView *target = nullptr;
        for (ItemView *itemview = locker->item_list; itemview; itemview = itemview->next)
        {
            if (itemview->item == it)
            {
                target = itemview;
                break;
            }
        }
        if (target)
        {
            if (target->prev)
                target->prev->next = target->next;
            else
                locker->item_list = target->next;
            if (target->next)
                target->next->prev = target->prev;
            locker->avaliable_space += it->size;
            locker->item_count--;
            delete target;
            target = nullptr;
        }
        LockerView *lockerpos = nullptr;
        for (LockerView *p = room->locker_list; p; p = p->next)
        {
            if (p->locker == locker)
            {
                lockerpos = p;
                break;
            }
        }
        if (lockerpos)
        {
            LockerView *pre = lockerpos->pre;
            LockerView *next = lockerpos->next;
            if (pre)
                pre->next = next;
            else
                room->locker_list = next;
            if (next)
                next->pre = pre;
            LockerView *q = room->locker_list;
            bool placed = false;
            for (; q; q = q->next)
            {
                if (q->locker->avaliable_space < locker->avaliable_space ||
                    (q->locker->avaliable_space == locker->avaliable_space && q->locker->locker_id < locker->locker_id))
                {
                    LockerView *temppre = q->pre;
                    q->pre = lockerpos;
                    lockerpos->pre = temppre;
                    lockerpos->next = q;
                    if (temppre)
                        temppre->next = lockerpos;
                    else
                        room->locker_list = lockerpos;
                    placed = true;
                    break;
                }
                if (!q->next)
                {
                    q->next = lockerpos;
                    lockerpos->pre = q;
                    lockerpos->next = nullptr;
                    placed = true;
                    break;
                }
            }
            if (!placed && !room->locker_list)
            {
                room->locker_list = lockerpos;
                lockerpos->pre = nullptr;
                lockerpos->next = nullptr;
            }
        }
    }
    student->items_count = 0;
    int items_remaining = total;
    while (items_remaining > 0)
    {
        Locker *current_locker = nullptr;
        Room *current_room = nullptr;
        LockerView *current_lockerpos = nullptr;
        for (int r = 0; r < room_management.room_count; r++)
        {
            LockerView *currlock = room_management.rooms[r].locker_list;
            for (; currlock; currlock = currlock->next)
            {
                if (currlock->locker->item_count == 0)
                {
                    current_locker = currlock->locker;
                    current_room = &room_management.rooms[r];
                    current_lockerpos = currlock;
                    break;
                }
            }
            if (current_locker)
                break;
        }
        if (!current_locker)
            break;
        bool packed_any = false;
        while (current_locker->avaliable_space > 0 && items_remaining > 0)
        {
            Item *max = nullptr;
            int max_index = -1;
            for (int j = 0; j < total; j++)
            {
                if (copy[j] != nullptr)
                {
                    if (copy[j]->size <= current_locker->avaliable_space)
                    {
                        if (max == nullptr)
                        {
                            max = copy[j];
                            max_index = j;
                        }
                        else if (copy[j]->size > max->size)
                        {
                            max = copy[j];
                            max_index = j;
                        }
                        else if (copy[j]->size == max->size)
                        {
                            if (copy[j]->id > max->id)
                            {
                                max = copy[j];
                                max_index = j;
                            }
                        }
                    }
                }
            }
            if (max == nullptr)
                break;
            ItemView *newnode = new ItemView;
            newnode->item = max;
            newnode->prev = nullptr;
            newnode->next = nullptr;
            ItemView *p = current_locker->item_list;
            if (!p)
            {
                current_locker->item_list = newnode;
            }
            else
            {
                for (; p; p = p->next)
                {
                    if (p->item->size > max->size || (p->item->size == max->size && p->item->id > max->id))
                    {
                        ItemView *temppre = p->prev;
                        p->prev = newnode;
                        newnode->prev = temppre;
                        newnode->next = p;
                        if (temppre)
                            temppre->next = newnode;
                        else
                            current_locker->item_list = newnode;
                        break;
                    }
                    if (!p->next)
                    {
                        p->next = newnode;
                        newnode->prev = p;
                        newnode->next = nullptr;
                        break;
                    }
                }
            }
            current_locker->avaliable_space -= max->size;
            current_locker->item_count++;
            max->stored_locker = current_locker;
            if (student->items_count >= student->items_capacity)
            {
                int newcap = student->items_capacity * 2 + 1;
                Item **old = student->items;
                student->items = new Item *[newcap];
                for (int ii = 0; ii < student->items_count; ii++)
                    student->items[ii] = old[ii];
                delete[] old;
                student->items_capacity = newcap;
            }
            student->items[student->items_count] = max;
            student->items_count++;
            copy[max_index] = nullptr;
            items_remaining--;
            packed_any = true;
            if (current_lockerpos)
            {
                LockerView *pre = current_lockerpos->pre;
                LockerView *next = current_lockerpos->next;
                if (pre)
                    pre->next = next;
                else
                    current_room->locker_list = next;
                if (next)
                    next->pre = pre;
                LockerView *q = current_room->locker_list;
                bool placed2 = false;
                for (; q; q = q->next)
                {
                    if (q->locker->avaliable_space < current_locker->avaliable_space ||
                        (q->locker->avaliable_space == current_locker->avaliable_space && q->locker->locker_id < current_locker->locker_id))
                    {
                        LockerView *temppre = q->pre;
                        q->pre = current_lockerpos;
                        current_lockerpos->pre = temppre;
                        current_lockerpos->next = q;
                        if (temppre)
                            temppre->next = current_lockerpos;
                        else
                            current_room->locker_list = current_lockerpos;
                        placed2 = true;
                        break;
                    }
                    if (!q->next)
                    {
                        q->next = current_lockerpos;
                        current_lockerpos->pre = q;
                        current_lockerpos->next = nullptr;
                        placed2 = true;
                        break;
                    }
                }
                if (!placed2 && !current_room->locker_list)
                {
                    current_room->locker_list = current_lockerpos;
                    current_lockerpos->pre = nullptr;
                    current_lockerpos->next = nullptr;
                }
            }
        }
        if (!packed_any)
            break;
    }
    delete[] copy;
    return true;
}

/// Task 8: Clean up all items for a room
void cleanup_for_room(StudentManagement &student_management, RoomManagement &room_management, int room_id)
{
    // 1. Find room based on room_id. if room not found, return.

    // 2. For each locker in the room:
    //    For each item in the locker:
    //      - Find the student the item belongs to.
    //      - Remove item from student's item array.
    //      - Deallocates the item.

    // 3. Reset locker information and locker list order.
    Room *room = nullptr;
    for (int i = 0; i < room_management.room_count; i++)
    {
        if (room_management.rooms[i].room_id == room_id)
        {
            room = &room_management.rooms[i];
            break;
        }
    }
    if (!room)
        return;

    int count = room->locker_count;
    LockerView **lockerpos = new LockerView *[(count > 0) ? count : 1];
    int t = 0;
    LockerView *p = room->locker_list;
    while (p)
    {
        lockerpos[t] = p;
        t++;
        p = p->next;
    }

    for (int i = 0; i < t; i++)
    {
        Locker *locker = lockerpos[i]->locker;
        ItemView *itemview = locker->item_list;
        while (itemview)
        {
            ItemView *nx = itemview->next;
            Item *item = itemview->item;
            Student *student = nullptr;
            if (item && item->belonged_student)
                student = item->belonged_student;
            if (student)
            {
                int pos = -1;
                for (int q = 0; q < student->items_count; q++)
                {
                    if (student->items[q] == item)
                    {
                        pos = q;
                        break;
                    }
                }
                if (pos != -1)
                {
                    for (int z = pos; z < student->items_count - 1; z++)
                        student->items[z] = student->items[z + 1];
                    student->items[student->items_count - 1] = nullptr;
                    student->items_count--;
                }
            }
            item->belonged_student = nullptr;
            delete item;
            delete itemview;
            itemview = nx;
        }
        locker->item_list = nullptr;
        locker->item_count = 0;
        locker->avaliable_space = locker->capacity;
    }

    for (int i = 0; i < t; i++)
    {
        for (int j = i + 1; j < t; j++)
        {
            Locker *a = lockerpos[i]->locker;
            Locker *b = lockerpos[j]->locker;
            if (a->avaliable_space < b->avaliable_space ||
                (a->avaliable_space == b->avaliable_space && a->locker_id < b->locker_id))
            {
                LockerView *temp = lockerpos[i];
                lockerpos[i] = lockerpos[j];
                lockerpos[j] = temp;
            }
        }
    }

    room->locker_list = nullptr;
    for (int i = 0; i < t; i++)
    {
        if (i == 0)
            lockerpos[i]->pre = nullptr;
        else
            lockerpos[i]->pre = lockerpos[i - 1];
        if (i == t - 1)
            lockerpos[i]->next = nullptr;
        else
            lockerpos[i]->next = lockerpos[i + 1];
    }

    if (t > 0)
        room->locker_list = lockerpos[0];

    delete[] lockerpos;
}