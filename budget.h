//budget.h
#ifndef BUDGET_H
#define BUDGET_H

#include "data.h"

//For Undo function (Extra Credits)
typedef struct {
    int valid;  // 0 = no undo, 1 = valid
    int actionType;  // 1 = add, 2 = modify
    Entry previousEntry;  // For modify
} Undo;

extern Undo undoData;  // Extern declaration for global undoData


// Function prototypes

void displayAllEntries(Entry *entries, int entryCount);
void expenseDistribution(Entry *entries, int entryCount);
void addEntry(Entry **entriesPtr, int *entryCountPtr);
void modifyEntry(Entry *entries, int entryCount);
void filterByMonth(Entry *entries, int entryCount);

void visualExpenseBreakdown(Entry *entries, int entryCount);
void searchByAmount(Entry *entries, int entryCount);
void undoLastAction(Entry **entriesPtr, int *entryCountPtr) ;


#endif