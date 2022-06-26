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

    if (size == 0) {

        yellow();
        printf("\n\n----------There are currently no student in the list----------\n\n");
        reset();

    } else {

        cyan();
        printf("\n------------------------Student list------------------------\n");
        printf("\t%-10s|%-10s %s %10s|%10s\n", "ID", "", "Name", "", "Grade");
        reset();
        for(int i = 0; i < size; i++) {
          printf("\t%-10d|\t%-21s|%10.2f\n", id[i], name[i], grades[i]);
        }
        printf("\n");
    
        int back_flag = 0;
        do {

            printf("\n----------------------------------------------------\n");
            printf("1. Sort Low to High Grades.\n");
            printf("2. Sort High to Low Grades.\n");
            printf("0. Back to Main Menu.\n\n");

            char sub_choice[32];
            scanf("%[^\n]%*c", sub_choice);
            int validate = isInteger(sub_choice);
            if (validate == 0) {
                int opt = atoi(sub_choice);
                switch(opt) {
                    case 1:
                        sort("asc");
                        break;
                    case 2: 
                        sort("des");
                        break;
                    case 0:
                        back_flag = 1;
                        break;
                    default:
                        printf("Sorry, I don't understand that.");
                        break;
                }
            } else if (validate == 1) {
                printf("Sorry, I don't understand that.");
            }

        } while (back_flag != 1);
        
    }

}

void sort(const char *type) {

    int temp_grade;
    int temp_id;
    char temp_name[256];
    if (strcmp(type, "asc") == 0) {
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                if (grades[j] > grades[j + 1]) {
                    //swap grades
                    temp_grade = grades[j];
                    grades[j] = grades[j + 1];
                    grades[j + 1] = temp_grade;
                    //swap id
                    temp_id = id[j];
                    id[j] = id[j + 1];
                    id[j + 1] = temp_id;
                    //swap names
                    strcpy(temp_name, name[j]);
                    strcpy(name[j], name[j + 1]);
                    strcpy(name[j + 1], temp_name);
                }
            }
        }
    } else if (strcmp(type, "des") == 0) {
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                if (grades[j] < grades[j + 1]) {
                    //swap grades
                    temp_grade = grades[j];
                    grades[j] = grades[j + 1];
                    grades[j + 1] = temp_grade;
                    //swap id
                    temp_id = id[j];
                    id[j] = id[j + 1];
                    id[j + 1] = temp_id;
                    //swap names
                    strcpy(temp_name, name[j]);
                    strcpy(name[j], name[j + 1]);
                    strcpy(name[j + 1], temp_name);
                }
            }
        }
    }

    cyan();
    printf("\n------------------------Student list------------------------\n");
    printf("\t%-10s|%-10s %s %10s|%10s\n", "ID", "", "Name", "", "Grade");
    reset();
    for(int i = 0; i < size; i++) {
      printf("\t%-10d|\t%-21s|%10.2f\n", id[i], name[i], grades[i]);
    }
    printf("\n");
    
}

void addStudent() {

    int new_id = 0;
    char new_name[31] = "";
    float new_grade = 0.0;
    int scf_rtn = 0;
    char end_term;

    for (;;) {
        printf("\nInput student ID: \n");
        scf_rtn = scanf("%d%c", &new_id, &end_term);
        int validate = validateIdInput(new_id, scf_rtn, end_term);

        if (validate == 0) {
            continue;
        } else if (validate == -1) {
            printf("Something wrong when trying to add a new student.\n");
            exit(0);
        }

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
        scf_rtn = scanf("%[^\n]%*c", new_name);
        int validateVal = validateName(new_name, scf_rtn);
        if(validateVal == 0)  {
            break;
        } else if (validateVal == 1) {
            continue;
        }
    }

    for (;;) {
        printf("\nInput student's mark: \n");
        scf_rtn = scanf("%f%c", &new_grade, &end_term);
        int validate = validateGradeInput(new_grade, scf_rtn, end_term);
        if (validate == 0) {
            continue;
        } else if (validate == -1) {
            printf("Something wrong when trying to add a new student.\n");
            exit(0);
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