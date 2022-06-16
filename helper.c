#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#include "variable.h"
#include "helper.h"

void emptyBuffer() {

    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
    
}

int isIdDuplicated(int input) {

  int flag = 0, i = 0;
  while (i < size) {
    if(input == id[i]) {
      flag = 1;
      break;
    } else {
      i++;
    }
  }
  return flag;

}

int validateIdInput(int input, int scf_rtn) {

  if (scf_rtn == 0) {
    printf("Invalid input. (Not a number)\n");
    emptyBuffer();
    return 0;
  } else if (input < 1) {
    printf("Invalid input. (Out of range)\n");
    emptyBuffer();
    return 0;
  } else {
    emptyBuffer();
    return 1;
  }
  return -1;

}

int validateFloatInput(float input, int scf_rtn) {

  if (scf_rtn == 0) {
    printf("Not a valid grade (Number only)\n");
    emptyBuffer();
    return 0;
  } else if (input < 0.0 || input > 10.0) {
    printf("Not a valid grade (Out of range)\n");
    emptyBuffer();
    return 0;
  } else {
    emptyBuffer();
    return 1;
  }
  return -1;

}

int validateName(const char *input) {

    int value;
    regex_t regex;
    const char* pattern = "^[[:alpha:]]* [[:alpha:]]*$";
    value = regcomp(&regex, pattern, 0);
    value = regexec(&regex, input, 0, NULL, 0);
    regfree(&regex);
    return value;

}

int isInteger(const char *input) {

    int value;
    regex_t regex;
    const char* pattern = "^[[:digit:]]*$";
    value = regcomp(&regex, pattern, 0);
    value = regexec(&regex, input, 0, NULL, 0);
    regfree(&regex);
    return value;
    
}