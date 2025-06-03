//budget.c
//(the code used to carry out the logic of the menu options)
//displayAllEntries()=>1. Display all entries
//expenseDistribution()=>2. Expense Distribution
//3. Sort Entries => is in ordering.c for sorting method
//addEntry()=> 4. Add Income/Expense Entry
//modifyEntry()=> 5. Modify Entry
//filterByMonth()=> 6. Filter by Month

//visualExpenseBreakdown()=> 8. Visual Expense Breakdown
//searchByAmount()=> 9. Transaction Search Feature
//undoLastAction()=> 10. Undo Last Action

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>   // for localtime() function
#include "data.h"
#include "budget.h"



#define MAX_LINE_LENGTH 200
#define StringsFields_SIZE 100
Undo undoData = {0};  // Initialize with no undo



// 1. Display all entries
void displayAllEntries(Entry *entries, int entryCount) {
    printf("\nFinances Summary\n");
    printf("=================");

    //All columns have column headers
    printf("\n%-5s %-12s %-10s %-10s %-15s %10s\n", "ID", "Date", "Type", "Category", "Description", "Amount");
    printf("---------------------------------------------------------------------\n");
    for (int i = 0; i < entryCount; i++) {
        printf("%-5d %-12s %-10s %-10s %-19s $%-.2f\n",
               entries[i].id, entries[i].date, entries[i].type,
               entries[i].category, entries[i].description, entries[i].amount);
    }
}

// 2. Expense Distribution
// print total income, total expenses, expenses separated into needs 
// and wants, and their share in expenses as well as total income, and the net balance
void expenseDistribution(Entry *entries, int entryCount) {
    double totalIncome = 0.0, totalExpenses = 0.0;
    double needs = 0.0, wants = 0.0;

    //strcmp to compare the contents of two strings.Returns 0 if the strings are equal

    for (int i = 0; i < entryCount; i++) {
        if (strcmp(entries[i].type, "income") == 0) {
            totalIncome += entries[i].amount;
        } else if (strcmp(entries[i].type, "expense") == 0) {
            totalExpenses += entries[i].amount;
            if (strcmp(entries[i].category, "Needs") == 0) {
                needs += entries[i].amount;
            } else if (strcmp(entries[i].category, "Wants") == 0) {
                wants += entries[i].amount;
            }
        }
    }

    printf("\n=====Expense Distribution Report=====\n");
    
    printf("Total Income: $%.2f\n", totalIncome);
    printf("Total Expenses: $%.2f\n", totalExpenses);
    printf("Needs: $%.2f (%.2f%% of expenses, %.2f%% of income)\n",
            needs,
            (totalExpenses > 0) ? (needs / totalExpenses * 100) : 0.0,
           (totalIncome > 0) ? (needs / totalIncome * 100) : 0.0
            );

    printf("Wants: $%.2f (%.2f%% of expenses, %.2f%% of income)\n",
           wants,
           (totalExpenses > 0) ? (wants / totalExpenses * 100) : 0.0,
           (totalIncome > 0) ? (wants / totalIncome * 100) : 0.0
            );
    printf("Net Balance: $%.2f\n", totalIncome - totalExpenses);
    printf("=========================================\n");
}

// 3. Sort Entries => is in ordering.c for sorting method 

// 4. Add Income/Expense Entry
//allow a user to add an entry to the finances.
    //entriesPtr is a pointer to a pointer to an array of Entry structs.
    //count holds the current number of entries.
void addEntry(Entry **entriesPtr, int *entryCountPtr) {
    Entry *entries = *entriesPtr;
    int count = *entryCountPtr; //count holds the current number of entries

    // Allocate space for a new entry
    // Resize the memory block to hold one more Entry.
    entries = realloc(entries, (count + 1) * sizeof(Entry));
    if (!entries) {
        printf("Memory allocation failed.\n");
        return;
    }

    //Initialize the New Entry
    Entry *newEntry = &entries[count];

    //New Id for the new entry 
    int maxID = -1; // Safe initial value assuming IDs start from 0
    for (int i = 0; i < count; i++) {
        if (entries[i].id > maxID) {
            maxID = entries[i].id;
        }
    }
    newEntry->id = maxID + 1; // find the max ID and add 1


    char choicetdy;
    printf("\nUse today's date? (y/n): ");
    scanf(" %c", &choicetdy);
    while ((getchar()) != '\n' && getchar() != EOF) ; //Clear input buffer

    if (choicetdy == 'y'|| choicetdy == 'Y') {

        // Get current date using localtime
        time_t t = time(NULL);
        struct tm *tm_info = localtime(&t);        //convert a raw time value (time_t) into a human-readable date/time structure.
        strftime(newEntry->date, StringsFields_SIZE, "%Y-%m-%d", tm_info);
    } else if (choicetdy == 'n'|| choicetdy == 'N'){
        
        printf("Enter date (YYYY-MM-DD): ");
        scanf("%s", newEntry->date);     
    }

    printf("Type (income/expense): ");
    scanf("%s", newEntry->type);
    while ((getchar()) != '\n' && getchar() != EOF) ; // Clear input buffer

    printf("Category : ");
    scanf("%s", newEntry->category);
    while ((getchar()) != '\n' && getchar() != EOF) ; // Clear input buffer

    printf("Description: ");
    scanf("%s", newEntry->description); 
    while ((getchar()) != '\n' && getchar() != EOF) ; // Clear input buffer

    do {
    printf("Amount: $");
    scanf("%f", &newEntry->amount);
    while ((getchar()) != '\n' && getchar() != EOF) ; // Clear input buffer

    //not be able to update an amount with a negative value
    if (newEntry->amount < 0) {
        printf("Error: Amount cannot be negative. Please enter a non-negative value.\n");
    }
    } while (newEntry->amount < 0);


    (*entryCountPtr)++;
    *entriesPtr = entries;

    printf("Entry added successfully with %d\n", newEntry->id);

    // For Undo function
    // After a new entry is added, records the action as an addition.
    undoData.valid = 1;  // Mark undo as valid
    undoData.actionType = 1;  // 1 = Addition
}

//5. Modify Entry
//update the amount for an entry,
void modifyEntry(Entry *entries, int entryCount) {

    // first display the current contents, by using option 1 to Display All Entries.
    displayAllEntries(entries, entryCount);

    int id;

    printf("\nEnter ID of entry to modify: ");
    scanf("%d", &id);

    for (int i = 0; i < entryCount; i++) {
        if (entries[i].id == id) {
            printf("\nCurrent Details:\n");
            printf("ID: %d\n", entries[i].id);
            printf("Date: %s\n", entries[i].date);
            printf("Type: %s\n", entries[i].type);
            printf("Category: %s\n", entries[i].category);
            printf("Description: %s\n", entries[i].description);
            printf("Amount: $%.2f\n", entries[i].amount);
                        

            // For Undo function
            // Before updating the amount, save previous state
            undoData.valid = 1;       // Mark undo as valid
            undoData.actionType = 2;  // 2 = modification
            undoData.previousEntry = entries[i];  // Save the full entry before changes

            int choicemodify;
            printf("\nWhat would you like to modify?\n"); 
            printf("1. Date\n");
            printf("2. Amount\n");
            printf("Choice: ");
            scanf("%d", &choicemodify);

            switch(choicemodify){
                //1. Date
                case 1:
                    printf("Enter new date: ");
                    scanf("%s", entries[i].date);
                    break;
                //2. Amount
                case 2:
                    
                    do {
                        printf("Enter new amount: $");
                        scanf("%f", &entries[i].amount);
                        while ((getchar()) != '\n' && getchar() != EOF) ; // Clear input buffer
                        
                        //not be able to update an amount with a negative value
                        if (entries[i].amount < 0) {
                            printf("Error: Amount cannot be negative. Please enter a non-negative value.\n");
                        }
                    } while (entries[i].amount < 0);
                    

                    break;
                default:
                    printf("Invalid choice. ");
            }          
            
            printf("Entry updated successfully.\n");
        
            return;
        }
    }
    
    printf("Entry with ID %d not found.\n", id); //If ID is invalid, it shows "not found".
    // if are updating an entry and use an entry ID that doesn’t exist, the program should not crash.
}

//6. Filter by Month
//the user will be asked year and month
//only the records matching this criterion will be displayed
void filterByMonth(Entry *entries, int entryCount) {

    int year, month;
    printf("Enter year (YYYY): ");
    scanf("%d", &year);
    printf("Enter month (1-12): ");
    scanf("%d", &month);
    while ((getchar()) != '\n' && getchar() != EOF) ; // Clear input buffer

    printf("\nEntries for %04d-%02d:\n", year, month);
    printf("\n%-5s %-12s %-10s %-10s %-15s %10s\n", "ID", "Date", "Type", "Category", "Description", "Amount");
    printf("---------------------------------------------------------------------\n");

    int found = 0; // Flag to track if any matching entries are found

    for (int i = 0; i < entryCount; i++) {
        int entryYear, entryMonth, entryDay;
        // sscanf, reads from a string.
        // entries[i].date is a string in the format YYYY-MM-DD
        // "%d-%d-%d" tells sscanf to expect three integers separated by -
        //  &entryYear, &entryMonth, &entryDay are the variables to store the parsed integers
        sscanf(entries[i].date, "%d-%d-%d", &entryYear, &entryMonth, &entryDay);

        // Check if the entry matches the user’s selected year and month
        if (entryYear == year && entryMonth == month) {
            printf("%-5d %-12s %-10s %-10s %-19s $%-.2f\n", 
                   entries[i].id, entries[i].date, entries[i].type, 
                   entries[i].category, entries[i].description, entries[i].amount);
            found = 1; // Mark that a match has been found
        }
    }

    // no entries matched
    if (!found) {
        printf("\nNo entries found for the specified year and month.\n");
    }

}

//=============================
// Extra Credits (tasks)

//8. Visual Expense Breakdown
//Print a basic text-based bar chart (e.g., using * characters) 
//showing how "income"($) is distributed across different "expense" "subtypes".
void visualExpenseBreakdown(Entry *entries, int entryCount) {
    // Initialize totals for income, needs, wants, and overall expenses
    float needsTotal = 0.0, wantsTotal = 0.0, totalExpenses = 0.0, totalIncome = 0.0;

    int maxHeight = 20;  // Max height of the chart 

    // Loop through all entries to calculate income and expense totals
    for (int i = 0; i < entryCount; i++) {
        // Calculate total income
        if (strcmp(entries[i].type, "income") == 0) {
            totalIncome += entries[i].amount;
        }
        // Only process entries of type "expense"
        else if (strcmp(entries[i].type, "expense") == 0) {
            totalExpenses += entries[i].amount; // Add the amount($) to total expenses

            // Add amount to either needsTotal or wantsTotal based on category
            if (strcmp(entries[i].category, "Needs") == 0) {
                needsTotal += entries[i].amount;
            } else if (strcmp(entries[i].category, "Wants") == 0) {
                wantsTotal += entries[i].amount;
            }
        }
    }

    // Print the bar chart - showing how income is distributed across expense subtypes
    printf("\nVisual Expense Breakdown (Bar Chart):\n");
    printf("(How Income is Distributed Across Expense Subtypes)\n");
    printf("------------------------------------------------\n");

    // Calculate bar heights based on expense subtypes as percentage of income
    int needsHeight = (totalIncome > 0) ? (int)((needsTotal / totalIncome) * maxHeight) : 0;
    int wantsHeight = (totalIncome > 0) ? (int)((wantsTotal / totalIncome) * maxHeight) : 0;

    // Print the chart top-down
    for (int row = maxHeight; row >= 1; row--) {
        int percentage = (int)(((float)row / maxHeight) * 100);  // Convert row height to percentage
        printf("%3d%% ", percentage);  // Left column with percentage scale
        printf("%s", (needsHeight >= row) ? "  *  " : "     ");
        printf("%s", (wantsHeight >= row) ? "     *" : "     ");
        printf("\n");
    }

    // Print category labels and amounts
    printf("     Needs   Wants\n");
    printf("    $%.2f $%.2f\n", needsTotal, wantsTotal);
    
    // Print percentages of income going to each expense subtype
    printf("    (%.2f%%)  (%.2f%%)\n", 
           (needsTotal/totalIncome)*100, 
           (wantsTotal/totalIncome)*100);
    printf("(Total Income: $%.2f, Total Expenses: $%.2f)\n", totalIncome, totalExpenses);

    printf("\n");

    printf("\n");

    // Save to file (for bar chart) (expense_chart.txt)
    FILE *file = fopen("expense_chart.txt", "w");
    if (!file) {
        printf("Error writing expense_chart.txt!\n");
        return;
    }

    fprintf(file, "Visual Expense Breakdown (Vertical Bar Chart):\n");
    fprintf(file, "(How Income is Distributed Across Expense Subtypes)\n");
    fprintf(file, "------------------------------------------------\n");

    for (int row = maxHeight; row >= 1; row--) {
        int percentage = (int)(((float)row / maxHeight) * 100);
        fprintf(file, "%3d%% ", percentage);
        fprintf(file, "%s", (needsHeight >= row) ? "  *  " : "     ");
        fprintf(file, "%s", (wantsHeight >= row) ? "     *" : "     ");
        fprintf(file, "\n");
    }

    fprintf(file, "     Needs   Wants\n");
    fprintf(file, "    $%.2f $%.2f\n", needsTotal, wantsTotal);
    fprintf(file, "    (%.2f%%)  (%.2f%%)\n", 
           (needsTotal/totalIncome)*100, 
           (wantsTotal/totalIncome)*100);
    fprintf(file, "(Total Income: $%.2f, Total Expenses: $%.2f)\n", totalIncome, totalExpenses);

    fclose(file);
}

// 9. Transaction Search Feature: 
// Allow the user to search for transactions by amount range.
void searchByAmount(Entry *entries, int entryCount) {

    float minAmount, maxAmount;
    printf("\nEnter minimum amount: ");
    scanf("%f", &minAmount);
    printf("Enter maximum amount: ");
    scanf("%f", &maxAmount);

    // Print the header of the search results
    printf("\nEntries between %.2f and %.2f:\n", minAmount, maxAmount);
    printf("=================================\n");
    printf("%-5s %-12s %-10s %-10s %-20s %10s\n", "ID", "Date", "Type", "Category", "Description", "Amount");
    printf("--------------------------------------------------------------------------------\n");

    int found = 0; // Flag to track if any matching entries are found

    // Loop through all entries to check if they fall within the amount range
    for (int i = 0; i < entryCount; i++) {
        // If the entry amount is within the range, print it
        if (entries[i].amount >= minAmount && entries[i].amount <= maxAmount) {
            printf("%-5d %-12s %-10s %-10s %-20s %10.2f\n",
                   entries[i].id,
                   entries[i].date,
                   entries[i].type,
                   entries[i].category,
                   entries[i].description,
                   entries[i].amount);
            found++;
        }
    }

    // NO entries matched the amount range
    if (found == 0) {
        printf("No entries found in this amount range.\n");
    }

    printf("\n");
}

//10. Undo Last Action
//A basic undo feature to reverse the "most recent" addition or update.  
void undoLastAction(Entry **entriesPtr, int *entryCountPtr) {
    
    if (!undoData.valid) {
        printf("\nNo undo available. Either no action has been performed or the last action has already been undone.\n");
        return;
    }

    Entry *entries = *entriesPtr;

    if (undoData.actionType == 1) {  // Undo Add
        (*entryCountPtr)--;
        printf("\nUndo(recent addition): Last entry removed.\n");
    } else if (undoData.actionType == 2) {  // Undo Modify
        for (int i = 0; i < *entryCountPtr; i++) {
            if (entries[i].id == undoData.previousEntry.id) {
                entries[i] = undoData.previousEntry;
                printf("\nUndo(recent update): Modification reverted for entry ID %d.\n", entries[i].id);
                break;
            }
        }
    }

    // Clear the undo
    // So only undo feature to reverse the most "recent" addition or update.  
    undoData.valid = 0;
}
