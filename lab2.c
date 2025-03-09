#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char name[50];
    float size;
    char unit[5];
    float price;
} Part;

// Function to add a new entry
void add_entry(Part **collection, int *entry_count) {
    Part *new_collection = realloc(*collection, (*entry_count + 1) * sizeof(Part));  // Allocate memory for one more entry

    if (new_collection == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    *collection = new_collection;
    
    // Add new entry
    printf("Enter Part ID: ");
    scanf("%d", &(*collection)[*entry_count].id);
    printf("Enter Part name: ");
    scanf("%s", (*collection)[*entry_count].name);
    printf("Enter part size: ");
    scanf("%f", &(*collection)[*entry_count].size);
    printf("Enter part size metric: ");
    scanf("%s", (*collection)[*entry_count].unit);
    printf("Enter Part Cost: ");
    scanf("%f", &(*collection)[*entry_count].price);

    (*entry_count)++;
}

// Function that removes the last entry
void remove_entry(Part **collection, int *entry_count) {
    if (*entry_count == 0) {
        printf("No entries to remove.\n");
        return;
    }

    if (*entry_count == 1) {
        free(*collection);
        *collection = NULL;
    } else {
        Part *new_collection = realloc(*collection, (*entry_count - 1) * sizeof(Part));
        if (new_collection == NULL) {
            printf("Memory allocation failed.\n");
            return;
        }
        *collection = new_collection;
    }
    (*entry_count)--;
}

// Function that displays all entries
void display_entries(Part *collection, int entry_count) {
    if (entry_count == 0) {
        printf("No records to print.\n");
        return;
    }

    for (int i = 0; i < entry_count; i++) {
        printf("Part %d: %s, %.2f %s, Cost: %.2f\n", 
               collection[i].id, 
               collection[i].name, 
               collection[i].size, 
               collection[i].unit, 
               collection[i].price);
    }
}

// Function that prints the number of records
void display_entry_count(int entry_count) {
    printf("Number of entries: %d\n", entry_count);
}

// Function that prints the size of the database
void display_collection_size(int entry_count) {
    printf("Size of collection: %lu bytes\n", entry_count * sizeof(Part));
}

// Main menu and program logic
int main() {
    Part *database = NULL;
    int num_records = 0;
    int choice;

    while (1) {
        printf("\nMENU\n");
        printf("1. Print all records\n");
        printf("2. Print number of records\n");
        printf("3. Print size of database\n");
        printf("4. Add record\n");
        printf("5. Delete record\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                display_entries(database, num_records);
                break;
            case 2:
                display_entry_count(num_records);
                break;
            case 3:
                display_collection_size(num_records);
                break;
            case 4:
                add_entry(&database, &num_records);
                break;
            case 5:
                remove_entry(&database, &num_records);
                break;
            case 6:
                free(database);  // Free allocated memory
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}