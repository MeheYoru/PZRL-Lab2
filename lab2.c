#include <stdio.h>
#include <regex.h>
#include <stdlib.h>
#include <string.h>

char** readFile(char* filename, int* size) {
  FILE *file = fopen(filename, "rw");
  if(file == NULL) {
    printf("Unable to open file\n");
    return NULL;
  }

  int nLines = 1;
  char** ans = malloc(sizeof(char*));
  ans[0] = malloc(2048*sizeof(char));
  int i = 1;
  while(fgets(ans[nLines-1], 2048, file) != NULL) {
    nLines+=1;
    ans = realloc(ans, nLines*sizeof(char*));
    ans[i] = malloc(2048*sizeof(char));
    i++;
  }
  *size = nLines-1;
  fclose(file);
  return ans;
}

void doSwap(char** file, const int size, char* old_text, char* new_text) {
  for(int i = 0; i < size; i++) {
    char* temp;
    temp = strstr(file[i], old_text);
    while(temp) {
      file[i] = realloc(file[i], 3000*sizeof(char));
      temp = strstr(file[i], old_text);
      memmove(temp+strlen(new_text), temp+strlen(old_text), 2048-strlen(old_text));
      memmove(temp, new_text, strlen(new_text));
      temp = strstr(file[i], old_text);
    }
  }
  return;
}
void extractRegex(char* input, char** output1, char** output2, int type) {
    const char *pattern = "";
    if(type) {
      pattern = "^s\\/(.*?)\\/(.*?)\\/$";
    }
    else {
      pattern = "^\\/(.*?)\\/d$";
    }
    regex_t compiled;
    regmatch_t matches[3];

    int status = regcomp(&compiled, pattern, REG_EXTENDED | REG_NEWLINE);

    if (status != 0) {
        printf("Regex compilation failed");
        return;
    }

    status = regexec(&compiled, input, 3, matches, 0);

    if (status == 0) {
        char *old_text = (char*)malloc(matches[1].rm_eo - matches[1].rm_so + 1);
        strncpy(old_text, input + matches[1].rm_so, matches[1].rm_eo - matches[1].rm_so);
        old_text[matches[1].rm_eo - matches[1].rm_so] = '\0';
        char *new_text = (char*)malloc(matches[2].rm_eo - matches[2].rm_so + 1);
        strncpy(new_text, input + matches[2].rm_so, matches[2].rm_eo - matches[2].rm_so);
        new_text[matches[2].rm_eo - matches[2].rm_so] = '\0';
        *output1 = old_text;
        *output2 = new_text;
    }

    regfree(&compiled);
  return;
}

void addFront(char** file, int size, char* output1, char* output2) {
  for(int i = 0; i < size; i++) {
    file[i] = realloc(file[i], (2048+strlen(output2))*sizeof(char));
    memmove(file[i]+strlen(output2), file[i], 2048*sizeof(char));
    memmove(file[i], output2, strlen(output2));
  }
  return;
}
void addEnd(char** file, int size, char* output1, char* output2) {
  strcat(output2, "\n");
  for(int i = 0; i < size; i++) {
    file[i] = realloc(file[i], (2048+strlen(output2))*sizeof(char));
    memcpy(file[i]+strlen(file[i])-1, output2, strlen(output2));
  }
  return;
}

void delText(char** file, int size, char* output1, char* output2) {
  for(int i = 0; i < size; i++) {
      char* temp;
      temp = strstr(file[i], output1);
      while(temp) {
        file[i] = realloc(file[i], 3000*sizeof(char));
        temp = strstr(file[i], output1);
        memmove(temp+strlen(""), temp+strlen(output1), 2048-strlen(output1));
        memmove(temp, "", strlen(""));
        temp = strstr(file[i], output1);
      }
    }
    return;
}
void writeFile(char** text, char* filename, const int size) {
  FILE *file = fopen(filename, "w");
  for(int i = 0; i < size; i++) {
    fprintf(file, text[i]);
  }
  return;
}