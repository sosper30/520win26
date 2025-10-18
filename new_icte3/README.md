# ICTE3: Multi-User Information Management System

## Exercise Overview
* **Objective:** Modify the program to handle information for multiple users with search, sorting, and validation features.
* **Key Concepts:** Arrays of structures, for loops, search algorithms, sorting algorithms, input validation.

## Features

### Core Functionality
1. **Multiple User Management**
   - Instead of handling a single `UserInfo`, handle an array of `UserInfo` structures (up to 5 users)

2. **Data Input with Validation**
   - Input information for multiple users via `getUserInfo` function
   - Loop through the array and input information for multiple users
   - Age range validation (0-120 years)
   - ID uniqueness check (no duplicate IDs allowed)
   - Input error handling

3. **Search Capabilities**
   - **Search by ID:** `searchUserById` - Find user by exact ID match
   - **Search by Name:** `searchUserByName` - Case-insensitive matching
   - Returns all users matching the search criteria

4. **Sorting Functionality**
   - **Sort by Age:** `sortUsersByAge` - Bubble sort implementation
   - Ascending order (youngest to oldest)
   - Descending order (oldest to youngest)

5. **Display Functions**
   - `displayUserInfo` - Display individual user details

## Program Structure

### Data Structure
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_USERS 5      // Maximum number of users
#define MIN_AGE 0        // Minimum valid age
#define MAX_AGE 120      // Maximum valid age

typedef struct {
    int id;
    char name[100];
    int age;
} UserInfo;
```

### Function Prototypes
```c
void getUserInfo(UserInfo users[], int count);
void displayUserInfo(const UserInfo *user);
int searchUserById(const UserInfo users[], int count, int id);
int searchUserByName(const UserInfo users[], int count, const char *name, int results[]);
void sortUsersByAge(UserInfo users[], int count, int ascending);
int validateAge(int age);
int isIdUnique(const UserInfo users[], int count, int id);
```

## Program Flow

### Step 1: Adding Users
- Prompts for 5 users
- Validates each ID for uniqueness
- Validates age range (0-120)
- Error message displayed for invalid input
- Tests: `getUserInfo()`, `validateAge()`, `isIdUnique()`

### Step 2: Display All Users
- Shows all entered users with formatted output
- Tests: `displayUserInfo()`

### Step 3: Search Users by Name
- Prompts for name to search
- Case-insensitive partial matching
- Displays all matching users
- Tests: `searchUserByName()`

### Step 4: Sort by Age (Ascending)
- Sorts users from youngest to oldest
- Displays sorted results
- Tests: `sortUsersByAge()` with ascending parameter

### Step 5: Sort by Age (Descending)
- Sorts users from oldest to youngest
- Displays sorted results
- Tests: `sortUsersByAge()` with descending parameter

Incorporate all these changes in the `main` function and ensure the program runs smoothly.

## Validation Features

### Age Validation
- Minimum age: 0
- Maximum age: 120
- Error message displayed for invalid input
- User prompted to re-enter

### ID Uniqueness
- Checks all previously entered IDs
- Prevents duplicate IDs
- Error message displayed for duplicates
- User prompted to enter a unique ID



