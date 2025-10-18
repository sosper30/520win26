#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_USERS 5
#define MIN_AGE 0
#define MAX_AGE 120

// Structure to hold user information
typedef struct {
    int id;
    char name[100];
    int age;
} UserInfo;

// Function prototypes
void getUserInfo(UserInfo users[], int count);
void displayUserInfo(const UserInfo *user);
int searchUserById(const UserInfo users[], int count, int id);
int searchUserByName(const UserInfo users[], int count, const char *name, int results[]);
void sortUsersByAge(UserInfo users[], int count, int ascending);
int validateAge(int age);
int isIdUnique(const UserInfo users[], int count, int id);

int main() {
    UserInfo users[MAX_USERS];
    
    // Get information for multiple users (fill the database)
    printf("=== STEP 1: Adding Users (Fill Database) ===\n");
    getUserInfo(users, MAX_USERS);
    
    // Display all users
    printf("\n=== STEP 2: Display All Users ===\n");
    for (int i = 0; i < MAX_USERS; i++) {
        printf("\nUser #%d:\n", i + 1);
        displayUserInfo(&users[i]);
    }
    
    // Test search by ID
    printf("\n=== STEP 3: Search User by ID ===\n");
    int searchId;
    printf("Enter ID to search: ");
    scanf("%d", &searchId);
    
    int index = searchUserById(users, MAX_USERS, searchId);
    if (index != -1) {
        printf("\nUser found:\n");
        displayUserInfo(&users[index]);
    } else {
        printf("\nUser with ID %d not found.\n", searchId);
    }
    
    // Test search by name
    printf("\n=== STEP 4: Search Users by Name ===\n");
    char searchName[100];
    printf("Enter name to search: ");
    while (getchar() != '\n'); // Clear input buffer
    fgets(searchName, sizeof(searchName), stdin);
    searchName[strcspn(searchName, "\n")] = '\0';
    
    int results[MAX_USERS];
    int foundCount = searchUserByName(users, MAX_USERS, searchName, results);
    
    if (foundCount > 0) {
        printf("\nFound %d user(s) matching '%s':\n", foundCount, searchName);
        for (int i = 0; i < foundCount; i++) {
            displayUserInfo(&users[results[i]]);
        }
    } else {
        printf("\nNo users found with name '%s'.\n", searchName);
    }
    
    // Test sorting - Ascending
    printf("\n=== STEP 5: Sort Users by Age (Ascending) ===\n");
    sortUsersByAge(users, MAX_USERS, 1);
    for (int i = 0; i < MAX_USERS; i++) {
        printf("\nUser #%d:\n", i + 1);
        displayUserInfo(&users[i]);
    }
    
    // Test sorting - Descending
    printf("\n=== STEP 6: Sort Users by Age (Descending) ===\n");
    sortUsersByAge(users, MAX_USERS, 0);
    for (int i = 0; i < MAX_USERS; i++) {
        printf("\nUser #%d:\n", i + 1);
        displayUserInfo(&users[i]);
    }
    
    return 0;
}

/**
 * Get information for multiple users
 * Validates age range and ensures ID uniqueness
 * 
 * @param users Array of UserInfo structures to populate
 * @param count Number of users to add
 */
void getUserInfo(UserInfo users[], int count) {
    printf("--- Enter User Information ---\n");
    
    for (int i = 0; i < count; i++) {
        printf("\nUser #%d:\n", i + 1);
        
        int validInput = 0;
        
        // Get and validate ID (ensure uniqueness)
        while (!validInput) {
            printf("Enter ID: ");
            scanf("%d", &users[i].id);
            
            if (!isIdUnique(users, i, users[i].id)) {
                printf("Error: ID %d already exists. Please enter a unique ID.\n", 
                       users[i].id);
            } else {
                validInput = 1;
            }
        }
        
        // Clear input buffer
        while (getchar() != '\n');
        
        // Get name
        printf("Enter name: ");
        fgets(users[i].name, sizeof(users[i].name), stdin);
        users[i].name[strcspn(users[i].name, "\n")] = '\0'; // Remove newline
        
        // Get and validate age
        validInput = 0;
        while (!validInput) {
            printf("Enter age (%d-%d): ", MIN_AGE, MAX_AGE);
            scanf("%d", &users[i].age);
            
            if (validateAge(users[i].age)) {
                validInput = 1;
            } else {
                printf("Error: Age must be between %d and %d.\n", MIN_AGE, MAX_AGE);
            }
        }
    }
}

/**
 * Display information for a single user
 * 
 * @param user Pointer to the UserInfo structure to display
 */
void displayUserInfo(const UserInfo *user) {
    printf("----------------------------------------\n");
    printf("ID:   %d\n", user->id);
    printf("Name: %s\n", user->name);
    printf("Age:  %d\n", user->age);
    printf("----------------------------------------\n");
}

/**
 * Search for a user by their ID
 * 
 * @param users Array of UserInfo structures to search
 * @param count Number of users in the array
 * @param id The ID to search for
 * @return Index of the user if found, -1 otherwise
 */
int searchUserById(const UserInfo users[], int count, int id) {
    for (int i = 0; i < count; i++) {
        if (users[i].id == id) {
            return i; // User found, return index
        }
    }
    return -1; // User not found
}

/**
 * Search for users by name (case-insensitive, partial match)
 * 
 * @param users Array of UserInfo structures to search
 * @param count Number of users in the array
 * @param name The name to search for
 * @param results Array to store indices of matching users
 * @return Number of users found
 */
int searchUserByName(const UserInfo users[], int count, const char *name, int results[]) {
    int foundCount = 0;
    char lowerName[100];
    char lowerUserName[100];
    
    // Convert search name to lowercase for case-insensitive comparison
    strcpy(lowerName, name);
    for (int i = 0; lowerName[i]; i++) {
        lowerName[i] = tolower(lowerName[i]);
    }
    
    // Search through all users
    for (int i = 0; i < count; i++) {
        // Convert current user's name to lowercase
        strcpy(lowerUserName, users[i].name);
        for (int j = 0; lowerUserName[j]; j++) {
            lowerUserName[j] = tolower(lowerUserName[j]);
        }
        
        // Check if search name is a substring of user's name
        if (strstr(lowerUserName, lowerName) != NULL) {
            results[foundCount] = i;
            foundCount++;
        }
    }
    
    return foundCount;
}

/**
 * Sort users by age using bubble sort algorithm
 * 
 * @param users Array of UserInfo structures to sort
 * @param count Number of users in the array
 * @param ascending 1 for ascending order, 0 for descending order
 */
void sortUsersByAge(UserInfo users[], int count, int ascending) {
    UserInfo temp;
    
    // Bubble sort implementation
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            int shouldSwap = ascending ? 
                (users[j].age > users[j + 1].age) : 
                (users[j].age < users[j + 1].age);
            
            if (shouldSwap) {
                // Swap users[j] and users[j+1]
                temp = users[j];
                users[j] = users[j + 1];
                users[j + 1] = temp;
            }
        }
    }
}

/**
 * Validate if age is within acceptable range
 * 
 * @param age The age to validate
 * @return 1 if valid, 0 otherwise
 */
int validateAge(int age) {
    return (age >= MIN_AGE && age <= MAX_AGE);
}

/**
 * Check if an ID is unique among existing users
 * 
 * @param users Array of UserInfo structures
 * @param count Number of users to check against
 * @param id The ID to check
 * @return 1 if unique, 0 if duplicate found
 */
int isIdUnique(const UserInfo users[], int count, int id) {
    for (int i = 0; i < count; i++) {
        if (users[i].id == id) {
            return 0; // Duplicate found
        }
    }
    return 1; // ID is unique
}