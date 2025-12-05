# Storage Management System

A C++ implementation of a university storage management system for student belongings, featuring dynamic memory management, linked lists, and greedy packing algorithms.

## 📋 Overview

This project simulates a comprehensive University Storage Management System that manages student storage facilities, locker allocation, and item storage/retrieval operations. The system implements efficient space management algorithms and dynamic data structures to optimize storage utilization.

### 🎯 Learning Objectives
- Implement various data structures (dynamic arrays, linked lists)
- Master dynamic memory allocation and management in C++
- Design algorithms for searching and manipulating complex data structures
- Maintain multiple data structure invariants simultaneously
- Implement greedy algorithms for space optimization

## 🏗️ System Architecture

### Core Components:
- **Storage Rooms**: Physical spaces containing multiple lockers
- **Lockers**: Storage units with fixed capacity for student items
- **Students**: Users who own and store items
- **Items**: Physical objects stored in lockers
- **Management Structures**: Central controllers for rooms and students

### Data Structures:
- **Dynamic Arrays**: For student and item management with doubling strategy
- **Doubly Linked Lists**: For locker and item organization within rooms
- **Sorted Lists**: Lockers sorted by available space, items sorted by size
- **Bidirectional Relationships**: Items maintain pointers to both owners and storage locations


