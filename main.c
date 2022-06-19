#include <stdio.h>

#include "feature.h"
#include "helper.h"

int main() {

  int choice;
  int exit_flag = 0;
  int scf_rtn = 0; //value to check if "scanf" return correct type

  do {
    purple();
    printf("\n----------------------Grade Management App----------------------\n");
    reset();
    printf("1. Show all.\n");
    printf("2. Add new student.\n");
    printf("3. Best and Worst student.\n");
    printf("4. Search student. (By 'name' and 'id')\n");
    printf("5. Export to CSV file.\n");
    printf("0. Quit.\n\n");
    printf("Choose your option: ");

    scf_rtn = scanf("%d", &choice);
    emptyBuffer();

    if (scf_rtn == 0) {
      red();
      printf("Invalid choice. (Not a number)\n");
      reset();
      continue;
    } else if (choice < 0 || choice > 5) {
      red();
      printf("Invalid choice. (Out of range)\n");
      reset();
      continue;
    }

    switch (choice) {

      case 1:
        displayStudents();
        break;

      case 2: {
        addStudent();
        break;
      }

      case 3:
        findHighLow();
        break;

      case 4: 
        search();
        break;

      case 5: {
        exportCsv();
        break;
      }

      case 0: 
        printf("Bye bye!\n");
        exit_flag = 1;
        break;

      default:
        printf("Invalid choice, try again.\n");
        break;
    }
  } while (exit_flag != 1);

  return 0;
  
}
