#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <stdlib.h>
#include "lab2.h"


int main(int argc, char** argv) {
  if(argc < 3) {
    printf("Incorrect input\n");
    return 1;
  }

  char* command = argv[2];
  int size = 0;
  char** inputText = readFile(argv[1], &size);
  if(!inputText) {
    return 1;
  }
  if(command[1] == command[2]) {
    return 1;
  }
  char* input1 = "in1";
  char* input2 = "in2";
  if(command[0] == 's') {
    extractRegex(command, &input1, &input2, 1);
    switch (*input1) {
    case '^':
      addFront(inputText, size, input1, input2);
      break;
    case '$':
      addEnd(inputText, size, input1, input2);
      break;
    default:
      doSwap(inputText, size, input1, input2);
      break;
    }
  }
  else if(command[strlen(command)-1]=='d') {
    extractRegex(command, &input1, &input2, 0);
    delText(inputText, size, input1, input2);
  }
  writeFile(inputText, argv[1], size);
  for(int i = 0; i < size; i++) {
    free(inputText[i]);
  }
  free(inputText);
  return 0;
}
