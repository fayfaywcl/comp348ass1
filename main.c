// main.c
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "ordering.h"
#include "budget.h"
#include "data.h"



int main(int argCount , char **argPointers) {

    printf("Welcome!\n"); //display the welcome message


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
    loadEntries(entries, &entryCount, argPointers[1]);

    do {
        
        displayMenu();
        scanf("%d", &choice);
        getchar();  // Clear newline character

        system("clear");  // Clear the screen 

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
                addEntry(&entries, &entryCount);
                break;
            case 5:
                modifyEntry(entries, entryCount);
                break;
            case 6: 
                filterByMonth(entries, entryCount);
                break;

            case 7:
                printf("Goodbye and thanks for using our budget tracker app!!!\n");
                break;

            case 8: 
                visualExpenseBreakdown(entries,entryCount);
                break;

            case 9:
                searchByAmount(entries, entryCount);
                break;

            case 10:
                undoLastAction(&entries, &entryCount);
                break; 

            default:
                printf("Invalid choice. Try again.\n");
        }
    
        

    } while (choice != 7); // Exit when the user selects option 7

    // Write data to the file
    saveEntries(entries,entryCount, argPointers[1]);

    free(entries);  // Free allocated memory
    
    return 0;
}

void displayMenu() {
    
    printf("\nBudget Tracking System\n");
    printf("===========================\n");
    printf("1. Display all entries\n");
    printf("2. Expense Distribution\n");
    printf("3. Sort Entries\n");
    printf("4. Add Income/Expense Entry\n");
    printf("5. Modify Entry\n");
    printf("6. Filter by Month\n");
    printf("7. Exit\n");
    printf("-------------------\n-Extra Credits Tasks-\n");
    printf("8. Visual Expense Breakdown\n");
    printf("9. Transaction Search Feature\n");
    printf("10: Undo Last Action\n");
    printf("\nChoice: ");
}
