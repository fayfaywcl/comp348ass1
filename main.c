// main.c
#include <stdio.h>
#include <stdlib.h>
#include "budget.h"


int main() {
    printf("Welcome");

    Entry *entries = NULL;
    
    int capacity = 10;    // Initial capacity for dynamic array
    int choice;
    int entryCount = 0; // Number of entries

    // Use malloc for dynamically creating data, and free for deallocating memory.
    // Allocate initial memory
    entries = (Entry *) malloc(capacity * sizeof(Entry));
    if (entries == NULL) {
        printf("Memory allocation failed. Exiting...\n");
         return 1;
    }

    // Load data from file
    loadEntries(entries, &entryCount);

    do {
        displayMenu();
        scanf("%d", &choice);
        getchar();  // Clear newline character

        switch (choice) {
            case 1:
                displayAllEntries(entries, entryCount);
                break;
            case 2:
                expenseDistribution(entries, entryCount);
                break;
            case 3:
                sortEntries(entries, entryCount);
                break;
            case 4:
                addEntry(entries, &entryCount);
                break;
            case 5:
                modifyEntry(entries, entryCount);
                break;
            case 6: {
                filterByMonth(entries, entryCount);
                break;
            }
            case 7:
                printf("Goodbye and thanks for using our budget tracker app\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }

    } while (choice != 7);

    free(entries);  // Free allocated memory
    
    return 0;
}

void displayMenu() {
    printf(" Budget Tracking System\n");
    printf("===========================\n");
    printf("1. Display all entries\n");
    printf("2. Expense Distribution\n");
    printf("3. Sort Entries\n");
    printf("4. Add Income/Expense Entry\n");
    printf("5. Modify Entry\n");
    printf("6. Filter by Month\n");
    printf("7. Exit\n");
    printf("Choice: ");
}
