// data.c
//(any code used to read the input file and extract the fields from each row)
//loadEntries()
//saveEntries()

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data.h"

#define MAX_LINE_LENGTH 200
// buffer size for reading a line
// reading each line up to 199 characters + null terminator

// Load the entries from the input

//  The input data is assumed to have NO errors. 
// Each row is separated by a single newline character and has exactly six fields. 
void loadEntries(Entry *entries, int *entryCount, char filename[]) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        fprintf(stderr, "Could not open %s.\n", filename);
        *entryCount = 0;
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LENGTH];
    int count = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        

        // Remove trailing newline character if present
        line[strcspn(line, "\n")] = 0; // Remove newline

        // Tokenize line by '|'
        char *tokens[6];
        int fieldCount = 0;

        char *token = strtok(line, "|"); // Get first token
        while (token != NULL && fieldCount < 6) {
            tokens[fieldCount++] = token;
            token = strtok(NULL, "|"); // Get next token
        }

        //In case the input file does not comply with the 
        //above specification(1. exactly 6 fields, 2. Check string lengths ),  program may simply display the following error message and exits 
        //abnormally (use standard error console, stderr).

        // Check exactly 6 fields
       
        if (fieldCount != 6) {
            fprintf(stderr, "Error: Invalid data format in input file.\n");
            fclose(file);
            exit(EXIT_FAILURE);// Exit the program with failure status
        }

        // Check string lengths 
        // that maximum possible lengths of all strings fields are no longer than 100 characters
        if (strlen(tokens[1]) >= StringsFields_SIZE ||
            strlen(tokens[2]) >= StringsFields_SIZE ||
            strlen(tokens[3]) >= StringsFields_SIZE ||
            strlen(tokens[4]) >= StringsFields_SIZE) {
            fprintf(stderr, "Error: One or more fields exceed maximum length.\n");
            fclose(file);
            exit(EXIT_FAILURE); // Exit due to invalid field length
        }

        // Parse validated tokens
        entries[count].id = atoi(tokens[0]); // Convert string to integer
        strncpy(entries[count].date, tokens[1], StringsFields_SIZE);
        strncpy(entries[count].type, tokens[2], StringsFields_SIZE);
        strncpy(entries[count].category, tokens[3], StringsFields_SIZE);
        strncpy(entries[count].description, tokens[4], StringsFields_SIZE);
        entries[count].amount = atof(tokens[5]); // Convert string to float

        count++; // Increment number of valid entries
    }

    *entryCount = count; // Update the caller with the number of entries loaded
    fclose(file);
}

void saveEntries(Entry *entries, int entryCount, char filename[]) {
    FILE *file = fopen(filename, "w");  // Overwrite the file with updated data

    if (file == NULL) {
        printf("Error: Could not open %s for writing.\n", filename);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < entryCount; i++) {
        fprintf(file, "%d|%s|%s|%s|%s|%.2f\n",
            entries[i].id,
            entries[i].date,
            entries[i].type,
            entries[i].category,
            entries[i].description,
            entries[i].amount
        );
    }

    fclose(file);

}

