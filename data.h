//data.h
#ifndef DATA_H
#define DATA_H

// make formatted column-oriented display
//All strings fields are no longer than 100 characters.
#define StringsFields_SIZE 100

typedef struct {
    int id;
    char date[StringsFields_SIZE];        // Format: YYYY-MM-DD
    char type[StringsFields_SIZE];        // "income" or "expense"
    char category[StringsFields_SIZE];    
    char description[StringsFields_SIZE];
    float amount;
} Entry;

// Function prototypes

void loadEntries(Entry *entries, int *entryCount, char filename[]);
void saveEntries(Entry *entries, int entryCount, char filename[]) ;

#endif