//ordering.c
//(any code related to sorting the entries)
//void sortEntries()=> 3. Sort Entries

//compare functions
// int compareByID(),int compareByDate(),int compareByAmount(),int compareByDescription()
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "budget.h"
#include "data.h"
#include "ordering.h"



// 3. Sort Entries

    // Name of compare functions 
    int compareByID(const void *a, const void *b) {
        Entry *e1 = (Entry *)a;
        Entry *e2 = (Entry *)b;
        return e1->id - e2->id;
    }

    int compareByDate(const void *a, const void *b) {
        Entry *e1 = (Entry *)a;
        Entry *e2 = (Entry *)b;
        return strcmp(e1->date, e2->date);
    }

    int compareByAmount(const void *a, const void *b) {
        Entry *e1 = (Entry *)a;
        Entry *e2 = (Entry *)b;
        if (e1->amount < e2->amount) return -1;
        if (e1->amount > e2->amount) return 1;
        return 0;
    }

    int compareByDescription(const void *a, const void *b) {
        Entry *e1 = (Entry *)a;
        Entry *e2 = (Entry *)b;
        return strcmp(e1->description, e2->description);
    }
//sortEntries function (3.)
void sortEntries(Entry *entries, int entryCount) {
    int sortChoice;
    printf("\nSort Menu\n");
    printf("1. Sort by ID\n");
    printf("2. Sort by Date\n");
    printf("3. Sort by Amount\n");
    printf("4. Sort by Description\n");
    printf("Choice: ");
    scanf("%d", &sortChoice);

    switch (sortChoice) {
        //qsort(1,2,3,4) takes 
        //(1) the array to be sorted, 
        //(2) the numbe rs of elements in the array, 
        //(3) the size (in bytes) of each element, and 
        //(4) the name of the comparison function. 
        
        case 1:
            qsort(entries, entryCount, sizeof(Entry), compareByID);
            printf("Entries sorted by ID.\n");
            break;
        case 2:
            qsort(entries, entryCount, sizeof(Entry), compareByDate);
            printf("Entries sorted by date.\n");
            break;
        case 3:
            qsort(entries, entryCount, sizeof(Entry), compareByAmount);
            printf("Entries sorted by amount.\n");
            break;
        case 4:
            qsort(entries, entryCount, sizeof(Entry), compareByDescription);
            printf("Entries sorted by description.\n");
            break;
        default:
            printf("Invalid choice.\n");
            break;
    }

    // Display sorted entries , by using option 1 to Display All Entries.
    displayAllEntries(entries, entryCount);
}