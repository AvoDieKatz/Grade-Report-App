#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "variable.h"
#include "feature.h"
#include "helper.h"

int size = 0;
int id[20];
char name[20][31];
float grades[20];

void displayStudents() {

    if (size != 0) {
        
        cyan();
        printf("\n------------------------Student list------------------------\n");
        printf("\t%-10s|%-10s %s %10s|%10s\n", "ID", "", "Name", "", "Grade");
        reset();
        for(int i = 0; i < size; i++) {
          printf("\t%-10d|\t%-21s|%10.2f\n", id[i], name[i], grades[i]);
        }
        printf("\n");
    } else {
        yellow();
        printf("\n\n----------There are currently no student in the list----------\n\n");
        reset();
    }

}

void addStudent() {

    int new_id = 0;
    char new_name[31] = "";
    float new_grade = 0.0;
    int scf_rtn = 0;

    for (;;) {      //equivalent to while(true)
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
            red();
            printf("Duplicate student ID, try again.\n");
            reset();
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
        } else if (validateVal == 1) {
            red();
            printf("Invalid name, try again (Correct format is: FirstName LastName)");
            reset();
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

    int i_max = 0;
    int i_min = 0;
    
    if(size !=0) {
        cyan();
        printf("\n-----------------Students with HIGHEST grade-----------------\n");
        printf("\t%-10s|%-10s %s %10s|%10s\n", "ID", "", "Name", "", "Grade");
        reset();
        // Find MAX grade
        for(int i=0; i<size; i++) {
            if(grades[i_max] <= grades[i]) {
                i_max = i;
            }
        }
        // Find students with MAX grade
        for (int i=0; i<size; i++) {
            if (grades[i_max] == grades[i]) {
                printf("\t%-10d|\t%-21s|%10.2f\n", id[i], name[i], grades[i]);
            }
        }

        cyan();
        printf("\n-----------------Students with LOWEST grade-----------------\n");
        printf("\t%-10s|%-10s %s %10s|%10s\n", "ID", "", "Name", "", "Grade");
        reset();
        // Find MIN grade
        for(int i=0; i<size; i++) {
            if(grades[i_min] >= grades[i]) {
                i_min = i;
            }
        }
        // Find students with MIN grade
        for (int i=0; i<size; i++) {
            if (grades[i_min] == grades[i]) {
                printf("\t%-10d|\t%-21s|%10.2f\n", id[i], name[i], grades[i]);
            }
        }
    } else {
        yellow();
        printf("\n\n----------There are currently no student in the list----------\n\n");
        reset();
    }    
    
}

void searchById(int input) {

    int found = isIdDuplicated(input);
    if (found == 1) {
        for (int i = 0; i < size; i++) {
            if (input == id[i]) {
                printf("\t%-10d|\t%-21s|%10.2f\n", id[i], name[i], grades[i]);
            }
        }
        green();
        printf("You found a match with ID: %d\n", input);
        reset();
    } else if (found == 0) {
        red();
        printf("No match");
        reset();
        printf("with ID: %d\n", input);
        
    }
    return;

}

void searchByName(const char *input) {

    int count = 0;
    for (int i = 0; i < size; i++) {
        if (strcmp(input, name[i]) == 0) {
            printf("\t%-10d|\t%-21s|%10.2f\n", id[i], name[i], grades[i]);
            count++;
        }
    }
    if (count == 0) {
        red();
        printf("No match ");
        reset();
        printf("with term: %s\n", input);
    } else if (count > 0) {
        printf("You found");
        green();
        printf(" %d ", count);
        reset();
        printf("matches with term:");
        printf(" %s\n ", input);
    }
    return;
    
}

void search() {

    char search_term[256];
    printf("Search: ");
    scanf("%[^\n]%*c", search_term);
    cyan();
    printf("\t%-10s|%-10s %s %10s|%10s\n", "ID", "", "Name", "", "Grade");
    reset();
    int isInt = isInteger(search_term);
    if (isInt == 0) {
        int intInput = atoi(search_term);
        searchById(intInput);
    } else if (isInt == 1) {
        searchByName(search_term);
    } else {
        printf("An error occurred while searching.");
    }
        
}

void exportCsv() {

    FILE *fpt;
    fpt = fopen("GradeReport.csv", "w+");
    fprintf(fpt, "ID, Name, Grade\n");
    for (int i = 0; i < size; i++) {
      fprintf(fpt, "%d, %s, %0.2f\n", id[i], name[i], grades[i]);
    }
    fclose(fpt);
    green();
    printf("\nA CSV file has been exported in the same directory\n");
    reset();
}