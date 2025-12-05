# COMP 2011 PA3 Storage Management System

## how to run

```
bash run.sh
```

## Command

add a new student
```
add
```
store a item for a student
```
store <student_id> <item_id> <item_size>
store 0 0 10 // store item 0 with size 10 for student 0
```
take a item for a student
```
store <student_id> <item_id> 
take 0 0 // take item 0 from student 0
```
remove a student and release all occupied lockers 
```
remove <student_id> 
remove 0 // remove student 0
```
defragment all items that a student has
```
defra <student_id> 
defra 0 // defragment items of student 0
```

clean all items in a room
```
clean <room_id> 
clean 0 // clean items in room 0
```

print a student information or all students information
```
infos <student_id>
infos 0 // print student 0 information
infos -1 // print all student information
``` 
print a room's information or all rooms information
```
infor <room_id>
infor 0 // print room 0 information
infor -1 // print all rooms information
``` 

## example

```
 --- Welcome to the locker management system! --- 
Room 0: 5 lockers
Lockers: [4: 100/100] -> [3: 100/100] -> [2: 100/100] -> [1: 100/100] -> [0: 100/100]
Room 1: 5 lockers
Lockers: [4: 100/100] -> [3: 100/100] -> [2: 100/100] -> [1: 100/100] -> [0: 100/100]
Room 2: 5 lockers
Lockers: [4: 100/100] -> [3: 100/100] -> [2: 100/100] -> [1: 100/100] -> [0: 100/100]
Room 3: 5 lockers
Lockers: [4: 100/100] -> [3: 100/100] -> [2: 100/100] -> [1: 100/100] -> [0: 100/100]
Room 4: 5 lockers
Lockers: [4: 100/100] -> [3: 100/100] -> [2: 100/100] -> [1: 100/100] -> [0: 100/100]
Room 5: 5 lockers
Lockers: [4: 100/100] -> [3: 100/100] -> [2: 100/100] -> [1: 100/100] -> [0: 100/100]
Room 6: 5 lockers
Lockers: [4: 100/100] -> [3: 100/100] -> [2: 100/100] -> [1: 100/100] -> [0: 100/100]
Room 7: 5 lockers
Lockers: [4: 100/100] -> [3: 100/100] -> [2: 100/100] -> [1: 100/100] -> [0: 100/100]
Room 8: 5 lockers
Lockers: [4: 100/100] -> [3: 100/100] -> [2: 100/100] -> [1: 100/100] -> [0: 100/100]
Room 9: 5 lockers
Lockers: [4: 100/100] -> [3: 100/100] -> [2: 100/100] -> [1: 100/100] -> [0: 100/100]
>> add
Student 0 added.
>> store 0 0 1
>> store 0 1 10
>> store 0 2 90
>> store 0 3 99
>> infos 0
Total students: 1 Actual students: 1
Student 0: 4 items
  Item 0: size 1
  Item 1: size 10
  Item 2: size 90
  Item 3: size 99
>> infor 0
Room 0: 5 lockers
Lockers: [1: 100/100] -> [0: 100/100] -> [4: 89/100] (Items: Item 0 student 0 size 1, Item 1 student 0 size 10) -> [3: 10/100] (Items: Item 2 student 0 size 90) -> [2: 1/100] (Items: Item 3 student 0 size 99)
>> defra 0
>> infor 0
Room 0: 5 lockers
Lockers: [2: 100/100] -> [1: 100/100] -> [0: 100/100] -> [4: 0/100] (Items: Item 0 student 0 size 1, Item 3 student 0 size 99) -> [3: 0/100] (Items: Item 1 student 0 size 10, Item 2 student 0 size 90)
>> remove 0
>> infor 0
Room 0: 5 lockers
Lockers: [4: 100/100] -> [3: 100/100] -> [2: 100/100] -> [1: 100/100] -> [0: 100/100]
```