#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "budget.h"

#define MAX_LINE_LENGTH 200


void loadEntries(Entry *entries, int *entryCount) {
    FILE *file = fopen("finances.txt", "r");
    if (file == NULL) {
        printf("Could not open finances.txt. \n");
        *entryCount = 0;
        return;
    }

    char line[MAX_LINE_LENGTH];
    int count = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        if (count >= MAX_LINE_LENGTH) break;

        line[strcspn(line, "\n")] = 0; // Remove newline

        // Use strtok to split line by '|'
        char *token = strtok(line, "|");
        if (token != NULL) entries[count].id = atoi(token);

        token = strtok(NULL, "|");
        if (token != NULL) strncpy(entries[count].date, token, sizeof(entries[count].date));

        token = strtok(NULL, "|");
        if (token != NULL) strncpy(entries[count].type, token, sizeof(entries[count].type));

        token = strtok(NULL, "|");
        if (token != NULL) strncpy(entries[count].category, token, sizeof(entries[count].category));

        token = strtok(NULL, "|");
        if (token != NULL) strncpy(entries[count].description, token, sizeof(entries[count].description));

        token = strtok(NULL, "|");
        if (token != NULL) entries[count].amount = atof(token);

        count++;
    }

    *entryCount = count;
    fclose(file);
}

void displayAllEntries(Entry *entries, int entryCount) {
    printf("\n%-5s %-12s %-10s %-10s %-15s %10s\n", "ID", "Date", "Type", "Subtype", "Description", "Amount");
    printf("---------------------------------------------------------------------\n");
    for (int i = 0; i < entryCount; i++) {
        printf("%-5d %-12s %-10s %-10s %-15s %10.2f\n",
               entries[i].id, entries[i].date, entries[i].type,
               entries[i].category, entries[i].description, entries[i].amount);
    }
    printf("\n");
}