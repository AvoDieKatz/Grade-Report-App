#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#include "variable.h"
#include "feature.h"
#include "helper.h"

int size = 0;
int id[20];
char name[20][31];
float grades[20];
char search_term[256];

void displayStudents() {

    if (size != 0) {
        printf("\n");
        printf("----------------------Student list----------------------\n");
        printf("\t%-10s| %-10s| %10s\n", "ID", "Name", "Grade");
        for(int i = 0; i < size; i++) {
          printf("\t%-10d| %-10s| %10.2f\n", id[i], name[i], grades[i]);
        }
        printf("\n");
    } else {
        printf("\n\n----------There are currently no student in the list----------\n\n");
    }

}

void addStudent() {

    int new_id = 0;
    char new_name[31] = "";
    float new_grade = 0.0;
    int scf_rtn = 0;

    for (;;) {
        printf("\nInput student ID: \n");
        scf_rtn = scanf("%d", &new_id);
    
        // Validate ID input
        int validateInt = validateIdInput(new_id, scf_rtn);
        if (validateInt == 0) {
          continue;
        } else if (validateInt == -1) {
          printf("Something wrong when trying to add a new student.\n");
        }

        // Check ID duplication
        int isDuplicate = isIdDuplicated(new_id);
        if (isDuplicate == 1) {
        printf("Duplicate student ID, try again.\n");
            continue;
        } else if (isDuplicate == 0) {
            break;
        }
    }

    for (;;) {
        printf("\nInput student's name: \n");
        scanf("%[^\n]%*c", new_name);
        int validateVal = validateName(new_name);
        if(validateVal == 0)  {
            break;
        } else if (validateVal == REG_NOMATCH) {
            printf("Invalid name, try again (Correct format is: FirstName LastName)");
            continue;
        }
    }

    for (;;) {
        printf("\nInput student's mark: \n");
        scf_rtn = scanf("%f", &new_grade);
        // Validate grade input
        int validateFl = validateFloatInput(new_grade, scf_rtn);
        if (validateFl == 0) {
            continue;
        } else if (validateFl == -1) {
            printf("Something wrong when trying to add a new student.\n");
        }
        break;
    }

    id[size] = new_id;
    strcpy(name[size], new_name);
    grades[size] = new_grade;
    size++;
    
}

void findHighLow() {

    int imax = 0;
    int imin = 0;
    
    if(size !=0) {
        printf("\n");
        printf("----------Students with HIGHEST grade----------\n");
        printf("\t%-10s| %10s| %10s\n", "ID", "Name", "Grade");
        // Find MAX grade
        for(int i=0; i<size; i++) {
            if(grades[imax] <= grades[i]) {
                imax = i;
            }
        }
        // Find students with MAX grade
        for (int i=0; i<size; i++) {
            if (grades[imax] == grades[i]) {
                printf("\t%-10d| %-10s| %10.2f\n", id[i], name[i], grades[i]);
            }
        }

        printf("----------Students with LOWEST grade----------\n");
        printf("\t%-10s| %10s| %10s\n", "ID", "Name", "Grade");
        // Find MIN grade
        for(int i=0; i<size; i++) {
            if(grades[imin] >= grades[i]) {
                imin = i;
            }
        }
        // Find students with MIN grade
        for (int i=0; i<size; i++) {
            if (grades[imin] == grades[i]) {
                printf("\t%-10d| %-10s| %10.2f\n", id[i], name[i], grades[i]);
            }
        }
    } else {
        printf("\n\n----------There are currently no student in the list----------\n\n");
    }    
    
}

void searchById(int input) {

    int found = isIdDuplicated(input);
    int count = 0;
    if (found == 1) {
        for (int i = 0; i < size; i++) {
            if (input == id[i]) {
                printf("\t%-10d| %-10s| %10.2f\n", id[i], name[i],grades[i]);
                count++;
            }
        }
    } else if (found == 0) {
        printf("No match with ID: %d\n", input);
    }
    if (count > 0) {
        printf("You found %d matches with id: %d\n", count, input);
    }
    return;

}

void searchByName(const char *input) {

    int count = 0;
    for (int i = 0; i < size; i++) {
        if (strcmp(input, name[i]) == 0) {
            printf("\t%-10d| %-10s| %10.2f\n", id[i], name[i],grades[i]);
            count++;
        }
    }
    if (count == 0) {
        printf("No match with name: %s\n", input);
    } else if (count > 0) {
        printf("You found %d matches with name: %s\n", count, input);
    }
    return;
    
}

void search() {

    printf("Search: ");
    scanf("%[^\n]%*c", search_term);
    printf("\t%-10s| %-10s| %5s\n", "ID", "Name", "Grade");
    int isInt = isInteger(search_term);
    if (isInt == 0) {
        int intInput = atoi(search_term);
        searchById(intInput);
    } else if (isInt == REG_NOMATCH) {
        searchByName(search_term);
    } else {
        printf("An error occurred while searching.");
    }
        
}

void exportCsv() {

    FILE *fpt;
    fpt = fopen("GradeReport.csv", "w+");
    fprintf(fpt, "ID, Grade\n");
    for (int i = 0; i < size; i++) {
      fprintf(fpt, "%d, %0.2f\n", id[i], grades[i]);
    }
    fclose(fpt);
    printf("\nA CSV file has been exported in the same directory\n");
    
}