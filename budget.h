//budget.h
#ifndef BUDGET_H
#define BUDGET_H

// make formatted column-oriented display
#define CATEGORY_SIZE 15
#define DESC_SIZE 50
#define DATE_SIZE 11
#define TYPE_SIZE 10

typedef struct {
    int id;
    char date[DATE_SIZE];        // Format: YYYY-MM-DD
    char type[TYPE_SIZE];        // "income" or "expense"
    char category[CATEGORY_SIZE];
    char description[DESC_SIZE];
    float amount;
} Entry;

// Function prototypes
void displayMenu();
void loadEntries(Entry *entries, int *entryCount);
void displayAllEntries(Entry *entries, int entryCount);
void expenseDistribution(Entry *entries, int entryCount);
void sortEntries(Entry *entries, int entryCount);
void addEntry(Entry *entries, int *entryCount);
void modifyEntry(Entry *entries, int entryCount);
void filterByMonth(Entry *entries, int entryCount);

#endif